import { load } from 'js-yaml';
import generatedCommands from '../../../schema/generated-commands.schema.json';
import { UI } from '../i18n/en.mjs';
import { assertContract } from './schema-validator';

const RAW_COMMANDS = import.meta.glob('../../../data/commands.yaml', {
	query: '?raw',
	import: 'default',
	eager: true,
}) as Record<string, string>;

export type CommandBuild = 'release' | 'debug';
export type CommandAudience = 'player' | 'developer' | 'debug';

export interface CommandAvailability {
	builds: CommandBuild[];
}

interface CommonCommand {
	id: string;
	route_id: string;
	title: string;
	description: string;
	audience: CommandAudience;
	availability: CommandAvailability;
}

export interface RegisteredCommand extends CommonCommand {
	kind: 'registered';
	category: string;
	forced_binding?: 'Delete' | 'Escape';
}

export interface FixedControl extends CommonCommand {
	kind: 'fixed';
	bindings: string[];
	context: string;
}

export interface LaunchOption extends CommonCommand {
	kind: 'launch';
	syntax: string;
	aliases?: string[];
}

export type CommandRecord = RegisteredCommand | FixedControl | LaunchOption;

interface RawCatalog {
	registered_commands: Array<RegisteredCommand & { _provenance: unknown }>;
	fixed_controls: Array<FixedControl & { _provenance: unknown }>;
	launch_options: Array<LaunchOption & { _provenance: unknown }>;
}

let commandCache: CommandRecord[] | null = null;

function source(): string {
	const values = Object.values(RAW_COMMANDS);
	if (values.length !== 1) throw new Error(`Expected one manual/data/commands.yaml, found ${values.length}`);
	return values[0];
}

export function allCommands(): CommandRecord[] {
	if (commandCache) return commandCache;
	const raw = load(source());
	assertContract(generatedCommands, raw, 'manual/data/commands.yaml');
	const catalog = raw as RawCatalog;
	const records = [
		...catalog.registered_commands,
		...catalog.fixed_controls,
		...catalog.launch_options,
	].map(({ _provenance: _private, ...record }) => record as CommandRecord);
	const ids = new Set<string>();
	const routes = new Set<string>();
	for (const record of records) {
		if (ids.has(record.id)) throw new Error(`Duplicate command ID: ${record.id}`);
		if (routes.has(record.route_id)) throw new Error(`Duplicate command route: ${record.route_id}`);
		ids.add(record.id);
		routes.add(record.route_id);
	}
	commandCache = records;
	return commandCache;
}

export function commandById(identifier: string): CommandRecord | undefined {
	return allCommands().find((record) => record.id === identifier);
}

export function commandByRoute(route: string): CommandRecord | undefined {
	return allCommands().find((record) => record.route_id === route);
}

export function requireCommand(identifier: string, context: string): CommandRecord {
	const record = commandById(identifier);
	if (!record) throw new Error(`${context}: unknown command "${identifier}"`);
	return record;
}

export function commandRoute(record: CommandRecord): string {
	return record.kind === 'launch'
		? `/using/command-line/${record.route_id}/`
		: `/commands/${record.route_id}/`;
}

export function commandHref(identifier: string): string | undefined {
	const record = commandById(identifier);
	return record ? commandRoute(record) : undefined;
}

export function commandLabel(identifier: string): string {
	return commandById(identifier)?.title ?? identifier;
}

export function commandKindLabel(kind: CommandRecord['kind']): string {
	return UI.commandKinds[kind];
}

export function commandAvailabilityLabel(availability: CommandAvailability): string {
	return availability.builds.map((build) => build === 'release' ? 'Release' : 'Debug').join(' and ');
}
