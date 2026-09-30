// @ts-check
import { existsSync, readFileSync, readdirSync } from 'node:fs';
import { fileURLToPath } from 'node:url';
import { defineConfig } from 'astro/config';
import starlight from '@astrojs/starlight';
import { unified } from '@astrojs/markdown-remark';
import { load } from 'js-yaml';
import rehypeBaseLinks from './src/lib/rehype-base-links.mjs';
import {
	OTHER_INI_FILES,
	REFERENCE_PAGES,
	referenceGroups,
	scenarioGroups,
} from './src/lib/reference.mjs';
import { resolveSiteConfig } from './src/lib/site-config.mjs';
import { UI } from './src/i18n/en.mjs';

/** @typedef {import('./src/lib/reference.mjs').RawReferenceEntry} RawReferenceEntry */
/** @typedef {import('./src/lib/reference.mjs').ReferencePage} ReferencePage */
/** @typedef {import('./src/lib/reference.mjs').ReferencePageMetadata} ReferencePageMetadata */
/** @typedef {{ label: string, link: string } | { label: string, collapsed?: boolean, items: NavItem[] }} NavItem */

/** @param {string} relative */
const here = (relative) => fileURLToPath(new URL(relative, import.meta.url));

const parsedKeys = load(readFileSync(here('../data/ini-keys.yaml'), 'utf-8'));
if (!parsedKeys || typeof parsedKeys !== 'object' || Array.isArray(parsedKeys)) {
	throw new Error('manual/data/ini-keys.yaml must contain a key mapping');
}
const rawKeys = /** @type {Record<string, RawReferenceEntry>} */ (parsedKeys);
const siteConfig = resolveSiteConfig(process.env);
const astroBase = siteConfig.base || '/';

// Starlight prefixes sidebar routes with Astro's base. Keep these logical.
/** @param {string} path */
const link = (path) => path.startsWith('/') ? path : `/${path}`;

/**
 * @param {string} dir
 * @param {string} routeBase
 * @returns {Array<{ label: string, link: string, meta: Record<string, unknown> }>}
 */
function proseSources(dir, routeBase) {
	const directory = here(dir);
	if (!existsSync(directory)) {
		return [];
	}

	return readdirSync(directory)
		.filter((file) => file.endsWith('.md'))
		.map((file) => {
			const source = readFileSync(here(`${dir}/${file}`), 'utf-8');
			const frontmatter = source.match(/^---\r?\n([\s\S]*?)\r?\n---/);
			const parsed = frontmatter ? load(frontmatter[1]) : undefined;
			const meta = parsed && typeof parsed === 'object' && !Array.isArray(parsed)
				? /** @type {Record<string, unknown>} */ (parsed)
				: {};
			const id = file.replace(/\.md$/, '');
			const label = typeof meta.title === 'string' ? meta.title : id;
			const route = typeof meta.route === 'string' ? meta.route : `${routeBase}/${id}/`;
			return { label, link: link(route), meta };
		})
		.sort((left, right) => left.label.localeCompare(right.label));
}

/**
 * @param {string} dir
 * @param {string} routeBase
 * @returns {NavItem[]}
 */
function proseEntries(dir, routeBase) {
	return proseSources(dir, routeBase).map(({ label, link: href }) => ({ label, link: href }));
}

/**
 * Pages grouped by a frontmatter field, in the taxonomy's own order. An empty
 * group is left out, so a taxonomy may name a kind nothing carries yet.
 *
 * @param {string} dir
 * @param {string} routeBase
 * @param {string} field
 * @param {ReadonlyArray<{ id: string, title: string }>} taxonomy
 * @returns {NavItem[]}
 */
function proseGroups(dir, routeBase, field, taxonomy) {
	const sources = proseSources(dir, routeBase);
	const grouped = taxonomy.map((entry) => ({
		label: entry.title,
		items: sources
			.filter((source) => source.meta[field] === entry.id)
			.map(({ label, link: href }) => ({ label, link: href })),
	})).filter((group) => group.items.length > 0);
	const placed = new Set(grouped.flatMap((group) => group.items.map((item) => item.link)));
	const stray = sources.find((source) => !placed.has(source.link));
	if (stray) throw new Error(`${dir}: "${stray.label}" has no ${field} in the navigation taxonomy`);
	return grouped;
}

const referencePages = /** @type {Array<[ReferencePage, ReferencePageMetadata]>} */ (
	Object.entries(REFERENCE_PAGES)
);
const referenceItems = referencePages.map(([family, meta]) => {
	const groups = referenceGroups(rawKeys, family);
	/** @type {NavItem[]} */
	let items;
	if (family === 'other') {
		items = OTHER_INI_FILES.map((file) => ({
			label: file.label,
			collapsed: true,
			items: groups
				.filter((group) => group.fileId === file.id)
				.map((group) => ({
					label: group.navTitle ?? group.title,
					link: link(`/reference/${family}/${group.slug}/`),
				})),
		}));
	} else if (family === 'rules') {
		items = [
			{
				label: UI.navigation.objectTypes,
				collapsed: true,
				items: groups.filter((group) => !group.literal && !group.behavior).map((group) => ({
					label: group.title,
					link: link(`/reference/rules/${group.slug}/`),
				})),
			},
			{
				label: UI.navigation.behaviorSettings,
				collapsed: true,
				items: groups.filter((group) => group.behavior).map((group) => ({
					label: group.navTitle ?? group.title,
					link: link(`/reference/rules/${group.slug}/`),
				})),
			},
			{
				label: UI.navigation.namedSections,
				collapsed: true,
				items: groups.filter((group) => group.literal).map((group) => ({
					label: group.title,
					link: link(`/reference/rules/${group.slug}/`),
				})),
			},
		];
	} else {
		items = groups.map((group) => ({
			label: group.title,
			link: link(`/reference/${family}/${group.slug}/`),
		}));
	}

	return {
		label: meta.title,
		collapsed: true,
		items: [
			{ label: UI.navigation.overview, link: link(`/reference/${family}/`) },
			...items,
		],
	};
});
const scenarioItems = scenarioGroups(rawKeys).map((group) => ({
	label: group.title,
	link: link(`/mapping/scenario/${group.slug}/`),
}));

