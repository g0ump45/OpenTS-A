// @ts-check

/**
 * Read a filter value from URL search params, tolerating URL normalizers
 * that append a slash to the last query value.
 *
 * @param {URLSearchParams} params
 * @param {string} name
 */
export function cleanParam(params, name) {
	return (params.get(name) ?? '').replace(/\/+$/, '');
}
