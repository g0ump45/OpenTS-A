const IDENTIFIER_LABELS = {
	'object-type': 'ObjectType ID',
	house: 'House ID',
	difficulty: 'Difficulty ID',
	campaign: 'Campaign ID',
	theme: 'Theme ID',
	sound: 'Sound ID',
	'tile-set': 'TileSet ID',
	'land-type': 'LandType ID',
	mission: 'Mission name',
	'multiplayer-map': 'Map ID',
};

const COMPATIBILITY_SLUGS = {
	'identifier:object-type': 'the-object-s-own-entry',
	'identifier:house': 'the-house-s-own-entry',
	'identifier:difficulty': 'the-selected-difficulty-entry',
	'identifier:campaign': 'the-campaign-s-own-entry',
	'identifier:theme': 'the-theme-s-own-entry',
	'identifier:sound': 'the-sound-s-own-entry',
	'identifier:tile-set': 'section',
	'identifier:land-type': 'lands-land',
	'identifier:mission': 'the-mission-s-own-entry',
	'identifier:multiplayer-map': 'the-map-s-own-entry',
	'image:object-type': 'the-entry-named-by-this-object-s-image',
	image: 'the-entry-named-by-this-object-s-image-only',
};

/** @param {unknown} value @param {string} context */
export function requireSectionSelector(value, context) {
	if (!value || typeof value !== 'object' || Array.isArray(value)) {
		throw new Error(`${context}: section must be a selector object`);
	}
	const selector = /** @type {Record<string, unknown>} */ (value);
	if (selector.kind === 'literal' && typeof selector.name === 'string' &&
		selector.name.length > 0 && !/[\[\]]/.test(selector.name)) {
		return /** @type {import('./section-selector.mjs').SectionSelector} */ (value);
	}
	if (selector.kind === 'identifier' && typeof selector.source === 'string' &&
		Object.hasOwn(IDENTIFIER_LABELS, selector.source)) {
		return /** @type {import('./section-selector.mjs').SectionSelector} */ (value);
	}
	// An Image= read either falls back to the object's own entry or has no
	// fallback at all; the reader that supplies an empty default decides.
	if (selector.kind === 'image' && Object.keys(selector).length === 1) {
		return /** @type {import('./section-selector.mjs').SectionSelector} */ (value);
	}
	if (selector.kind === 'image' && selector.fallback === 'object-type') {
		return /** @type {import('./section-selector.mjs').SectionSelector} */ (value);
	}
	throw new Error(`${context}: invalid section selector ${JSON.stringify(value)}`);
}

/** @param {import('./section-selector.mjs').SectionSelector} selector */
export function sectionSelectorKey(selector) {
	if (selector.kind === 'literal') return `literal:${selector.name}`;
	if (selector.kind === 'identifier') return `identifier:${selector.source}`;
	return selector.fallback ? `image:${selector.fallback}` : 'image';
}

/** @param {import('./section-selector.mjs').SectionSelector} selector */
export function sectionSelectorLabel(selector) {
	if (selector.kind === 'literal') return `[${selector.name}]`;
	if (selector.kind === 'identifier') return `[<${IDENTIFIER_LABELS[selector.source]}>]`;
	return '[<Image ID>]';
}

/** Does an Image= read fall back to the object's own entry when Image= is absent? */
export function imageSectionHasObjectFallback(selector) {
	return selector.kind === 'image' && selector.fallback === 'object-type';
}

/** @param {import('./section-selector.mjs').SectionSelector} selector */
export function sectionSelectorSlug(selector) {
	if (selector.kind === 'literal') {
		if (selector.name === 'LEVITATION') return 'levitation-controls';
		return selector.name.toLowerCase().replace(/[^a-z0-9]+/g, '-').replace(/^-|-$/g, '');
	}
	const slug = COMPATIBILITY_SLUGS[sectionSelectorKey(selector)];
	if (!slug) throw new Error(`No compatibility slug for ${sectionSelectorKey(selector)}`);
	return slug;
}

/** @param {import('./section-selector.mjs').SectionSelector} selector */
export function isLiteralSection(selector) {
	return selector.kind === 'literal';
}

/** @param {import('./section-selector.mjs').SectionSelector} selector */
export function isImageSection(selector) {
	return selector.kind === 'image';
}
