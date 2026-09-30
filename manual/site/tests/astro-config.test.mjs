import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import test from 'node:test';

const source = readFileSync(new URL('../astro.config.mjs', import.meta.url), 'utf8');

test('Astro publication UI consumes consolidated demo configuration', () => {
	assert.match(source, /\.\.\.\(!siteConfig\.demo\s*\?\s*\[\{/);
	assert.doesNotMatch(source, /process\.env\.(?:DOCS_|PUBLIC_)/);
});

test('Astro navigation tolerates optional authored directories being absent', () => {
	assert.match(source, /if \(!existsSync\(directory\)\) \{\s*return \[\];/);
});
