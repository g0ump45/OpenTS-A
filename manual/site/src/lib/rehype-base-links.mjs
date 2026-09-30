/** Prefix root-relative links in authored Markdown with the configured Pages base. */
export default function rehypeBaseLinks(options = {}) {
	const base = String(options.base ?? '').replace(/\/$/, '');
	return function transform(tree) {
		if (!base) return;
		const walk = (node) => {
			if (node?.properties) {
				for (const property of ['href', 'src']) {
					const value = node.properties[property];
					if (
						typeof value === 'string' &&
						value.startsWith('/') &&
						!value.startsWith('//') &&
						value !== base &&
						!value.startsWith(`${base}/`)
					) {
						node.properties[property] = `${base}${value}`;
					}
				}
			}
			for (const child of node?.children ?? []) walk(child);
		};
		walk(tree);
	};
}
