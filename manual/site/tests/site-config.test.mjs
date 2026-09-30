import assert from 'node:assert/strict';
import test from 'node:test';
import { resolveSiteConfig, sourceFileUrl } from '../src/lib/site-config.mjs';

test('site configuration uses the published manual defaults', () => {
	assert.deepEqual(resolveSiteConfig({}), {
		site: 'https://opents-developers.github.io',
		base: '/OpenTS-Prepub-Scratch',
		repositoryUrl: 'https://github.com/OpenTS-Developers/OpenTS-Prepub-Scratch',
		revision: 'main',
		demo: false,
	});
});

test('site configuration normalizes custom deployment values from one authority', () => {
	const config = resolveSiteConfig({
		DOCS_SITE: 'https://manual.example.test/',
		DOCS_BASE: 'preview//candidate/',
		DOCS_REPOSITORY_URL: 'https://github.com/example/project/',
		DOCS_REVISION: 'abc123',
		DOCS_DEMO: 'yes',
	});

	assert.deepEqual(config, {
		site: 'https://manual.example.test',
		base: '/preview/candidate',
		repositoryUrl: 'https://github.com/example/project',
		revision: 'abc123',
		demo: true,
	});
	assert.equal(
		sourceFileUrl('/manual/content/guides/example.md', config),
		'https://github.com/example/project/blob/abc123/manual/content/guides/example.md',
	);
});

test('root-base and Docs-Demo deployments retain their compatibility behavior', () => {
	assert.equal(resolveSiteConfig({ DOCS_BASE: '/' }).base, '');
	assert.equal(resolveSiteConfig({ DOCS_BASE: '/Docs-Demo', DOCS_DEMO: '0' }).demo, true);
	assert.equal(resolveSiteConfig({ DOCS_BASE: '/not-a-demo', DOCS_DEMO: 'true' }).demo, true);
});

test('invalid site configuration fails with the responsible variable name', () => {
	for (const [environment, variable] of [
		[{ DOCS_SITE: '/relative' }, 'DOCS_SITE'],
		[{ DOCS_SITE: 'ftp://manual.example.test' }, 'DOCS_SITE'],
		[{ DOCS_SITE: 'https://manual.example.test/docs' }, 'DOCS_SITE'],
		[{ DOCS_REPOSITORY_URL: 'github.com/example/project' }, 'DOCS_REPOSITORY_URL'],
		[{ DOCS_BASE: '/docs?preview=1' }, 'DOCS_BASE'],
		[{ DOCS_BASE: '../docs' }, 'DOCS_BASE'],
		[{ DOCS_DEMO: 'sometimes' }, 'DOCS_DEMO'],
	]) {
		assert.throws(
			() => resolveSiteConfig(environment),
			(error) => error instanceof Error && error.message.includes(variable),
		);
	}
});
