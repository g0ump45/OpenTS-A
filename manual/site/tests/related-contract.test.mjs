import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { dirname, resolve } from 'node:path';
import test from 'node:test';
import { fileURLToPath } from 'node:url';
import { relatedIdentity, referenceTargets } from '../src/lib/related-identity.mjs';

const site = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const readSite = (relative) => readFileSync(resolve(site, relative), 'utf8');

test('unscoped key targets collect scoped and key-wide references', () => {
	const keyWide = { type: 'key', id: 'Strength' };
	const aircraft = { type: 'key', id: 'Strength', scope: 'aircrafttype' };
	const overlay = { type: 'key', id: 'Strength', scope: 'overlaytype' };

	assert.equal(referenceTargets(keyWide, keyWide), true);
	assert.equal(referenceTargets(aircraft, keyWide), true);
	assert.equal(referenceTargets(overlay, keyWide), true);
	assert.equal(referenceTargets(aircraft, aircraft), true);
	assert.equal(referenceTargets(overlay, aircraft), false);
	assert.equal(referenceTargets(keyWide, aircraft), false);
});

test('relation identities retain key scopes for validation and labels', () => {
	assert.equal(relatedIdentity({ type: 'key', id: 'Strength' }), 'key:Strength:');
	assert.equal(
		relatedIdentity({ type: 'key', id: 'Strength', scope: 'overlaytype' }),
		'key:Strength:overlaytype',
	);
});


test('system and command detail routes include active history and removed identities', () => {
	const system = readSite('src/pages/systems/[id].astro');
	const command = readSite('src/pages/commands/[id].astro')
		+ readSite('src/pages/using/command-line/[id].astro')
		+ readSite('src/components/CommandPage.astro');
	const change = readSite('src/pages/changes/[change].astro');
	const changeIndex = readSite('src/pages/changes/index.astro');
	const lifecycle = readSite('src/components/LifecycleHistory.astro');
	const styles = readSite('src/styles/custom.css');

	assert.match(system, /record\.type === 'system'/);
	assert.match(system, /LifecycleHistory reference=\{\{ type: 'system'/);
	assert.match(system, /page\.rows\.length > 0/);
	assert.equal(system.includes(['active', '!'].join('')), false);
	assert.match(command, /record\.type === 'command'/);
	assert.match(command, /LifecycleHistory reference=\{\{ type: 'command'/);
	assert.match(change, /entry\.data\.migration\.map/);
	assert.match(changeIndex, /Upgrade to \{release\.version\}/);
	const emDash = String.fromCodePoint(0x2014);
	assert.equal(lifecycle.includes(`' ${emDash} '`), true);
	for (const mojibake of [
		String.fromCodePoint(0x0432, 0x0402),
		String.fromCodePoint(0x00e2, 0x20ac),
		String.fromCodePoint(0xfffd),
	]) {
		assert.equal(lifecycle.includes(mojibake), false, `lifecycle mojibake remains: ${JSON.stringify(mojibake)}`);
	}
	const lifecyclePresentation = `${lifecycle}\n${change}\n${styles}`;
	for (const suffix of ['dead', 'since', 'complete']) {
		const retired = `ots-badge-${suffix}`;
		assert.equal(lifecyclePresentation.includes(retired), false, `retired class remains: ${retired}`);
	}
	for (const semantic of ['ots-badge-removed', 'ots-badge-change', 'ots-badge-release', 'ots-badge-breaking']) {
		assert.equal(lifecyclePresentation.includes(semantic), true, `semantic class is missing: ${semantic}`);
	}
});
