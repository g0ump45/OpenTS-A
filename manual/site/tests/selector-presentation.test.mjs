import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import test from 'node:test';

const read = (relative) => readFileSync(new URL(relative, import.meta.url), 'utf8');

test('Starlight processes authored content outside the site content directory', () => {
	const config = read('../astro.config.mjs');
	assert.match(
		config,
		/markdown:\s*\{\s*processedDirs:\s*\['\.\.\/content', '\.\.\/changes'\],?\s*\}/,
	);
});

test('reference grouping consumes selector objects without English-prefix inference', () => {
	const reference = read('../src/lib/reference.mjs');
	assert.match(reference, /requireSectionSelector\(scope\.section/);
	assert.match(reference, /sectionSelectorKey\(selector\)/);
	assert.match(reference, /isImageSection\(selector\)/);
	assert.doesNotMatch(reference, /startsWith\(['"]the entry named by/);
	assert.doesNotMatch(reference, /startsWith\(['"]\[/);
	for (const phrase of [
		"the object's own entry",
		"the entry named by this object's Image=",
		"the campaign's own entry",
		"the sound's own entry",
		"the theme's own entry",
	]) {
		assert.doesNotMatch(reference, new RegExp(phrase.replace(/[.*+?^${}()|[\]\\]/g, '\\$&')));
	}
});

test('shared detail presentation uses Section selectors and has no review placeholder', () => {
	const spec = read('../src/components/SpecBlock.astro');
	const scripting = read('../src/components/ScriptingDetail.astro');
	const ui = read('../src/i18n/en.mjs');
	assert.match(spec, /UI\.specification\.section/);
	assert.match(spec, /<SectionSelector selector=\{scope\.section\} explainImage \/>/);
	assert.match(spec, /<SectionSelector selector=\{read\.section\} explainImage \/>/);
	assert.doesNotMatch(spec, /Loaded through|entry_source|directEntry|imageEntry/);
	assert.doesNotMatch(scripting, /Behavioral explanation wanted|traced, reviewed explanation/);
	assert.doesNotMatch(ui, /Help improve this page|Browse the manual|What's new/);
});
