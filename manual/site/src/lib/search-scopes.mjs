// @ts-check

import { UI } from '../i18n/en.mjs';
import { REFERENCE_PAGES } from './reference.mjs';

export const SEARCH_FILTERS = Object.freeze({
	view: UI.search.filterGroups.view,
	area: UI.search.filterGroups.area,
});

export const SEARCH_VIEWS = Object.freeze({
	start: UI.navigation.start,
	using: UI.navigation.using,
	systems: UI.navigation.systems,
	reference: UI.navigation.reference,
	guides: UI.navigation.guides,
	mapping: UI.navigation.mapping,
	commands: UI.navigation.commands,
	formats: UI.navigation.formats,
	internals: UI.navigation.internals,
	changes: UI.navigation.changes,
});

export const SEARCH_AREAS = Object.freeze({
	rules: REFERENCE_PAGES.rules.title,
	art: REFERENCE_PAGES.art.title,
	other: REFERENCE_PAGES.other.title,
	enums: UI.navigation.enums,
	mapSeeds: UI.navigation.mapSeeds,
	theaterControls: UI.navigation.theaterControls,
	scenario: UI.navigation.scenario,
	actions: UI.navigation.actions,
	events: UI.navigation.events,
	missions: UI.navigation.missions,
	teamTypes: UI.navigation.teamTypes,
	taskForces: UI.navigation.taskForces,
	scripts: UI.navigation.scripts,
	aiTriggers: UI.navigation.aiTriggers,
});

export const COMMAND_KIND_AREAS = Object.freeze(UI.commandKindAreas);
export const COMMAND_AUDIENCE_AREAS = Object.freeze(UI.commandAudiences);
export const FORMAT_KIND_AREAS = Object.freeze(
	Object.fromEntries(UI.formatKinds.map((kind) => [kind.id, kind.title])),
);

export const SYSTEM_GROUP_AREAS = Object.freeze(UI.systemGroups.map((group) => group.title));

export const KNOWN_SEARCH_AREAS = Object.freeze([...new Set([
	...Object.values(SEARCH_AREAS),
	...SYSTEM_GROUP_AREAS,
	...UI.systemCategories.map((category) => category.title),
	...UI.guideCategories.map((category) => category.title),
	...UI.usingCategories.map((category) => category.title),
	...UI.internalCategories.map((category) => category.title),
	...Object.values(COMMAND_KIND_AREAS),
	...Object.values(COMMAND_AUDIENCE_AREAS),
	...Object.values(FORMAT_KIND_AREAS),
])]);

/** @param {string} pathname @param {string} [base] */
export function logicalSearchPath(pathname, base = '') {
	const rooted = pathname.startsWith('/') ? pathname : `/${pathname}`;
	const normalizedBase = base === '/'
		? ''
		: `/${base.replace(/^\/+|\/+$/g, '')}`;
	if (normalizedBase && (rooted === normalizedBase || rooted.startsWith(`${normalizedBase}/`))) {
		return rooted.slice(normalizedBase.length) || '/';
	}
	return rooted;
}

/** @param {string} pathname @param {string} route */
const isWithin = (pathname, route) =>
	pathname === route.replace(/\/$/, '') || pathname.startsWith(route);

/** @param {Array<{id: string, title: string}>} rows @param {string | undefined} id */
const taxonomyTitle = (rows, id) => rows.find((row) => row.id === id)?.title;

const referenceAreaRoutes = [
	['/reference/rules/', SEARCH_AREAS.rules],
	['/reference/art/', SEARCH_AREAS.art],
	['/reference/other/', SEARCH_AREAS.other],
	['/reference/enums/', SEARCH_AREAS.enums],
	['/reference/map-seeds/', SEARCH_AREAS.mapSeeds],
	['/reference/theater-controls/', SEARCH_AREAS.theaterControls],
];

const mappingAreaRoutes = [
	['/mapping/scenario/', SEARCH_AREAS.scenario],
	['/mapping/actions/', SEARCH_AREAS.actions],
	['/mapping/events/', SEARCH_AREAS.events],
	['/mapping/missions/', SEARCH_AREAS.missions],
	['/mapping/team-types/', SEARCH_AREAS.teamTypes],
	['/mapping/task-forces/', SEARCH_AREAS.taskForces],
	['/mapping/scripts/', SEARCH_AREAS.scripts],
	['/mapping/ai-triggers/', SEARCH_AREAS.aiTriggers],
];

