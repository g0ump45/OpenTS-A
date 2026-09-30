/*
 * File-system boundary for generated and hand-authored manual data. Keep Vite
 * glob loading, YAML/frontmatter parsing, and raw contract validation out of
 * the public view models.
 */

import { load } from 'js-yaml';
import authoredEnum from '../../../schema/authored-enum.schema.json';
import generatedIniKeys from '../../../schema/generated-ini-keys.schema.json';
import generatedScripting from '../../../schema/generated-scripting.schema.json';
import releases from '../../../schema/releases.schema.json';
import scriptingRouteAliases from '../../../schema/scripting-route-aliases.schema.json';
import tombstones from '../../../schema/tombstones.schema.json';
import { assertContract } from './schema-validator';

const RAW_DATA = import.meta.glob('../../../data/*.yaml', {
	query: '?raw',
	import: 'default',
	eager: true,
}) as Record<string, string>;
const RAW_ENUMS = import.meta.glob('../../../content/enums/*.md', {
	query: '?raw',
	import: 'default',
	eager: true,
}) as Record<string, string>;
const TEST_DATA = import.meta.glob('../../tests/fixtures/*.yaml', {
	query: '?raw',
	import: 'default',
	eager: true,
}) as Record<string, string>;

const DATA_SCHEMAS: Readonly<Record<string, object>> = {
	'ini-keys.yaml': generatedIniKeys,
	'scripting.yaml': generatedScripting,
	'releases.yaml': releases,
	'scripting-route-aliases.yaml': scriptingRouteAliases,
	'tombstones.yaml': tombstones,
};
const dataCache = new Map<string, unknown>();
let enumDocumentCache: Readonly<Record<string, unknown>> | null = null;

function requireRawFile(files: Record<string, string>, suffix: string, label: string): string {
	const hit = Object.entries(files).find(([path]) => path.endsWith(`/${suffix}`));
	if (!hit) throw new Error(`${label} is missing`);
	return hit[1];
}

export function loadDataYaml<T>(name: string): T {
	if (dataCache.has(name)) return dataCache.get(name) as T;
	const schema = DATA_SCHEMAS[name];
	if (!schema) throw new Error(`manual/data/${name} has no registered shared schema`);
	const value = load(requireRawFile(RAW_DATA, name, `manual/data/${name}`));
	assertContract(schema, value, `manual/data/${name}`);
	dataCache.set(name, value);
	return value as T;
}

export function loadEnumDocuments(): Readonly<Record<string, unknown>> {
	if (enumDocumentCache) return enumDocumentCache;
	const documents: Record<string, unknown> = {};
	for (const [path, source] of Object.entries(RAW_ENUMS)) {
		const frontmatter = source.match(/^---\r?\n([\s\S]*?)\r?\n---/);
		if (!frontmatter) throw new Error(`${path}: missing enum frontmatter`);
		const value = load(frontmatter[1]);
		assertContract(authoredEnum, value, path);
		documents[path] = value;
	}
	enumDocumentCache = Object.freeze(documents);
	return enumDocumentCache;
}

export function loadFixtureYaml<T>(name: string): T {
	return load(requireRawFile(TEST_DATA, name, `manual/site/tests/fixtures/${name}`)) as T;
}
