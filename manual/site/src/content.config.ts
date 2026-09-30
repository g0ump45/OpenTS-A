import { defineCollection } from 'astro:content';
import { glob } from 'astro/loaders';
import { docsLoader } from '@astrojs/starlight/loaders';
import { docsSchema } from '@astrojs/starlight/schema';
import {
	changeSchema,
	commandSchema,
	enumSchema,
	formatSchema,
	guideSchema,
	internalSchema,
	keyProseSchema,
	scriptingSchema,
	systemSchema,
	usingSchema,
} from './lib/content-contracts';

export const collections = {
	docs: defineCollection({ loader: docsLoader(), schema: docsSchema() }),

	keyprose: defineCollection({
		loader: glob({ pattern: '*.md', base: '../content/keys' }),
		schema: keyProseSchema,
	}),

	guides: defineCollection({
		loader: glob({ pattern: '*.md', base: '../content/guides' }),
		schema: guideSchema,
	}),

	systems: defineCollection({
		loader: glob({ pattern: '*.md', base: '../content/systems' }),
		schema: systemSchema,
	}),

	using: defineCollection({
		loader: glob({ pattern: '*.md', base: '../content/using' }),
		schema: usingSchema,
	}),

	commands: defineCollection({
		loader: glob({ pattern: '*.md', base: '../content/commands' }),
		schema: commandSchema,
	}),

	formats: defineCollection({
		loader: glob({ pattern: '*.md', base: '../content/formats' }),
		schema: formatSchema,
	}),

	internals: defineCollection({
		loader: glob({ pattern: '*.md', base: '../content/internals' }),
		schema: internalSchema,
	}),

	enums: defineCollection({
		loader: glob({ pattern: '*.md', base: '../content/enums' }),
		schema: enumSchema,
	}),

	scripting: defineCollection({
		loader: glob({ pattern: '**/*.md', base: '../content/scripting' }),
		schema: scriptingSchema,
	}),

	changes: defineCollection({
		loader: glob({ pattern: '*.md', base: '../changes' }),
		schema: changeSchema,
	}),
};
