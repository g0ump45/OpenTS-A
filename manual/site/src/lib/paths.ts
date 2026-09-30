import { siteConfig } from './site-config.mjs';

const base = import.meta.env.BASE_URL.replace(/\/$/, '');

/** Prefix a logical site route with Astro's deployment base exactly once. */
export function withBase(path: string): string {
	if (!path || /^(?:[a-z]+:|#|\/\/)/i.test(path)) return path;
	const rooted = path.startsWith('/') ? path : `/${path}`;
	if (base && (rooted === base || rooted.startsWith(`${base}/`))) return rooted;
	return `${base}${rooted}` || '/';
}

export function publicPageUrl(pathname: string): string {
	return new URL(withBase(pathname), `${siteConfig.site}/`).toString();
}

export function requireRouteTail(route: string, context: string): string {
	const tail = route.split('/').filter(Boolean).at(-1);
	if (!tail) throw new Error(`${context}: route ${JSON.stringify(route)} has no path segment`);
	return tail;
}

export function requireRouteParam(value: string | undefined, name: string): string {
	if (!value) throw new Error(`Missing required route parameter: ${name}`);
	return value;
}
