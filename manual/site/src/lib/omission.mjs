import { UI } from '../i18n/en.mjs';

export function whenOmittedForScope(entries, record, scope) {
	const scoped = entries.find(
		(entry) =>
			entry.data.key === record.key &&
			entry.data.scope === scope.route_id &&
			entry.data.when_omitted,
	);
	if (scoped) return scoped.data.when_omitted;
	if (record.scopes.length !== 1) return undefined;
	return entries.find(
		(entry) => entry.data.key === record.key && !entry.data.scope && entry.data.when_omitted,
	)?.data.when_omitted;
}

export function formatWhenOmitted(whenOmitted) {
	if (!whenOmitted) {
		return { text: UI.omission.notDocumented, code: false };
	}
	if (whenOmitted.kind === 'value') {
		return {
			text: whenOmitted.value === '' ? UI.omission.empty : whenOmitted.value,
			code: true,
			note: whenOmitted.note,
		};
	}
	return {
		text: UI.omission.kinds[whenOmitted.kind],
		code: false,
		note: whenOmitted.note,
	};
}

/** Table-cell display for one scope. */
export function displayWhenOmitted(entries, record, scope) {
	return formatWhenOmitted(whenOmittedForScope(entries, record, scope));
}

export function summarizeWhenOmitted(entries, record) {
	const values = record.scopes.map((scope) => whenOmittedForScope(entries, record, scope));
	const documented = values.filter(Boolean);
	if (documented.length === 0) {
		return { text: UI.omission.notDocumented, code: false };
	}
	if (documented.length !== values.length) {
		return { text: UI.omission.partiallyDocumented, code: false };
	}
	const displays = documented.map(formatWhenOmitted);
	const distinct = new Set(displays.map((display) => `${display.code}:${display.text}`));
	return distinct.size === 1
		? displays[0]
		: { text: UI.omission.variesByType, code: false };
}