/**
 * Classify one rendered route for Pagefind's user-facing filters.
 * Taxonomy options are supplied from the route's validated content record, so
 * empty categories never become filter values.
 *
 * @param {string} pathname
 * @param {{
 *   base?: string,
 *   keyFamilies?: string[],
 *   systemCategory?: string,
 *   guideCategory?: string,
 *   usingCategory?: string,
 *   commandKind?: 'registered' | 'fixed' | 'launch',
 *   commandAudience?: 'player' | 'developer' | 'debug',
 *   formatKind?: 'syntax' | 'file' | 'registry' | 'record' | 'binary',
 *   internalCategory?: string,
 * }} [options]
 */
export function searchScopesForPath(pathname, options = {}) {
	const path = logicalSearchPath(pathname, options.base);
	const views = new Set();
	const areas = new Set();

	if (isWithin(path, '/using/')) {
		views.add(SEARCH_VIEWS.using);
		const category = taxonomyTitle(UI.usingCategories, options.usingCategory);
		if (category) areas.add(category);
		if (isWithin(path, '/using/command-line/')) {
			areas.add(COMMAND_KIND_AREAS.launch);
			if (options.commandAudience) areas.add(COMMAND_AUDIENCE_AREAS[options.commandAudience]);
		}
	} else if (isWithin(path, '/systems/')) {
		views.add(SEARCH_VIEWS.systems);
		const systemCategory = options.systemCategory;
		const category = taxonomyTitle(UI.systemCategories, systemCategory);
		const group = systemCategory ? UI.systemGroups.find((candidate) => candidate.categories.includes(systemCategory)) : undefined;
		if (group) areas.add(group.title);
		if (category) areas.add(category);
		if (!systemCategory && (path === '/systems' || path === '/systems/')) {
			for (const groupArea of SYSTEM_GROUP_AREAS) areas.add(groupArea);
		}
	} else if (isWithin(path, '/commands/')) {
		views.add(SEARCH_VIEWS.commands);
		if (options.commandKind) areas.add(COMMAND_KIND_AREAS[options.commandKind]);
		else if (isWithin(path, '/commands/fixed-controls/')) areas.add(COMMAND_KIND_AREAS.fixed);
		else if (path === '/commands' || path === '/commands/') areas.add(COMMAND_KIND_AREAS.registered);
		if (options.commandAudience) areas.add(COMMAND_AUDIENCE_AREAS[options.commandAudience]);
	} else if (isWithin(path, '/formats/')) {
		views.add(SEARCH_VIEWS.formats);
		if (options.formatKind) areas.add(FORMAT_KIND_AREAS[options.formatKind]);
	} else if (isWithin(path, '/reference/') || isWithin(path, '/keys/')) {
		views.add(SEARCH_VIEWS.reference);
		for (const [route, area] of referenceAreaRoutes) {
			if (isWithin(path, route)) areas.add(area);
		}

		if (isWithin(path, '/keys/')) {
			const families = new Set(options.keyFamilies ?? []);
			if (families.has('rules')) areas.add(SEARCH_AREAS.rules);
			if (families.has('art')) areas.add(SEARCH_AREAS.art);
			if (families.has('other')) areas.add(SEARCH_AREAS.other);
			if (families.has('map-seeds')) areas.add(SEARCH_AREAS.mapSeeds);
			if (families.has('theater-controls')) areas.add(SEARCH_AREAS.theaterControls);
			if (families.has('mapping')) {
				views.add(SEARCH_VIEWS.mapping);
				areas.add(SEARCH_AREAS.scenario);
			}
		}
	} else if (isWithin(path, '/guides/')) {
		views.add(SEARCH_VIEWS.guides);
		const category = taxonomyTitle(UI.guideCategories, options.guideCategory);
		if (category) areas.add(category);
	} else if (isWithin(path, '/mapping/')) {
		views.add(SEARCH_VIEWS.mapping);
		for (const [route, area] of mappingAreaRoutes) {
			if (isWithin(path, route)) areas.add(area);
		}
		if (options.formatKind) {
			views.add(SEARCH_VIEWS.formats);
			areas.add(FORMAT_KIND_AREAS[options.formatKind]);
		}
	} else if (isWithin(path, '/internals/')) {
		views.add(SEARCH_VIEWS.internals);
		const category = taxonomyTitle(UI.internalCategories, options.internalCategory);
		if (category) areas.add(category);
	} else if (isWithin(path, '/changes/')) {
		views.add(SEARCH_VIEWS.changes);
	} else {
		views.add(SEARCH_VIEWS.start);
	}

	return { views: [...views], areas: [...areas] };
}