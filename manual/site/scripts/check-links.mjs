import { existsSync, readFileSync, readdirSync, statSync } from 'node:fs';
import { join, relative, resolve, sep } from 'node:path';

const dist = resolve('dist');
const configured = process.env.DOCS_BASE ?? '/OpenTS-Prepub-Scratch';
const base = configured === '/' ? '' : `/${configured.replace(/^\/+|\/+$/g, '')}`;
if (!existsSync(dist)) throw new Error('dist/ is missing; run npm run build first');

const files = [];
const visit = (directory) => {
	for (const name of readdirSync(directory)) {
		const path = join(directory, name);
		statSync(path).isDirectory() ? visit(path) : files.push(path);
	}
};
visit(dist);

const failures = [];
const htmlFiles = files.filter((path) => path.endsWith('.html'));
const publicPath = (file) => {
	const local = relative(dist, file).split(sep).join('/');
	return '/' + (local.endsWith('/index.html') ? local.slice(0, -10) : local === 'index.html' ? '' : local);
};

function targetFor(url, sourceFile) {
	if (/^(?:[a-z]+:|#|\/\/)/i.test(url)) return null;
	const clean = url.replace(/&amp;/g, '&').split('#')[0].split('?')[0];
	if (!clean) return null;
	let route;
	if (clean.startsWith('/')) {
		if (base && clean !== base && !clean.startsWith(`${base}/`)) {
			failures.push(`${relative(dist, sourceFile)}: root URL misses Pages base: ${clean}`);
			return null;
		}
		route = base ? clean.slice(base.length) || '/' : clean;
	} else {
		const sourceRoute = publicPath(sourceFile);
		route = new URL(clean, `https://local.invalid${sourceRoute}`).pathname;
	}
	route = decodeURIComponent(route);
	const local = route.replace(/^\//, '');
	if (!local) return join(dist, 'index.html');
	if (route.endsWith('/')) return join(dist, local, 'index.html');
	const direct = join(dist, local);
	if (existsSync(direct)) return direct;
	return join(dist, local, 'index.html');
}

for (const file of htmlFiles) {
	const html = readFileSync(file, 'utf8');
	const links = [...html.matchAll(/\b(?:href|src)=["']([^"']+)["']/gi)].map((match) => match[1]);
	for (const link of links) {
		const target = targetFor(link, file);
		if (target && !existsSync(target)) failures.push(`${relative(dist, file)} -> ${link}`);
	}
	for (const match of html.matchAll(/\bsrcset=["']([^"']+)["']/gi)) {
		for (const item of match[1].split(',').map((part) => part.trim().split(/\s+/)[0])) {
			const target = targetFor(item, file);
			if (target && !existsSync(target)) failures.push(`${relative(dist, file)} -> ${item}`);
		}
	}
}

if (failures.length) {
	console.error(`Internal link check failed (${failures.length}):`);
	for (const failure of failures.slice(0, 80)) console.error(`  ${failure}`);
	if (failures.length > 80) console.error(`  … ${failures.length - 80} more`);
	process.exit(1);
}
console.log(`OK       ${htmlFiles.length} HTML pages and their internal links/assets`);
console.log(`OK       every root-relative URL uses ${base || '/'} as its deployment base`);
