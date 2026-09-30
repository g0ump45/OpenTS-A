import { getCollection } from 'astro:content';
import type { EntityReference, RelatedEntityType } from './content-contracts';
import { entityHref, entityLabel, requireEntityHref } from './data';
import { relatedIdentity, referenceTargets } from './related-identity.mjs';
import { allFormats } from './formats';

export interface RelatedResource {
	type: RelatedEntityType;
	id: string;
	scope?: string;
	href: string;
	label: string;
}

type AuthoredType = 'system' | 'guide' | 'using' | 'internal' | 'format' | 'action' | 'event' | 'mission';
interface AuthoredRecord {
	href: string;
	label: string;
	related: EntityReference[];
}

let authoredCatalogPromise: Promise<Map<string, AuthoredRecord>> | undefined;

async function authoredCatalog(): Promise<Map<string, AuthoredRecord>> {
	if (authoredCatalogPromise) return authoredCatalogPromise;
	authoredCatalogPromise = (async () => {
		const [systems, guides, using, internals, scripting] = await Promise.all([
			getCollection('systems'),
			getCollection('guides'),
			getCollection('using'),
			getCollection('internals'),
			getCollection('scripting'),
		]);
		const catalog = new Map<string, AuthoredRecord>();
		const add = (
			type: AuthoredType,
			id: string,
			title: string,
			related: EntityReference[] = [],
		) => {
			const reference = { type, id } as EntityReference;
			const href = entityHref(reference);
			if (!href) throw new Error(`No route for ${type} reference "${id}"`);
			const key = relatedIdentity(reference);
			if (catalog.has(key)) throw new Error(`Duplicate ${type} reference identity "${id}"`);
			catalog.set(key, { href, label: title, related });
		};
		for (const entry of systems) add('system', entry.id, entry.data.title, [
			...entry.data.related,
			...entry.data.keys.map((id) => ({ type: 'key' as const, id })),
		]);
		for (const entry of guides) add('guide', entry.id, entry.data.title, [
			...entry.data.related,
			...entry.data.uses_keys.map((id) => ({ type: 'key' as const, id })),
		]);
		for (const entry of using) add('using', entry.id, entry.data.title, entry.data.related);
		for (const entry of internals) add('internal', entry.id, entry.data.title, entry.data.related);
		for (const entry of scripting) add(entry.data.type, entry.data.id, entry.data.title, entry.data.related);
		for (const format of allFormats().values()) add('format', format.format_id, format.title, format.related);
		return catalog;
	})();
	return authoredCatalogPromise;
}

export async function resolveRelatedReferences(
	references: EntityReference[],
	context: string,
): Promise<RelatedResource[]> {
	const authored = await authoredCatalog();
	const resources: RelatedResource[] = [];
	const seen = new Set<string>();
	for (const reference of references) {
		const key = relatedIdentity(reference);
		if (seen.has(key)) throw new Error(`${context}: duplicate related reference ${key}`);
		seen.add(key);
		const record = authored.get(key);
		if (record) {
			resources.push({ ...reference, href: record.href, label: record.label });
			continue;
		}
		if (['system', 'guide', 'using', 'internal'].includes(reference.type)) {
			throw new Error(`${context}: unresolved ${reference.type} reference "${reference.id}"`);
		}
		resources.push({
			...reference,
			href: requireEntityHref(reference, context),
			label: entityLabel(reference),
		});
	}
	return resources;
}

export async function relatedResourcesFor(
	target: EntityReference,
	direct: EntityReference[],
	context: string,
): Promise<RelatedResource[]> {
	const authored = await authoredCatalog();
	const backlinks: EntityReference[] = [];
	for (const [key, record] of authored) {
		if (record.related.some((reference) => referenceTargets(reference, target))) {
			const [type, id] = key.split(':');
			backlinks.push({ type: type as AuthoredType, id });
		}
	}
	const merged = [...direct, ...backlinks].filter((reference, index, rows) =>
		relatedIdentity(reference) !== relatedIdentity(target) &&
		rows.findIndex((candidate) => relatedIdentity(candidate) === relatedIdentity(reference)) === index,
	);
	return resolveRelatedReferences(merged, context);
}