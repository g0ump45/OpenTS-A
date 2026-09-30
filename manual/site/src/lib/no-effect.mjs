// @ts-check

/*
 * A key spelling can be inert everywhere or inert in only some of the places
 * the engine reads it. A key-level record states that the whole spelling is
 * inert; a scope record states only that one reading is. Rows that stand for a
 * single reading resolve to a definite answer; rows that stand for a whole
 * spelling keep the partial case distinct so a key such as Armor is never
 * presented as dead.
 */

/** @typedef {'used' | 'partial' | 'none'} EffectState */
/** @typedef {{ data: { key: string, scope?: string, no_effect?: boolean } }} EffectProseEntry */
/** @typedef {{ key: string, scopes: Array<{ route_id: string }> }} EffectKeyRecord */

/**
 * @param {EffectProseEntry[]} entries
 * @param {EffectKeyRecord} record
 */
const wholeKeyIsInert = (entries, record) => entries.some(
	(entry) => entry.data.key === record.key && !entry.data.scope && entry.data.no_effect,
);

/**
 * @param {EffectProseEntry[]} entries
 * @param {EffectKeyRecord} record
 * @param {{ route_id: string }} scope
 */
export function noEffectForScope(entries, record, scope) {
	if (wholeKeyIsInert(entries, record)) return true;
	return entries.some(
		(entry) => entry.data.key === record.key
			&& entry.data.scope === scope.route_id
			&& entry.data.no_effect,
	);
}

/**
 * State for a row that stands for one reading of a spelling.
 *
 * @param {EffectProseEntry[]} entries
 * @param {EffectKeyRecord} record
 * @param {{ route_id: string }} scope
 * @returns {EffectState}
 */
export function effectForScope(entries, record, scope) {
	return noEffectForScope(entries, record, scope) ? 'none' : 'used';
}

/**
 * State for a row that stands for every reading of a spelling.
 *
 * @param {EffectProseEntry[]} entries
 * @param {EffectKeyRecord} record
 * @returns {EffectState}
 */
export function effectForKey(entries, record) {
	if (wholeKeyIsInert(entries, record)) return 'none';
	const inert = record.scopes.filter((scope) => noEffectForScope(entries, record, scope));
	if (inert.length === 0) return 'used';
	return inert.length === record.scopes.length ? 'none' : 'partial';
}
