import assert from 'node:assert/strict';
import { existsSync, readFileSync, readdirSync } from 'node:fs';
import { dirname, resolve } from 'node:path';
import test from 'node:test';
import { fileURLToPath } from 'node:url';
import Ajv2020 from 'ajv/dist/2020.js';
import { load } from 'js-yaml';

const site = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const manual = resolve(site, '..');
const repository = resolve(manual, '..');
const readManual = (path) => readFileSync(resolve(manual, path), 'utf8');
const frontmatter = (source, context) => {
	const match = source.match(/^---\r?\n([\s\S]*?)\r?\n---/);
	assert.ok(match, `${context}: missing frontmatter`);
	return load(match[1]);
};
const formatDirectory = resolve(manual, 'content/formats');
const formats = readdirSync(formatDirectory)
	.filter((name) => name.endsWith('.md'))
	.map((name) => ({
		slug: name.replace(/\.md$/, ''),
		source: readFileSync(resolve(formatDirectory, name), 'utf8'),
		...frontmatter(readFileSync(resolve(formatDirectory, name), 'utf8'), name),
	}));
const routeFor = (format) => format.route ?? `/formats/${format.slug}/`;
const keys = load(readManual('data/ini-keys.yaml'));
const sameSelector = (left, right) => JSON.stringify(left) === JSON.stringify(right);
const scopeMatches = (scope, query) =>
	(!query.file || scope.file === query.file)
	&& (!query.section || sameSelector(scope.section, query.section))
	&& (!query.applies_to || scope.applies_to.includes(query.applies_to));
const acceptedKeys = (format) => Object.entries(keys).flatMap(([key, record]) =>
	record.scopes.filter((scope) => (format.key_scopes ?? []).some((query) => scopeMatches(scope, query)))
		.map((scope) => ({ key, scope })));

test('every authored format satisfies the canonical five-variant contract', () => {
	const schema = JSON.parse(readManual('schema/authored-format.schema.json'));
	const validate = new Ajv2020({ allErrors: true, strict: true }).compile(schema);
	assert.ok(formats.length > 0);
	for (const format of formats) {
		const { slug: _slug, source: _source, ...document } = format;
		assert.equal(validate(document), true, `${format.slug}: ${JSON.stringify(validate.errors)}`);
		assert.equal(routeFor(format).split('/').filter(Boolean).at(-1), format.slug);
		for (const source of format.source_files) {
			assert.equal(existsSync(resolve(repository, source)), true, `${format.slug}: missing ${source}`);
		}
	}
	assert.deepEqual(new Set(formats.map((format) => format.kind)),
		new Set(['syntax', 'file', 'registry', 'record', 'binary']));
	assert.equal(new Set(formats.map((format) => format.format_id)).size, formats.length);
	assert.equal(new Set(formats.map(routeFor)).size, formats.length);
});

test('registration definitions are exactly one section or value', () => {
	const schema = JSON.parse(readManual('schema/authored-format.schema.json'));
	const validate = new Ajv2020({ allErrors: true, strict: true }).compile(schema);
	const base = {
		format_id: 'example', title: 'Example', summary: 'Defines an example registry.',
		kind: 'registry', files: ['rules.ini'], source_files: ['code/example.cpp'],
	};
	const section = { section: 'BuildingTypes', id_from: 'value', entry_section: '<BuildingType ID>' };
	const value = { section: 'Sides', id_from: 'key', value: 'HouseType ID list' };
	assert.equal(validate({ ...base, registrations: [section] }), true);
	assert.equal(validate({ ...base, registrations: [value] }), true);
	assert.equal(validate({ ...base, registrations: [{ ...section, ...value }] }), false);
	assert.equal(validate({ ...base, registrations: [{ section: 'Sides', id_from: 'key' }] }), false);
});

test('legacy AI format identities retain their published Mapping routes', () => {
	const byId = Object.fromEntries(formats.map((format) => [format.format_id, format]));
	assert.equal(routeFor(byId.teamtypes), '/mapping/team-types/');
	assert.equal(routeFor(byId.taskforces), '/mapping/task-forces/');
	assert.equal(routeFor(byId.scripts), '/mapping/scripts/');
	assert.equal(routeFor(byId.ai_triggers), '/mapping/ai-triggers/');
	for (const id of ['teamtypes', 'taskforces', 'scripts', 'ai_triggers']) {
		assert.equal(routeFor(byId[id]).startsWith('/formats/'), false);
	}
});

test('accepted-setting tables are derived from generated file, section, and applicability selectors', () => {
	const byId = Object.fromEntries(formats.map((format) => [format.format_id, format]));
	const mapSeed = acceptedKeys(byId['map-seed']);
	const theater = acceptedKeys(byId['theater-control']);
	/* "Derived from the selectors" means the queries reach every scope the file holds,
	   which the file's own scope total states without either side naming a number. */
	const scopesInFile = (file) => Object.values(keys)
		.flatMap((record) => record.scopes)
		.filter((scope) => scope.file === file);
	assert.ok(mapSeed.length > 0);
	assert.ok(theater.length > 0);
	assert.equal(mapSeed.length, scopesInFile('map seed file').length);
	assert.equal(theater.length, scopesInFile('theater control file').length);
	assert.deepEqual(new Set(mapSeed.map(({ scope }) => scope.file)), new Set(['map seed file']));
	assert.deepEqual(new Set(theater.map(({ scope }) => scope.file)), new Set(['theater control file']));
	assert.deepEqual(new Set(theater.map(({ scope }) => scope.section.kind)), new Set(['literal', 'identifier']));
});

test('binary roles and companions use closed, resolvable identities', () => {
	const byId = new Map(formats.map((format) => [format.format_id, format]));
	const roles = new Set(['archive', 'image', 'model', 'audio', 'video', 'persistence']);
	const binary = formats.filter((format) => format.kind === 'binary');
	assert.deepEqual(new Set(binary.map((format) => format.role)), roles);
	for (const format of binary) {
		for (const companion of format.companion_formats ?? []) {
			assert.ok(byId.has(companion), `${format.format_id}: missing companion ${companion}`);
			assert.notEqual(companion, format.format_id);
		}
	}
});

test('format rendering owns structure while generated scopes own accepted settings', () => {
	const page = readManual('site/src/components/FormatPage.astro');
	const table = readManual('site/src/components/FormatKeyTable.astro');
	const mapping = readManual('site/src/pages/mapping/[kind]/index.astro');
	assert.match(page, /<FormatSpec format=\{format\}/);
	assert.match(readManual('site/src/components/FormatSpec.astro'), /<th>Definition<\/th>/);
	assert.match(readManual('site/src/components/FormatSpec.astro'), /registration\.entry_section \? section/);
	assert.match(page, /<FormatKeyTable format=\{format\}/);
	assert.match(table, /formatKeyMatches\(format, allKeys\(\)\)/);
	assert.match(mapping, /<FormatPage entry=\{format\}/);
	assert.doesNotMatch(mapping, /positionalFormats/);
	assert.doesNotMatch(formats.find((format) => format.format_id === 'ini-syntax').source,
		/include directives|section inheritance/i);
});
