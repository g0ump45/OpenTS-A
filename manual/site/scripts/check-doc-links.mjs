import { existsSync, readFileSync, readdirSync, statSync } from 'node:fs';
import { dirname, extname, isAbsolute, relative, resolve, sep } from 'node:path';
import { fileURLToPath } from 'node:url';

const scriptDirectory = dirname(fileURLToPath(import.meta.url));
const rootOption = process.argv.indexOf('--root');
if (rootOption >= 0 && !process.argv[rootOption + 1]) throw new Error('--root requires a directory');
const repository = rootOption >= 0
	? resolve(process.argv[rootOption + 1])
	: resolve(scriptDirectory, '../../..');
const roots = rootOption >= 0 ? ['.'] : [
	'README.md',
	'CONTRIBUTING.md',
	'AGENTS.md',
	'docs',
	'manual/README.md',
	'manual/AUTHORING.md',
	'manual/AGENTS.md',
	'manual/STYLE.md',
	'manual/MAINTAINING.md',
	'manual/content',
	'manual/changes',
	'manual/site/src/content/docs',
];

const markdownFiles = [];
function collect(path) {
	if (!existsSync(path)) return;
	if (statSync(path).isDirectory()) {
		for (const name of readdirSync(path).sort()) collect(resolve(path, name));
		return;
	}
	if (['.md', '.mdx'].includes(extname(path).toLowerCase())) markdownFiles.push(path);
}
for (const root of roots) collect(resolve(repository, root));

const displayPath = (path) => relative(repository, path).split(sep).join('/');
const failures = [];

function exactCaseFailure(path) {
	const local = relative(repository, path);
	if (isAbsolute(local) || local === '..' || local.startsWith(`..${sep}`)) {
		return 'target escapes the repository';
	}
	let cursor = repository;
	for (const part of local.split(sep).filter(Boolean)) {
		const names = readdirSync(cursor);
		if (!names.includes(part)) {
			const actual = names.find((name) => name.toLowerCase() === part.toLowerCase());
			return actual ? `path case is ${JSON.stringify(actual)}, not ${JSON.stringify(part)}` : null;
		}
		cursor = resolve(cursor, part);
	}
	return null;
}

function githubSlug(value) {
	return value
		.replace(/<[^>]*>/g, '')
		.replace(/!\[([^\]]*)\]\([^)]*\)/g, '$1')
		.replace(/\[([^\]]+)\]\([^)]*\)/g, '$1')
		.replace(/[`*_~]/g, '')
		.toLowerCase()
		.trim()
		.replace(/[^\p{L}\p{M}\p{N}\s_-]/gu, '')
		.replace(/\s+/g, '-');
}

const anchorsByFile = new Map();
function anchorsFor(path) {
	if (anchorsByFile.has(path)) return anchorsByFile.get(path);
	const source = readFileSync(path, 'utf8');
	const anchors = new Set();
	const duplicates = new Map();
	for (const match of source.matchAll(/^ {0,3}#{1,6}\s+(.+?)\s*#*\s*$/gm)) {
		const explicit = match[1].match(/\s+\{#([^}]+)\}\s*$/)?.[1];
		const base = explicit ?? githubSlug(match[1].replace(/\s+\{#[^}]+\}\s*$/, ''));
		if (!base) continue;
		const duplicate = duplicates.get(base) ?? 0;
		anchors.add(duplicate === 0 ? base : `${base}-${duplicate}`);
		duplicates.set(base, duplicate + 1);
	}
	for (const match of source.matchAll(/\bid=["']([^"']+)["']/gi)) anchors.add(match[1]);
	anchorsByFile.set(path, anchors);
	return anchors;
}

function targetsOnLine(line) {
	const targets = [];
	for (const match of line.matchAll(/!?\[[^\]]*\]\(\s*(?:<([^>]+)>|([^\s)]+))/g)) {
		targets.push(match[1] ?? match[2]);
	}
	const definition = line.match(/^\s*\[[^\]]+\]:\s*(?:<([^>]+)>|(\S+))/);
	if (definition) targets.push(definition[1] ?? definition[2]);
	for (const match of line.matchAll(/<a\b[^>]*\bhref=["']([^"']+)["']/gi)) targets.push(match[1]);
	return [...new Set(targets)];
}

function checkTarget(sourceFile, lineNumber, rawTarget) {
	if (!rawTarget || /^(?:[a-z][a-z0-9+.-]*:|\/\/)/i.test(rawTarget)) return;
	if (rawTarget.startsWith('/')) return;
	const [rawPath, rawFragment] = rawTarget.split('#', 2);
	let pathPart;
	let fragment;
	try {
		pathPart = decodeURIComponent(rawPath.split('?')[0]);
		fragment = rawFragment === undefined ? undefined : decodeURIComponent(rawFragment);
	} catch {
		failures.push(`${displayPath(sourceFile)}:${lineNumber}: invalid URL encoding in ${rawTarget}`);
		return;
	}
	const target = pathPart ? resolve(dirname(sourceFile), pathPart) : sourceFile;
	const local = relative(repository, target);
	if (isAbsolute(local) || local === '..' || local.startsWith(`..${sep}`)) {
		failures.push(`${displayPath(sourceFile)}:${lineNumber}: target escapes the repository: ${rawTarget}`);
		return;
	}
	if (!existsSync(target)) {
		failures.push(`${displayPath(sourceFile)}:${lineNumber}: missing target ${rawTarget}`);
		return;
	}
	const caseFailure = exactCaseFailure(target);
	if (caseFailure) {
		failures.push(`${displayPath(sourceFile)}:${lineNumber}: ${caseFailure}: ${rawTarget}`);
		return;
	}
	if (!fragment) return;
	if (/^L\d+(?:-L\d+)?$/.test(fragment) && !['.md', '.mdx'].includes(extname(target).toLowerCase())) return;
	let anchorSource = target;
	if (statSync(target).isDirectory()) anchorSource = resolve(target, 'README.md');
	if (!existsSync(anchorSource) || !['.md', '.mdx'].includes(extname(anchorSource).toLowerCase())) {
		failures.push(`${displayPath(sourceFile)}:${lineNumber}: cannot validate fragment in ${rawTarget}`);
		return;
	}
	if (!anchorsFor(anchorSource).has(fragment)) {
		failures.push(`${displayPath(sourceFile)}:${lineNumber}: missing fragment #${fragment} in ${displayPath(anchorSource)}`);
	}
}

for (const file of markdownFiles) {
	const lines = readFileSync(file, 'utf8').split(/\r?\n/);
	let fence = null;
	for (let index = 0; index < lines.length; index += 1) {
		const marker = lines[index].match(/^\s*(`{3,}|~{3,})/)?.[1];
		if (marker) {
			if (!fence) fence = marker[0];
			else if (marker[0] === fence) fence = null;
			continue;
		}
		if (fence) continue;
		for (const target of targetsOnLine(lines[index])) checkTarget(file, index + 1, target);
	}
}

if (failures.length) {
	console.error(`Repository documentation link check failed (${failures.length}):`);
	for (const failure of failures.slice(0, 80)) console.error(`  ${failure}`);
	if (failures.length > 80) console.error(`  ... ${failures.length - 80} more`);
	process.exit(1);
}

console.log(`OK       ${markdownFiles.length} repository Markdown files and their internal targets/fragments`);
