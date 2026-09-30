import { existsSync } from 'node:fs';
import { readFile } from 'node:fs/promises';
import { extname, resolve, sep } from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
import {
	COMMAND_KIND_AREAS,
	FORMAT_KIND_AREAS,
	KNOWN_SEARCH_AREAS,
	SEARCH_AREAS,
	SEARCH_FILTERS,
	SEARCH_VIEWS,
	SYSTEM_GROUP_AREAS,
} from '../src/lib/search-scopes.mjs';


const pagefindDirectory = resolve('dist/pagefind');
const pagefindModule = resolve(pagefindDirectory, 'pagefind.js');
const configuredBase = process.env.DOCS_BASE ?? '/OpenTS-Prepub-Scratch';
const base = configuredBase === '/' ? '' : `/${configuredBase.replace(/^\/+|\/+$/g, '')}`;
const fixturesEnabled = process.env.MANUAL_TEST_FIXTURES === '1';
const fixturePage = resolve('dist/keys/oldexample/index.html');
if (!existsSync(pagefindModule)) throw new Error('Pagefind output is missing; run npm run build first');
if (existsSync(fixturePage) !== fixturesEnabled) {
	throw new Error(fixturesEnabled
		? 'Fixture build is missing keys/oldexample/index.html'
		: 'Production build unexpectedly contains keys/oldexample/index.html');
}
for (const relative of ['systems/old-system/index.html', 'commands/old-command/index.html']) {
	const exists = existsSync(resolve('dist', relative));
	if (exists !== fixturesEnabled) {
		throw new Error(fixturesEnabled
			? `Fixture build is missing ${relative}`
			: `Production build unexpectedly contains ${relative}`);
	}
}

// Pagefind's browser bundle uses fetch(). Teach Node how to fetch the generated local
// index so the same search artifact shipped to Pages is exercised in CI.
const networkFetch = globalThis.fetch;
globalThis.fetch = async (resource, init) => {
	const raw = resource instanceof Request ? resource.url : String(resource);
	const url = new URL(raw);
	if (url.protocol !== 'file:') return networkFetch(resource, init);
	try {
		const bytes = await readFile(fileURLToPath(url));
		const type = extname(url.pathname) === '.wasm' ? 'application/wasm' : 'application/octet-stream';
		return new Response(bytes, { status: 200, headers: { 'content-type': type } });
	} catch {
		return new Response(null, { status: 404 });
	}
};

const pagefind = await import(pathToFileURL(pagefindModule).href + `?check=${Date.now()}`);
await pagefind.options({
	basePath: pathToFileURL(pagefindDirectory + sep).href,
	baseUrl: `https://local.invalid${base}`,
});
const availableFilters = await pagefind.filters();
const expectedFilterNames = Object.values(SEARCH_FILTERS).sort();
const actualFilterNames = Object.keys(availableFilters).sort();
if (JSON.stringify(actualFilterNames) !== JSON.stringify(expectedFilterNames)) {
	throw new Error(`Search filters are ${actualFilterNames.join(', ')}; expected ${expectedFilterNames.join(', ')}`);
}
const actualViews = Object.keys(availableFilters[SEARCH_FILTERS.view] ?? {}).sort();
const expectedViews = Object.values(SEARCH_VIEWS).sort();
if (JSON.stringify(actualViews) !== JSON.stringify(expectedViews)) {
	throw new Error(`View filter values are ${actualViews.join(', ')}; expected ${expectedViews.join(', ')}`);
}
const actualAreas = Object.keys(availableFilters[SEARCH_FILTERS.area] ?? {}).sort();
const unknownAreas = actualAreas.filter((area) => !KNOWN_SEARCH_AREAS.includes(area));
if (unknownAreas.length) {
	throw new Error(`Unknown Area filter values: ${unknownAreas.join(', ')}`);
}
const missingCoreAreas = Object.values(SEARCH_AREAS).filter((area) => !actualAreas.includes(area));
const missingSystemGroups = SYSTEM_GROUP_AREAS.filter((area) => !actualAreas.includes(area));
if (missingCoreAreas.length || missingSystemGroups.length) {
	throw new Error(`Required Area filter values are missing: ${[...missingCoreAreas, ...missingSystemGroups].join(', ')}`);
}
console.log(`OK       ${actualFilterNames.length} scoped search filter groups`);


