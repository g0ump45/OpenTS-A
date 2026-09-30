/*
 * Authored format catalog. Metadata is loaded synchronously so routes,
 * lifecycle links, and cross-references can resolve formats without coupling
 * the generated-data layer to Astro's asynchronous content API.
 */

import { load } from 'js-yaml';
import authoredFormat from '../../../schema/authored-format.schema.json';
import { UI } from '../i18n/en.mjs';
import type { KeyRecord, KeyScope } from './data';
import { assertContract } from './schema-validator';
import type { SectionSelector } from './section-selector.mjs';

export type FormatKind = 'syntax' | 'file' | 'registry' | 'record' | 'binary';

export interface FormatReference {
	type: 'key' | 'action' | 'event' | 'mission' | 'format' | 'enum' | 'system' | 'command' | 'guide' | 'using' | 'internal';
	id: string;
	scope?: string;
}

export interface FormatKeyScopeQuery {
	file?: string;
	section?: SectionSelector;
	applies_to?: string;
}

export interface FormatRegistration {
	section: string;
	id_from: 'key' | 'value' | 'entry-name';
	entry_section?: string;
	value?: string;
}

export interface FormatField {
	position: number;
	label: string;
	value: string;
	required: boolean;
	note?: string;
}

interface FormatCommon {
	format_id: string;
	title: string;
	summary: string;
	kind: FormatKind;
	route?: string;
	source_files: string[];
	related: FormatReference[];
	key_scopes: FormatKeyScopeQuery[];
}

export interface SyntaxFormat extends FormatCommon {
	kind: 'syntax';
	applies_to: string[];
}

export interface FileFormat extends FormatCommon {
	kind: 'file';
	filenames: string[];
}

export interface RegistryFormat extends FormatCommon {
	kind: 'registry';
	files: string[];
	registrations: FormatRegistration[];
}

export interface RecordFormat extends FormatCommon {
	kind: 'record';
	files: string[];
	section: string;
	syntax: string;
	registration?: FormatRegistration;
	enable_section?: string;
	fields: FormatField[];
}

export interface BinaryFormat extends FormatCommon {
	kind: 'binary';
	extensions: string[];
	role: 'archive' | 'image' | 'model' | 'audio' | 'video' | 'persistence';
	companion_formats: string[];
}

export type FormatData = SyntaxFormat | FileFormat | RegistryFormat | RecordFormat | BinaryFormat;

export type FormatRecord = FormatData & {
	slug: string;
	route: string;
};

export interface FormatKeyMatch {
	record: KeyRecord;
	scope: KeyScope;
}

const RAW_FORMATS = import.meta.glob('../../../content/formats/*.md', {
	query: '?raw',
	import: 'default',
	eager: true,
}) as Record<string, string>;

let formatCache: Map<string, FormatRecord> | null = null;

function parseFrontmatter(path: string, source: string): Record<string, unknown> {
	const match = source.match(/^---\r?\n([\s\S]*?)\r?\n---/);
	if (!match) throw new Error(`${path}: missing format frontmatter`);
	const value = load(match[1]);
	assertContract(authoredFormat, value, path);
	return value as Record<string, unknown>;
}

function routeTail(route: string): string {
	const tail = route.split('/').filter(Boolean).at(-1);
	if (!tail) throw new Error(`Format route ${JSON.stringify(route)} has no path segment`);
	return tail;
}

function normalize(path: string, source: string): FormatRecord {
	const data = parseFrontmatter(path, source) as unknown as FormatData;
	const slug = path.split('/').at(-1)?.replace(/\.md$/, '');
	if (!slug) throw new Error(`${path}: cannot derive format slug`);
	const route = data.route ?? `/formats/${slug}/`;
	if (routeTail(route) !== slug) {
		throw new Error(`${path}: filename must match the final segment of ${route}`);
	}
	return {
		...data,
		related: data.related ?? [],
		key_scopes: data.key_scopes ?? [],
		...(data.kind === 'binary' ? { companion_formats: data.companion_formats ?? [] } : {}),
		slug,
		route,
	} as FormatRecord;
}

export function allFormats(): Map<string, FormatRecord> {
	if (formatCache) return formatCache;
	formatCache = new Map();
	const routes = new Map<string, string>();
	for (const [path, source] of Object.entries(RAW_FORMATS)) {
		const record = normalize(path, source);
		if (formatCache.has(record.format_id)) {
			throw new Error(`Duplicate format ID: ${record.format_id}`);
		}
		const routeOwner = routes.get(record.route);
		if (routeOwner) {
			throw new Error(`Format route ${record.route} is shared by ${routeOwner} and ${record.format_id}`);
		}
		routes.set(record.route, record.format_id);
		formatCache.set(record.format_id, record);
	}

	for (const record of formatCache.values()) {
		if (record.kind !== 'binary') continue;
		for (const companion of record.companion_formats) {
			if (!formatCache.has(companion)) {
				throw new Error(`Format ${record.format_id}: unknown companion format ${companion}`);
			}
			if (companion === record.format_id) {
				throw new Error(`Format ${record.format_id}: a format cannot be its own companion`);
			}
		}
	}
	return formatCache;
}

export function formatBySlug(slug: string): FormatRecord | undefined {
	return [...allFormats().values()].find((record) => record.slug === slug);
}

export function formatHref(formatId: string): string | undefined {
	return allFormats().get(formatId)?.route;
}

export function formatLabel(formatId: string): string | undefined {
	return allFormats().get(formatId)?.title;
}

function sameSelector(left: SectionSelector, right: SectionSelector): boolean {
	if (left.kind !== right.kind) return false;
	if (left.kind === 'literal' && right.kind === 'literal') return left.name === right.name;
	if (left.kind === 'identifier' && right.kind === 'identifier') return left.source === right.source;
	// An Image= read that keeps the object's own name as its fallback is a
	// different lookup from one that has no fallback, so a query for either
	// must never match the other.
	return left.kind === 'image' && right.kind === 'image'
		&& (left.fallback ?? null) === (right.fallback ?? null);
}

function matches(scope: KeyScope, query: FormatKeyScopeQuery): boolean {
	return (!query.file || scope.file === query.file)
		&& (!query.section || sameSelector(scope.section, query.section))
		&& (!query.applies_to || scope.applies_to.includes(query.applies_to));
}

/** Resolve accepted settings from generated scopes without copying key lists into Markdown. */
export function formatKeyMatches(format: FormatData, keys: ReadonlyMap<string, KeyRecord>): FormatKeyMatch[] {
	const matchesByIdentity = new Map<string, FormatKeyMatch>();
	for (const record of keys.values()) {
		for (const scope of record.scopes) {
			if (!format.key_scopes.some((query) => matches(scope, query))) continue;
			matchesByIdentity.set(`${record.key}\u0000${scope.route_id}`, { record, scope });
		}
	}
	return [...matchesByIdentity.values()].sort((left, right) =>
		left.record.key.localeCompare(right.record.key)
		|| left.scope.route_id.localeCompare(right.scope.route_id));
}

export function formatKindLabel(kind: FormatKind): string {
	const entry = UI.formatKinds.find((candidate) => candidate.id === kind);
	if (!entry) throw new Error(`Unknown format kind: ${kind}`);
	return entry.title;
}
