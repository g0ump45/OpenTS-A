const scopeIdentity = (reference) => reference.scope ?? '';

export function relatedIdentity(reference) {
	return `${reference.type}:${reference.id}:${scopeIdentity(reference)}`;
}

export function referenceTargets(reference, target) {
	if (reference.type !== target.type || reference.id !== target.id) return false;
	if (target.type === 'key' && target.scope === undefined) {
		return true;
	}
	return scopeIdentity(reference) === scopeIdentity(target);
}