const filterLabel = (filters) => filters
	? ' with ' + Object.entries(filters).map(([name, values]) => `${name}=${values.join('|')}`).join(', ')
	: '';

async function urlsFor(query, filters, limit = 25) {
	const response = await pagefind.search(query, filters ? { filters } : undefined);
	return Promise.all(response.results.slice(0, limit).map(async (result) => (await result.data()).url));
}

async function expectRoute(query, route, filters) {
	const urls = await urlsFor(query, filters);
	if (!urls.some((url) => new URL(url, 'https://local.invalid').pathname === route)) {
		throw new Error(`Search for ${JSON.stringify(query)}${filterLabel(filters)} did not find ${route}. Top results:\n  ${urls.join('\n  ')}`);
	}
	console.log(`OK       ${JSON.stringify(query)}${filterLabel(filters)} -> ${route}`);
}

async function expectNoRoute(query, route, filters) {
	const urls = await urlsFor(query, filters, Number.POSITIVE_INFINITY);
	if (urls.some((url) => new URL(url, 'https://local.invalid').pathname === route)) {
		throw new Error(`Search for ${JSON.stringify(query)}${filterLabel(filters)} unexpectedly found ${route}`);
	}
	console.log(`OK       ${JSON.stringify(query)}${filterLabel(filters)} excludes ${route}`);
}

await expectRoute('Strength', `${base}/keys/strength/`);
await expectRoute('DropPod', `${base}/keys/droppod-global-rules/`);
await expectRoute('Change House', `${base}/mapping/actions/taction-change-house/`);
await expectRoute('Action 14', `${base}/mapping/actions/taction-change-house/`);
await expectRoute('Event 34', `${base}/mapping/events/tevent-near-waypoint/`);
await expectRoute('Mission 6', `${base}/mapping/missions/tmission-loop/`);
await expectRoute('GDI Drop Pods superweapon', `${base}/systems/drop-pods/`);
await expectRoute('Target property', base + '/mapping/missions/tmission-attack-building-with-property/');
await expectRoute('OpenTS manual', base + '/changes/opents-manual/');
await expectRoute('SOUND01.INI', base + '/reference/other/');
await expectRoute('AbstractTypeClass', `${base}/internals/class-hierarchy/`);
await expectRoute('radio contact protocol', `${base}/internals/radio/`);
await expectRoute('Locomotion and piggybacking', `${base}/internals/locomotion/`);
await expectRoute('MISSION_HUNT', `${base}/reference/enums/mission/`);
await expectRoute('RTTI_VEINHOLEMONSTER', `${base}/reference/enums/rtti-type/`);
await expectRoute('developer builds', `${base}/using/project-status/`);
await expectRoute('Toggle follow state', `${base}/commands/follow/`);
await expectRoute('Command-line help', `${base}/using/command-line/help/`);
await expectRoute('CRC-indexed archive members', `${base}/formats/mix/`);
await expectRoute('RandomMap', `${base}/reference/map-seeds/`);
await expectRoute('Each TileSet section defines', `${base}/reference/theater-controls/`);
await expectNoRoute('Browse all INI keys', `${base}/keys/`);

