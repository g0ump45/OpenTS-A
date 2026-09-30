import assert from 'node:assert/strict';
import test from 'node:test';
import {
	COMMAND_AUDIENCE_AREAS,
	COMMAND_KIND_AREAS,
	FORMAT_KIND_AREAS,
	logicalSearchPath,
	SEARCH_AREAS,
	SEARCH_VIEWS,
	SYSTEM_GROUP_AREAS,
	searchScopesForPath,
} from '../src/lib/search-scopes.mjs';

const scopes = (pathname, options) => searchScopesForPath(pathname, options);

test('search scope paths normalize every supported deployment base', () => {
	assert.equal(logicalSearchPath('/OpenTS-Prepub-Scratch/mapping/actions/', '/OpenTS-Prepub-Scratch/'), '/mapping/actions/');
	assert.equal(logicalSearchPath('/Docs-Demo/', '/Docs-Demo/'), '/');
	assert.equal(logicalSearchPath('/mapping/actions/', '/'), '/mapping/actions/');
});

test('search views follow the manual view selector', () => {
	for (const [path, view] of [
		['/', SEARCH_VIEWS.start],
		['/how-to-read/', SEARCH_VIEWS.start],
		['/using/', SEARCH_VIEWS.using],
		['/reference/', SEARCH_VIEWS.reference],
		['/guides/', SEARCH_VIEWS.guides],
		['/mapping/', SEARCH_VIEWS.mapping],
		['/formats/', SEARCH_VIEWS.formats],
		['/internals/', SEARCH_VIEWS.internals],
		['/changes/', SEARCH_VIEWS.changes],
	]) {
		assert.deepEqual(scopes(path), { views: [view], areas: [] }, path);
	}
	assert.deepEqual(scopes('/systems/'), {
		views: [SEARCH_VIEWS.systems],
		areas: [...SYSTEM_GROUP_AREAS],
	});
	assert.deepEqual(scopes('/commands/'), {
		views: [SEARCH_VIEWS.commands],
		areas: [COMMAND_KIND_AREAS.registered],
	});
	assert.deepEqual(scopes('/commands/fixed-controls/'), {
		views: [SEARCH_VIEWS.commands],
		areas: [COMMAND_KIND_AREAS.fixed],
	});
	assert.deepEqual(scopes('/using/command-line/'), {
		views: [SEARCH_VIEWS.using],
		areas: [COMMAND_KIND_AREAS.launch],
	});
	assert.deepEqual(scopes('/unclassified/'), { views: [SEARCH_VIEWS.start], areas: [] });
});

test('reference and mapping routes receive their detailed areas', () => {
	const cases = [
		['/reference/rules/buildingtype/', SEARCH_VIEWS.reference, SEARCH_AREAS.rules],
		['/reference/art/buildingtype/', SEARCH_VIEWS.reference, SEARCH_AREAS.art],
		['/reference/other/options/', SEARCH_VIEWS.reference, SEARCH_AREAS.other],
		['/reference/enums/mission/', SEARCH_VIEWS.reference, SEARCH_AREAS.enums],
		['/reference/map-seeds/', SEARCH_VIEWS.reference, SEARCH_AREAS.mapSeeds],
		['/reference/theater-controls/', SEARCH_VIEWS.reference, SEARCH_AREAS.theaterControls],
		['/mapping/scenario/basic/', SEARCH_VIEWS.mapping, SEARCH_AREAS.scenario],
		['/mapping/actions/taction-change-house/', SEARCH_VIEWS.mapping, SEARCH_AREAS.actions],
		['/mapping/events/tevent-near-waypoint/', SEARCH_VIEWS.mapping, SEARCH_AREAS.events],
		['/mapping/missions/tmission-loop/', SEARCH_VIEWS.mapping, SEARCH_AREAS.missions],
		['/mapping/team-types/', SEARCH_VIEWS.mapping, SEARCH_AREAS.teamTypes],
		['/mapping/task-forces/', SEARCH_VIEWS.mapping, SEARCH_AREAS.taskForces],
		['/mapping/scripts/', SEARCH_VIEWS.mapping, SEARCH_AREAS.scripts],
		['/mapping/ai-triggers/', SEARCH_VIEWS.mapping, SEARCH_AREAS.aiTriggers],
	];
	for (const [path, view, area] of cases) {
		assert.deepEqual(scopes(path), { views: [view], areas: [area] }, path);
	}
});

test('canonical key pages retain every applicable family', () => {
	assert.deepEqual(scopes('/keys/bounceanim/', { keyFamilies: ['art', 'rules', 'art'] }), {
		views: [SEARCH_VIEWS.reference],
		areas: [SEARCH_AREAS.rules, SEARCH_AREAS.art],
	});
	assert.deepEqual(scopes('/keys/action/', { keyFamilies: ['mapping', 'rules'] }), {
		views: [SEARCH_VIEWS.reference, SEARCH_VIEWS.mapping],
		areas: [SEARCH_AREAS.rules, SEARCH_AREAS.scenario],
	});
	assert.deepEqual(scopes('/keys/mapseed/', { keyFamilies: ['map-seeds', 'theater-controls'] }), {
		views: [SEARCH_VIEWS.reference],
		areas: [SEARCH_AREAS.mapSeeds, SEARCH_AREAS.theaterControls],
	});
	assert.deepEqual(scopes('/keys/oldexample/'), {
		views: [SEARCH_VIEWS.reference],
		areas: [],
	});
});

test('content taxonomies add only the populated route categories', () => {
	assert.deepEqual(scopes('/systems/drop-pods/', { systemCategory: 'superweapons-special' }), {
		views: [SEARCH_VIEWS.systems],
		areas: ['Combat & weapons', 'Superweapons & special systems'],
	});
	assert.deepEqual(scopes('/guides/example-guide/', { guideCategory: 'troubleshooting' }), {
		views: [SEARCH_VIEWS.guides],
		areas: ['Troubleshooting'],
	});
	assert.deepEqual(scopes('/using/project-status/', { usingCategory: 'getting-started' }), {
		views: [SEARCH_VIEWS.using],
		areas: ['Getting started'],
	});
	assert.deepEqual(scopes('/internals/locomotion/', { internalCategory: 'simulation-systems' }), {
		views: [SEARCH_VIEWS.internals],
		areas: ['Simulation systems'],
	});
});

test('commands and formats expose kind, audience, and compatibility views', () => {
	assert.deepEqual(scopes('/commands/follow/', { commandKind: 'registered', commandAudience: 'player' }), {
		views: [SEARCH_VIEWS.commands],
		areas: [COMMAND_KIND_AREAS.registered, COMMAND_AUDIENCE_AREAS.player],
	});
	assert.deepEqual(scopes('/using/command-line/help/', { commandKind: 'launch', commandAudience: 'developer' }), {
		views: [SEARCH_VIEWS.using],
		areas: [COMMAND_KIND_AREAS.launch, COMMAND_AUDIENCE_AREAS.developer],
	});
	assert.deepEqual(scopes('/formats/mix/', { formatKind: 'binary' }), {
		views: [SEARCH_VIEWS.formats],
		areas: [FORMAT_KIND_AREAS.binary],
	});
	assert.deepEqual(scopes('/mapping/team-types/', { formatKind: 'registry' }), {
		views: [SEARCH_VIEWS.mapping, SEARCH_VIEWS.formats],
		areas: [SEARCH_AREAS.teamTypes, FORMAT_KIND_AREAS.registry],
	});
});
