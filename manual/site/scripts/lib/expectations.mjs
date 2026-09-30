/* Expectations rebuilt from authored content and navigation configuration.

   These reproduce what the site should render from the same inputs it renders
   from, by a separate implementation. A page that never reaches the tree, a
   category that keeps a heading after losing its last page, or an ordering that
   stops following titles still fails; adding a page does not. */

import { UI } from '../../src/i18n/en.mjs';
import { readChanges, readCollection, readDataYaml } from './content-sources.mjs';

const byTitleThenId = (left, right) =>
	left.title.localeCompare(right.title) || left.id.localeCompare(right.id);

/* Authored text reaches the page escaped, so an expectation taken from the
   source has to be escaped the same way before it is looked for in the HTML.
   An apostrophe is the one that bites: it renders as &#39; and nothing else
   about the title changes. */
export function escapeHtml(text) {
	return String(text)
		.replace(/&/g, '&amp;')
		.replace(/</g, '&lt;')
		.replace(/>/g, '&gt;')
		.replace(/"/g, '&quot;')
		.replace(/'/g, '&#39;');
}

/** The Features & systems tree: overview, then populated groups and categories. */
export function systemNavigation(base) {
	const systems = readCollection('systems').sort(byTitleThenId);
	if (!systems.length) throw new Error('No system pages were read from content/systems');
	const categories = new Map(UI.systemCategories.map((category) => [category.id, category]));
	const rows = [['overview', 'overview', `${base}/systems/`]];
	for (const group of UI.systemGroups) {
		const populated = group.categories.map((id) => {
			if (!categories.has(id)) throw new Error(`System group ${group.id} names unknown category ${id}`);
			return { id, entries: systems.filter((system) => system.category === id) };
		}).filter((category) => category.entries.length > 0);
		if (populated.length === 0) continue;
		rows.push(['group', group.id, `${base}/systems/#${group.id}`]);
		for (const category of populated) {
			rows.push(['category', category.id, `${base}/systems/#category-${category.id}`]);
			for (const entry of category.entries) {
				rows.push(['system', entry.id, `${base}/systems/${entry.id}/`]);
			}
		}
	}
	const classified = new Set(rows.filter(([kind]) => kind === 'system').map(([, id]) => id));
	const stray = systems.find((system) => !classified.has(system.id));
	if (stray) throw new Error(`content/systems/${stray.id}.md is in no rendered category`);
	return rows;
}

/** Group and category anchors the systems hub must offer the tree. */
export function systemHubAnchors(base) {
	return systemNavigation(base)
		.filter(([kind]) => kind !== 'system')
		.map(([kind, id]) => (kind === 'overview' ? null : `id="${kind === 'group' ? id : `category-${id}`}"`))
		.filter(Boolean);
}

/** Prose navigation ordered by title, matching proseEntries in astro.config.mjs. */
export function proseNavigation(collection, prefix, base) {
	return [
		`${base}${prefix}/`,
		...readCollection(collection).sort(byTitleThenId)
			.map((entry) => `${base}${entry.route ?? `${prefix}/${entry.id}`}/`),
	];
}

/**
 * Formats navigation grouped by kind, matching proseGroups in
 * astro.config.mjs: the taxonomy's own order, titles inside each group, and no
 * heading for a kind nothing carries. Returns the ordered needles the sidebar
 * must show, so a page under the wrong heading fails on order alone.
 */
export function formatNavigation(base) {
	const formats = readCollection('formats');
	if (!formats.length) throw new Error('No format pages were read from content/formats');
	const needles = [`href="${base}/formats/"`];
	const placed = new Set();
	for (const kind of UI.formatKinds) {
		const entries = formats.filter((entry) => entry.kind === kind.id).sort(byTitleThenId);
		if (!entries.length) continue;
		needles.push(`>${escapeHtml(kind.title)}</span>`);
		for (const entry of entries) {
			// An authored route already ends in a slash; a derived one does not.
			const route = (entry.route ?? `/formats/${entry.id}`).replace(/\/$/, '');
			needles.push(`href="${base}${route}/"`);
			placed.add(entry.id);
		}
	}
	const stray = formats.find((entry) => !placed.has(entry.id));
	if (stray) throw new Error(`content/formats/${stray.id}.md is under no rendered kind`);
	return needles;
}

/** Per-release copy on the changes index, including the count and its plural. */
export function releaseExpectations(base) {
	const changes = readChanges();
	return readDataYaml('releases.yaml').releases.map((release) => {
		const items = changes.filter((change) => change.release === release.version);
		return {
			version: release.version,
			status: release.status,
			count: `${items.length} ${items.length === 1 ? 'change' : 'changes'}`,
			anchor: `release-${release.version}`,
			upgradeHref: `href="${base}/changes/${release.version}/"`,
			titles: items.map((item) => item.title),
			// One credit line per record, names joined: a record naming two people
			// renders "by A, B", so neither name stands on its own behind "by".
			credits: [...new Set(items
				.filter((item) => item.credit?.length)
				.map((item) => `by ${item.credit.join(', ')}`))],
			breaking: items.filter((item) => item.breaking),
		};
	});
}

export function developmentRelease(base) {
	const rows = releaseExpectations(base);
	const development = rows.find((release) => release.status === 'development');
	if (!development) throw new Error('data/releases.yaml declares no release in development');
	return development;
}

/* A page reaching the head without its taxonomy record drops silently out of
   its search filter, so every page carrying one is checked rather than a few. */
export function taxonomyContracts(collection, prefix, categories, view) {
	const escape = escapeHtml;
	const labels = new Map(categories.map((category) => [category.id, category.title]));
	return readCollection(collection).map((entry) => {
		const label = labels.get(entry.category);
		if (!label) {
			throw new Error(`content/${collection}/${entry.id}.md names unknown category ${entry.category}`);
		}
		const areas = [label];
		if (collection === 'systems') {
			const group = UI.systemGroups.find((candidate) => candidate.categories.includes(entry.category));
			if (!group) throw new Error(`System category ${entry.category} belongs to no group`);
			areas.push(group.title);
		}
		return [
			`${prefix}/${entry.id}/index.html`,
			[...areas.map((area) => `Topic:${escape(area)}`), `Part of the manual:${escape(view)}`],
		];
	});
}
