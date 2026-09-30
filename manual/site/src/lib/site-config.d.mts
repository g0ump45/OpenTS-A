export interface SiteConfig {
	readonly site: string;
	readonly base: string;
	readonly repositoryUrl: string;
	readonly revision: string;
	readonly demo: boolean;
}

export function resolveSiteConfig(env?: Readonly<Record<string, string | undefined>>): SiteConfig;
export const siteConfig: SiteConfig;
export function sourceFileUrl(path: string, config?: SiteConfig): string;
