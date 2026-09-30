import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { dirname, resolve } from 'node:path';
import test from 'node:test';
import { fileURLToPath } from 'node:url';
import { load } from 'js-yaml';
import { slugify } from '../src/lib/reference.mjs';

const site = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const repository = resolve(site, '../..');
const readRepositoryFile = (path) => readFileSync(resolve(repository, path), 'utf8');

test('authored H3 headings use the shared subordinate scale and color', () => {
	const css = readRepositoryFile('manual/site/src/styles/custom.css');
	assert.match(css, /:root\s*{[^}]*--sl-text-h3:\s*1\.375rem;/s);
	assert.match(
		css,
		/@media\s*\(min-width:\s*50em\)\s*{\s*:root\s*{[^}]*--sl-text-h3:\s*1\.625rem;/s,
	);
	assert.match(
		css,
		/\.sl-markdown-content\s+\.sl-heading-wrapper\.level-h3\s*>\s*h3\s*{[^}]*color:\s*var\(--ots-ink\);/s,
	);
});

test('Image keeps four ordered public scopes and stable fragment identities', () => {
	const keys = load(readRepositoryFile('manual/data/ini-keys.yaml'));
	const scopes = keys.Image?.scopes;
	assert.ok(scopes, 'Image is missing from the generated INI catalog');
	/* Published #scope- fragments are addressed by each scope's leading type and are
	   handed out in order, so this list is a route-stability contract rather than a
	   copy of the extraction. What each scope reads is settled against the engine in
	   the Python object-type tests; what a reader can link to is settled here. */
	assert.deepEqual(scopes.map((scope) => slugify(scope.applies_to[0])), [
		'aircrafttype',
		'animtype',
		'tiberium',
		'buildingtype',
	]);
	assert.ok(scopes.every((scope) => !scope.applies_to.includes('IsometricTileType')));
});
