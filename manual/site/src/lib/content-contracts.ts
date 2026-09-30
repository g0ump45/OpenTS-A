import { z } from 'astro/zod';
import authoredChange from '../../../schema/authored-change.schema.json';
import authoredCommand from '../../../schema/authored-command.schema.json';
import authoredEnum from '../../../schema/authored-enum.schema.json';
import authoredFormat from '../../../schema/authored-format.schema.json';
import authoredGuide from '../../../schema/authored-guide.schema.json';
import authoredInternal from '../../../schema/authored-internal.schema.json';
import authoredKey from '../../../schema/authored-key.schema.json';
import authoredScripting from '../../../schema/authored-scripting.schema.json';
import authoredSystem from '../../../schema/authored-system.schema.json';
import authoredUsing from '../../../schema/authored-using.schema.json';
import { contractErrors } from './schema-validator';
import type { FormatData } from './formats';
export type { FormatData } from './formats';

export type SystemCategory = 'combat-targeting' | 'units-movement' | 'buildings-economy' | 'weapons-projectiles' | 'superweapons-special' | 'ai-teams' | 'maps-scenarios' | 'interface-controls' | 'rendering-presentation' | 'audio-speech' | 'multiplayer-networking' | 'tools-diagnostics';
export type GuideCategory = 'setup' | 'configuration' | 'files-formats' | 'compatibility-migration' | 'troubleshooting';
export type UsingCategory = 'getting-started' | 'configuration' | 'compatibility-migration' | 'troubleshooting';
export type InternalCategory = 'architecture' | 'simulation-systems' | 'data-scripting' | 'rendering-media' | 'networking-persistence';
export type LifecycleEntityType = 'key' | 'action' | 'event' | 'mission' | 'format' | 'enum' | 'system' | 'command';
export type RelatedEntityType = LifecycleEntityType | 'guide' | 'using' | 'internal';
export type LifecycleEffect = 'added' | 'changed' | 'deprecated' | 'removed';
export type EntityReference<T extends RelatedEntityType = RelatedEntityType> = { type: T; id: string; scope?: string };
export type WhenOmitted =
	| { kind: 'value'; value: string; note?: string }
	| { kind: 'computed' | 'inherited' | 'unchanged' | 'context-dependent'; note: string };
export interface CommandData { command_id: string }
export interface KeyProseData { key: string; scope?: string; label?: string; summary?: string; when_omitted?: WhenOmitted; no_effect: boolean; see_also: string[] }
export interface GuideData { title: string; summary: string; category: GuideCategory; uses_keys: string[]; prerequisites: string[]; related: EntityReference[] }
export interface SystemData { title: string; summary: string; category: SystemCategory; keys: string[]; related: EntityReference[] }
export interface UsingData { title: string; summary: string; category: UsingCategory; source_files: string[]; related: EntityReference[] }
export interface InternalData { title: string; summary: string; category: InternalCategory; source_files: string[]; related: EntityReference[] }
export interface EnumData { enum_id: string; slug: string; title: string; summary: string; representation: 'token' | 'integer'; bindings: { key_value_types: string[]; scripting_parameter_types: string[] }; source_files: string[]; values: Array<{ constant: string; value: number; input: string; meaning: string; note?: string }> }
export interface ScriptingData { type: 'action' | 'event' | 'mission'; id: string; title: string; summary: string; valid_values: string[]; caveats: string[]; related: EntityReference[] }
export interface ChangeData { title: string; category: 'feature' | 'fix' | 'balance' | 'internal' | 'performance'; release: string; breaking: boolean; migration: string[]; targets: Array<EntityReference<LifecycleEntityType> & { effect: LifecycleEffect }>; credit: string[] }

function pointerPath(error: { instancePath: string; keyword: string; params: Record<string, unknown> }): (string | number)[] {
	const parts = error.instancePath
		.split('/')
		.slice(1)
		.map((part) => part.replace(/~1/g, '/').replace(/~0/g, '~'));
	if (error.keyword === 'required' && typeof error.params.missingProperty === 'string') {
		parts.push(error.params.missingProperty);
	}
	return parts.map((part) => /^\d+$/.test(part) ? Number(part) : part);
}

function contract<T>(jsonSchema: object, normalize: (value: Record<string, unknown>) => T) {
	return z.record(z.string(), z.unknown()).superRefine((value, context) => {
		for (const error of contractErrors(jsonSchema, value)) {
			context.addIssue({
				code: 'custom',
				path: pointerPath(error),
				message: error.message ?? 'does not satisfy the shared documentation contract',
			});
		}
	}).transform(normalize);
}

const cast = <T>(defaults: Partial<T>) => (value: Record<string, unknown>): T => ({ ...defaults, ...value }) as T;

export const commandSchema = contract(authoredCommand, cast<CommandData>({}));
export const formatSchema = contract(authoredFormat, cast<FormatData>({ related: [], key_scopes: [] }));
export const keyProseSchema = contract(authoredKey, cast<KeyProseData>({ no_effect: false, see_also: [] }));
export const guideSchema = contract(authoredGuide, cast<GuideData>({ uses_keys: [], prerequisites: [], related: [] }));
export const systemSchema = contract(authoredSystem, cast<SystemData>({ keys: [], related: [] }));
export const usingSchema = contract(authoredUsing, cast<UsingData>({ related: [] }));
export const internalSchema = contract(authoredInternal, cast<InternalData>({ related: [] }));
export const enumSchema = contract(authoredEnum, cast<EnumData>({}));
export const scriptingSchema = contract(authoredScripting, cast<ScriptingData>({ valid_values: [], caveats: [], related: [] }));
export const changeSchema = contract(authoredChange, cast<ChangeData>({ breaking: false, migration: [], targets: [], credit: [] }));
