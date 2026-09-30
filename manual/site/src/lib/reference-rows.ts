/*
 * Shared row construction for the tables that list one INI section.
 *
 * A section table stands for a place in a file, so a spelling the engine reads
 * more than once there contributes more than one row. The rows are only
 * distinguishable if each carries the label its reading is documented under,
 * and only honest if a reading that does nothing is not allowed to badge a
 * spelling that works.
 */

import {
	applicabilitySummary,
	displayWhenOmitted,
	effectForScope,
	requireKey,
	type EffectState,
	type ReferenceRow,
	type WhenOmittedDisplay,
} from './data';
import { withBase } from './paths';

interface KeyProseEntry {
	data: { key: string; scope?: string; label?: string; summary?: string };
}

export interface ReferenceTableRow {
	key: string;
	href: string;
	summary?: string;
	value: string;
	whenOmitted: WhenOmittedDisplay;
	effect: EffectState;
	context?: string;
	searchContext?: string;
	viaImage?: boolean;
}

interface Options {
	/** Names the table in the error raised for a key the catalog does not hold. */
	context: string;
	/** Row detail that outranks the reading label, such as an exception summary. */
	detail?: (row: ReferenceRow) => string | undefined;
	searchContext?: (row: ReferenceRow) => string;
}

export function referenceTableRows(
	rows: ReferenceRow[],
	prose: KeyProseEntry[],
	options: Options,
): ReferenceTableRow[] {
	const summaries = new Map<string, string>();
	const labels = new Map<string, string>();
	for (const entry of prose) {
		if (entry.data.scope) {
			if (entry.data.label) labels.set(`${entry.data.key}\u0000${entry.data.scope}`, entry.data.label);
		} else if (entry.data.summary) {
			summaries.set(entry.data.key, entry.data.summary);
		}
	}

	const resolved = rows.map((row) => {
		const record = requireKey(row.key, options.context);
		return { row, record, effect: effectForScope(prose, record, row.scope) };
	});

	/* A spelling that works here keeps only the readings that do something; one
	   inert everywhere in this table keeps its rows and its badge. */
	const liveKeys = new Set(
		resolved.filter(({ effect }) => effect === 'used').map(({ row }) => row.key),
	);
	const kept = resolved.filter(({ row, effect }) => effect === 'used' || !liveKeys.has(row.key));

	const readings = new Map<string, number>();
	for (const { row } of kept) readings.set(row.key, (readings.get(row.key) ?? 0) + 1);

	return kept.map(({ row, record, effect }) => {
		const scope = row.scope;
		/* Only a table listing one spelling twice has to say which reading a
		   row is, or land the reader on it rather than on the whole key. */
		const multiple = (readings.get(row.key) ?? 0) > 1;
		const reading = multiple
			? labels.get(`${row.key}\u0000${scope.route_id}`)
				?? applicabilitySummary(scope.applies_to, scope.level)
			: undefined;
		return {
			key: row.key,
			href: withBase(`/keys/${row.keyRoute}/${multiple ? `#scope-${scope.route_id}` : ''}`),
			summary: summaries.get(row.key),
			value: scope.value_type,
			whenOmitted: displayWhenOmitted(prose, record, scope),
			effect,
			context: options.detail?.(row) ?? reading,
			searchContext: options.searchContext?.(row),
			viaImage: row.viaImage,
		};
	});
}