await expectRoute('TACTION_PLAY_ANIM', `${base}/mapping/actions/taction-play-anim/`);
await expectRoute('0.1.0', `${base}/changes/opents-manual/`);
const scoped = (view, area) => ({
	[SEARCH_FILTERS.view]: [view],
	...(area ? { [SEARCH_FILTERS.area]: [area] } : {}),
});
await expectRoute('BounceAnim', `${base}/keys/bounceanim/`, scoped(SEARCH_VIEWS.reference, SEARCH_AREAS.rules));
await expectRoute('BounceAnim', `${base}/keys/bounceanim/`, scoped(SEARCH_VIEWS.reference, SEARCH_AREAS.art));
await expectRoute('Action', `${base}/keys/action/`, scoped(SEARCH_VIEWS.mapping, SEARCH_AREAS.scenario));
await expectRoute('StretchMovies', `${base}/keys/stretchmovies/`, scoped(SEARCH_VIEWS.reference, SEARCH_AREAS.other));
await expectRoute('MISSION_HUNT', `${base}/reference/enums/mission/`, scoped(SEARCH_VIEWS.reference, SEARCH_AREAS.enums));
await expectRoute('Change House', `${base}/mapping/actions/taction-change-house/`, scoped(SEARCH_VIEWS.mapping, SEARCH_AREAS.actions));
await expectRoute('GDI Drop Pods superweapon', `${base}/systems/drop-pods/`, scoped(SEARCH_VIEWS.systems, 'Superweapons & special systems'));
await expectRoute('Base placement', `${base}/systems/base-adjacency/`, scoped(SEARCH_VIEWS.systems, 'Buildings & economy'));
await expectRoute('developer builds', `${base}/using/project-status/`, scoped(SEARCH_VIEWS.using, 'Getting started'));
await expectRoute('Toggle follow state', `${base}/commands/follow/`, scoped(SEARCH_VIEWS.commands, COMMAND_KIND_AREAS.registered));
await expectRoute('Map zoom', `${base}/commands/fixed-map-zoom/`, scoped(SEARCH_VIEWS.commands, COMMAND_KIND_AREAS.fixed));
await expectRoute('Command-line help', `${base}/using/command-line/help/`, scoped(SEARCH_VIEWS.using, COMMAND_KIND_AREAS.launch));
await expectRoute('CRC-indexed archive members', `${base}/formats/mix/`, scoped(SEARCH_VIEWS.formats, FORMAT_KIND_AREAS.binary));
await expectRoute('RandomMap', `${base}/reference/map-seeds/`, scoped(SEARCH_VIEWS.reference, SEARCH_AREAS.mapSeeds));
await expectRoute('Each TileSet section defines', `${base}/reference/theater-controls/`, scoped(SEARCH_VIEWS.reference, SEARCH_AREAS.theaterControls));
await expectRoute('TeamTypes', `${base}/mapping/team-types/`, scoped(SEARCH_VIEWS.formats, FORMAT_KIND_AREAS.registry));
await expectRoute('AbstractTypeClass', `${base}/internals/class-hierarchy/`, scoped(SEARCH_VIEWS.internals));
await expectRoute('Locomotion and piggybacking', `${base}/internals/locomotion/`, scoped(SEARCH_VIEWS.internals));
await expectNoRoute('Change House', `${base}/mapping/actions/taction-change-house/`, scoped(SEARCH_VIEWS.reference));
await expectNoRoute('BounceAnim', `${base}/keys/bounceanim/`, { [SEARCH_FILTERS.area]: [SEARCH_AREAS.other] });


for (const [query, retiredRoute] of [
	['Action 14', `${base}/mapping/actions/14/`],
	['Event 34', `${base}/mapping/events/34/`],
	['Mission 6', `${base}/mapping/missions/6/`],
]) {
	const paths = (await urlsFor(query)).map((url) => new URL(url, 'https://local.invalid').pathname);
	if (paths.includes(retiredRoute)) {
		throw new Error(`Search for ${JSON.stringify(query)} indexed compatibility alias ${retiredRoute}`);
	}
}
if (fixturesEnabled) {
	await expectRoute('OldExample', `${base}/keys/oldexample/`);
	await expectRoute('OldExample', `${base}/keys/oldexample/`, scoped(SEARCH_VIEWS.reference));
	await expectRoute('OldSystem', `${base}/systems/old-system/`, scoped(SEARCH_VIEWS.systems));
	await expectRoute('OldCommand', `${base}/commands/old-command/`, scoped(SEARCH_VIEWS.commands));
} else {
	await expectNoRoute('OldExample', `${base}/keys/oldexample/`);
	await expectNoRoute('OldSystem', `${base}/systems/old-system/`);
	await expectNoRoute('OldCommand', `${base}/commands/old-command/`);
}
