import type { EntityReference } from './content-contracts';

export function relatedIdentity(reference: EntityReference): string;
export function referenceTargets(reference: EntityReference, target: EntityReference): boolean;
