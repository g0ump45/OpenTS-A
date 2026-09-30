import type { CollectionEntry } from 'astro:content';
import {
	compareVersions,
	type EntityReference,
	type LifecycleEffect,
	type LifecycleTarget,
} from './data';

export interface LifecycleEvent {
	change: CollectionEntry<'changes'>;
	target: LifecycleTarget;
	release: string;
	effect: LifecycleEffect;
}

export function lifecycleFor(
	changes: CollectionEntry<'changes'>[],
	reference: EntityReference,
): LifecycleEvent[] {
	const events = changes.flatMap((change) =>
		change.data.targets
			.filter((target) =>
				target.type === reference.type
				&& target.id === reference.id
				&& (reference.scope === undefined || target.scope === reference.scope))
			.map((target) => ({
				change,
				target,
				release: change.data.release,
				effect: target.effect,
			})),
	);
	return events.sort((left, right) =>
		compareVersions(left.release, right.release)
		|| left.change.id.localeCompare(right.change.id));
}

export function introductionFor(events: LifecycleEvent[]): LifecycleEvent | undefined {
	return events.find((event) => event.effect === 'added' && event.target.scope === undefined);
}

/** TOC entry for LifecycleHistory's "History" section, when it will render. */
export function historyHeading(
	changes: CollectionEntry<'changes'>[],
	reference: EntityReference,
): Array<{ depth: number; slug: string; text: string }> {
	return lifecycleFor(changes, reference).length > 0
		? [{ depth: 2, slug: 'entity-history', text: 'History' }]
		: [];
}

export function latestStateFor(events: LifecycleEvent[]): LifecycleEvent | undefined {
	const recent = [...events].reverse();
	return recent.find((event) => event.effect === 'deprecated' || event.effect === 'removed')
		?? recent.find((event) => event.effect === 'changed');
}

export const effectLabels: Record<LifecycleEffect, string> = {
	added: 'Added',
	changed: 'Changed',
	deprecated: 'Deprecated',
	removed: 'Removed',
};

