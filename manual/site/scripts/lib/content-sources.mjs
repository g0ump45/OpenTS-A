/* Authored frontmatter and generated data, read straight from the repository.

   An artifact check that writes its expectations out by hand has to be edited
   every time a page is added, which trains the reader to update the check
   rather than to read the failure. Deriving them from the same content the
   site renders keeps the two independent -- the expectation comes from the
   content tree, the actual from the built HTML -- while a new page needs no
   edit here at all. */

import { existsSync, readFileSync, readdirSync } from 'node:fs';
import { resolve } from 'node:path';
import { load } from 'js-yaml';

const FRONTMATTER = /^---\r?\n([\s\S]*?)\r?\n---/;

export function readCollection(name) {
	const directory = resolve('../content', name);
	// A collection with nothing in it yet has no directory, which is a state the
	// hub is expected to render rather than a missing input.
	if (!existsSync(directory)) return [];
	return readdirSync(directory)
		.filter((file) => file.endsWith('.md'))
		.map((file) => {
			const text = readFileSync(resolve(directory, file), 'utf8');
			const block = text.match(FRONTMATTER);
			if (!block) throw new Error(`content/${name}/${file} has no frontmatter`);
			return { id: file.replace(/\.md$/, ''), ...load(block[1]) };
		});
}

export function readChanges() {
	const directory = resolve('../changes');
	return readdirSync(directory)
		.filter((file) => file.endsWith('.md'))
		.map((file) => {
			const text = readFileSync(resolve(directory, file), 'utf8');
			const block = text.match(FRONTMATTER);
			if (!block) throw new Error(`changes/${file} has no frontmatter`);
			return { id: file.replace(/\.md$/, ''), ...load(block[1]) };
		});
}

export function readDataYaml(name) {
	return load(readFileSync(resolve('../data', name), 'utf8'));
}