const social = [
	{
		icon: /** @type {const} */ ('github'),
		label: 'OpenTS on GitHub',
		href: siteConfig.repositoryUrl,
	},
	...(!siteConfig.demo ? [{
		icon: /** @type {const} */ ('discord'),
		label: 'OpenTS Discord',
		href: 'https://opents.net/discord',
	}] : []),
];

export default defineConfig({
	site: siteConfig.site,
	base: astroBase,
	trailingSlash: 'always',
	markdown: {
		processor: unified({ rehypePlugins: [[rehypeBaseLinks, { base: siteConfig.base }]] }),
	},
	integrations: [
		starlight({
			title: 'OpenTS Manual',
			description: 'OpenTS setup, features, commands, formats, INI files, mapping, internals, and changes.',
			customCss: ['./src/styles/custom.css'],
			components: {
				Head: './src/components/Head.astro',
				Sidebar: './src/components/Sidebar.astro',
				PageTitle: './src/components/PageTitle.astro',
			},
			favicon: '/favicon.svg',
			pagination: false,
			lastUpdated: true,
			markdown: {
				processedDirs: ['../content', '../changes'],
			},
			social,
			sidebar: [
				{
					label: UI.navigation.start,
					items: [
						{ label: UI.navigation.welcome, link: link('/') },
						{ label: UI.navigation.howToRead, link: link('/how-to-read/') },
						{ label: UI.navigation.glossary, link: link('/glossary/') },
					],
				},
				{
					label: UI.navigation.using,
					items: [
						{ label: UI.navigation.browseUsing, link: link('/using/') },
						{ label: UI.navigation.commandLine, link: link('/using/command-line/') },
						...proseEntries('../content/using', '/using'),
					],
				},
				/* Top-level `collapsed` flags are inert: Sidebar.astro renders only each
				   group's entries. Nested groups follow one rule — any group with
				   children is collapsed. */
				{
					label: UI.navigation.reference,
					items: [
						{ label: UI.navigation.referenceHome, link: link('/reference/') },
						{ label: UI.navigation.allKeys, link: link('/reference/all/') },
						...referenceItems,
						{ label: UI.navigation.mapSeeds, link: link('/reference/map-seeds/') },
						{ label: UI.navigation.theaterControls, link: link('/reference/theater-controls/') },
						{
							label: UI.navigation.enums,
							collapsed: true,
							items: [
								{ label: UI.navigation.overview, link: link('/reference/enums/') },
								...proseEntries('../content/enums', '/reference/enums'),
							],
						},
					],
				},
				{
					label: UI.navigation.guides,
					items: [
						{ label: UI.navigation.browseGuides, link: link('/guides/') },
						...proseEntries('../content/guides', '/guides'),
					],
				},
				{
					label: UI.navigation.mapping,
					items: [
						{ label: UI.navigation.mappingHome, link: link('/mapping/') },
						{
							label: UI.navigation.scenario,
							collapsed: true,
							items: [
								{ label: UI.navigation.overview, link: link('/mapping/scenario/') },
								...scenarioItems,
							],
						},
						{ label: UI.navigation.events, link: link('/mapping/events/') },
						{ label: UI.navigation.actions, link: link('/mapping/actions/') },
						{ label: UI.navigation.teamTypes, link: link('/mapping/team-types/') },
						{ label: UI.navigation.taskForces, link: link('/mapping/task-forces/') },
						{ label: UI.navigation.scripts, link: link('/mapping/scripts/') },
						{ label: UI.navigation.missions, link: link('/mapping/missions/') },
						{ label: UI.navigation.aiTriggers, link: link('/mapping/ai-triggers/') },
					],
				},
				{
					label: UI.navigation.commands,
					items: [
						{ label: UI.navigation.browseCommands, link: link('/commands/') },
						{ label: UI.navigation.fixedControls, link: link('/commands/fixed-controls/') },
					],
				},
				{
					label: UI.navigation.formats,
					items: [
						{ label: UI.navigation.browseFormats, link: link('/formats/') },
						...proseGroups('../content/formats', '/formats', 'kind', UI.formatKinds),
					],
				},
				{
					label: UI.navigation.internals,
					items: [
						{ label: UI.navigation.browseInternals, link: link('/internals/') },
						...proseEntries('../content/internals', '/internals'),
					],
				},
			],
		}),
	],
});
