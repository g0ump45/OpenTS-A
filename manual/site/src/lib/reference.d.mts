import type { SectionSelector } from './section-selector.mjs';

export type ReferencePage = 'rules' | 'art' | 'other';

export interface ReferencePageMetadata {
	title: string;
	files: string[];
	blurb: string;
}

export interface OtherIniFileMetadata {
	id: string;
	label: string;
	title: string;
	sourceFiles: string[];
	purpose: string;
	loadBehavior: string;
	groupOrder?: string[];
	sectionGroup?: { slug: string; title: string };
}

export interface RawReferenceRead {
	file: string;
	section: SectionSelector;
}

export interface RawReferenceScope {
	applies_to: string[];
	file: string;
	section: SectionSelector;
	value_type: string;
	level: string;
	note?: string;
	precedence?: string;
	read_from?: RawReferenceRead[];
}

export interface RawReferenceEntry {
	scopes: RawReferenceScope[];
	case_collides_with?: string[];
}

export interface RawReferenceRow {
	key: string;
	keySlug: string;
	/* Position in the key's own scope list; the identity a row resolves by. */
	scopeIndex: number;
	scope: RawReferenceScope;
	except?: string[];
	viaImage: boolean;
}

export interface RawReferenceGroup {
	title: string;
	slug: string;
	file?: string;
	fileId?: string;
	fileLabel?: string;
	displayTitle?: string;
	navTitle?: string;
	subtitle?: string;
	literal?: boolean;
	behavior?: boolean;
	shared?: number;
	rows: RawReferenceRow[];
}

export const REFERENCE_PAGES: Readonly<Record<ReferencePage, ReferencePageMetadata>>;
export const OTHER_INI_FILES: readonly OtherIniFileMetadata[];
export const MAPPING_FILES: readonly string[];
export const LEVEL_NAMES: Readonly<Record<string, string>>;

export function otherIniFile(sourceFile: string): OtherIniFileMetadata | undefined;
export function referenceFileLabel(sourceFile: string): string;
export function applicabilitySummary(appliesTo?: string[], level?: string): string;
export function exceptionSummary(exceptions?: string[]): string;
export function slugify(text: unknown): string;
export function keySlug(name: string, entry: RawReferenceEntry): string;
export function referenceGroups(
	raw: Record<string, RawReferenceEntry>,
	page: ReferencePage,
): RawReferenceGroup[];
export function scenarioGroups(raw: Record<string, RawReferenceEntry>): RawReferenceGroup[];
