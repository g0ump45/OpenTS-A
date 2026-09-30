const DEFAULT_SITE = 'https://opents-developers.github.io';
const DEFAULT_BASE = '/OpenTS-Prepub-Scratch';
const DEFAULT_REPOSITORY = 'https://github.com/OpenTS-Developers/OpenTS-Prepub-Scratch';

function configuredValue(env, name, fallback) {
	const value = env?.[name]?.trim();
	return value || fallback;
}

function webUrl(value, name) {
	let url;
	try {
		url = new URL(value);
	} catch {
		throw new Error(`${name} must be an absolute HTTP(S) URL, got ${JSON.stringify(value)}`);
	}
	if (url.protocol !== 'https:' && url.protocol !== 'http:') {
		throw new Error(`${name} must use HTTP or HTTPS, got ${JSON.stringify(value)}`);
	}
	if (url.search || url.hash) {
		throw new Error(`${name} must not contain a query or fragment, got ${JSON.stringify(value)}`);
	}
	return url;
}

function siteOrigin(value) {
	const url = webUrl(value, 'DOCS_SITE');
	if (url.pathname !== '/') {
		throw new Error('DOCS_SITE is the deployment origin; put the path prefix in DOCS_BASE');
	}
	return url.origin;
}

function repositoryUrl(value) {
	return webUrl(value, 'DOCS_REPOSITORY_URL').toString().replace(/\/$/, '');
}

function deploymentBase(value) {
	if (!value || value === '/') return '';
	if (/[?#]/.test(value)) throw new Error('DOCS_BASE must be a URL path without a query or fragment');
	const rooted = value.startsWith('/') ? value : `/${value}`;
	const normalized = rooted.replace(/\/{2,}/g, '/').replace(/\/$/, '');
	if (normalized.split('/').some((part) => part === '.' || part === '..')) {
		throw new Error('DOCS_BASE must not contain . or .. path segments');
	}
	return normalized;
}

function booleanValue(value, name) {
	if (value === undefined || value === '') return false;
	if (/^(?:1|true|yes|on)$/i.test(value)) return true;
	if (/^(?:0|false|no|off)$/i.test(value)) return false;
	throw new Error(`${name} must be one of 1/0, true/false, yes/no, or on/off`);
}

export function resolveSiteConfig(env = typeof process === 'undefined' ? {} : process.env) {
	const base = deploymentBase(configuredValue(env, 'DOCS_BASE', DEFAULT_BASE));
	const explicitDemo = booleanValue(env?.DOCS_DEMO, 'DOCS_DEMO');
	return Object.freeze({
		site: siteOrigin(configuredValue(env, 'DOCS_SITE', DEFAULT_SITE)),
		base,
		repositoryUrl: repositoryUrl(configuredValue(env, 'DOCS_REPOSITORY_URL', DEFAULT_REPOSITORY)),
		revision: configuredValue(env, 'DOCS_REVISION', 'main'),
		demo: explicitDemo || base.toLowerCase() === '/docs-demo',
	});
}

export const siteConfig = resolveSiteConfig();

export function sourceFileUrl(path, config = siteConfig) {
	const cleanPath = String(path).replace(/^\/+/, '');
	return `${config.repositoryUrl}/blob/${encodeURIComponent(config.revision)}/${cleanPath}`;
}
