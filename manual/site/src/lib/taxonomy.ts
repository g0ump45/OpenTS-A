import { UI } from '../i18n/en.mjs';
import type { GuideCategory, InternalCategory, SystemCategory, UsingCategory } from './content-contracts';

export const SYSTEM_CATEGORIES = UI.systemCategories;
export const SYSTEM_GROUPS = UI.systemGroups;
export const GUIDE_CATEGORIES = UI.guideCategories;
export const USING_CATEGORIES = UI.usingCategories;
export const INTERNAL_CATEGORIES = UI.internalCategories;

export function systemCategoryTitle(id: SystemCategory | string): string {
	return SYSTEM_CATEGORIES.find((category) => category.id === id)?.title ?? id;
}

export function guideCategoryTitle(id: GuideCategory | string): string {
	return GUIDE_CATEGORIES.find((category) => category.id === id)?.title ?? id;
}

export function usingCategoryTitle(id: UsingCategory | string): string {
	return USING_CATEGORIES.find((category) => category.id === id)?.title ?? id;
}

export function internalCategoryTitle(id: InternalCategory | string): string {
	return INTERNAL_CATEGORIES.find((category) => category.id === id)?.title ?? id;
}

export function systemGroupForCategory(id: SystemCategory | string) {
	return SYSTEM_GROUPS.find((group) => group.categories.includes(id));
}