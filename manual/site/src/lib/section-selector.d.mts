export type IdentifierSectionSource =
	| 'object-type'
	| 'house'
	| 'difficulty'
	| 'campaign'
	| 'theme'
	| 'sound'
	| 'tile-set'
	| 'land-type'
	| 'mission'
	| 'multiplayer-map';

export type SectionSelector =
	| { kind: 'literal'; name: string }
	| { kind: 'identifier'; source: IdentifierSectionSource }
	| { kind: 'image'; fallback?: 'object-type' };

export function requireSectionSelector(value: unknown, context: string): SectionSelector;
export function sectionSelectorKey(selector: SectionSelector): string;
export function sectionSelectorLabel(selector: SectionSelector): string;
export function sectionSelectorSlug(selector: SectionSelector): string;
export function isLiteralSection(selector: SectionSelector): selector is Extract<SectionSelector, { kind: 'literal' }>;
export function isImageSection(selector: SectionSelector): selector is Extract<SectionSelector, { kind: 'image' }>;
export function imageSectionHasObjectFallback(selector: SectionSelector): boolean;
