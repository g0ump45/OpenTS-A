import { readFileSync, readdirSync } from 'node:fs';
import { resolve } from 'node:path';

const html = (relative) => readFileSync(resolve('dist', relative), 'utf8');
const requireText = (source, text, context) => {
	if (!source.includes(text)) throw new Error(`${context} is missing ${JSON.stringify(text)}`);
};
const rejectText = (source, text, context) => {
	if (source.includes(text)) throw new Error(`${context} still contains ${JSON.stringify(text)}`);
};

const direct = html('keys/aa/index.html');
requireText(direct, '<dt>Section</dt><dd><code>[&lt;ObjectType ID&gt;]</code></dd>', 'Direct key specification');
rejectText(direct, 'Loaded through', 'Direct key specification');
rejectText(direct, 'Image ID: Image= value; ObjectType ID when omitted', 'Direct key specification');

const image = html('keys/fireangle/index.html');
requireText(image, '<dt>Section</dt><dd><code>[&lt;Image ID&gt;]</code><small>Image ID: Image= value; ObjectType ID when omitted</small></dd>', 'Image key specification');
requireText(image, '<th>Order</th><th>File</th><th>Section</th>', 'Secondary read table');
requireText(image, '<code>[&lt;ObjectType ID&gt;]</code>', 'Secondary direct read');

const art = html('reference/art/buildingtype/index.html');
requireText(art, 'Image-selected sections only', 'Art reference filter');
requireText(art, '<th>Image-selected section</th>', 'Art reference table');
requireText(art, 'data-via-image="yes"', 'Art reference table');
requireText(art, 'data-via-image="no"', 'Art reference table');

for (const [relative, title, selector] of [
	['reference/other/campaign/index.html', 'Campaign sections in BATTLE*.INI', '[&lt;Campaign ID&gt;]'],
	['reference/other/sounds/index.html', 'Sound sections in SOUND.INI / SOUND01.INI', '[&lt;Sound ID&gt;]'],
	['reference/other/themes/index.html', 'Theme sections in THEME.INI + THEME01.INI', '[&lt;Theme ID&gt;]'],
]) {
	const source = html(relative);
	requireText(source, title, relative);
	requireText(source, selector, relative);
}

const map = html('mapping/scenario/map/index.html');
requireText(map, '[Map]', 'Merged map section');
requireText(map, '<code>Fill</code>', 'Merged map section');
requireText(map, '<code>Theater</code>', 'Merged map section');

const pilot = html('systems/base-adjacency/index.html');
requireText(pilot, '<figure class="frame has-title not-content"><figcaption class="header"><span class="title">rules.ini</span></figcaption>', 'Pilot INI frame');
requireText(pilot, 'BaseNormal=no', 'Pilot INI frame');
requireText(pilot, 'Adjacent=5', 'Pilot INI frame');
requireText(pilot, '<aside aria-label="Adjacent zero still permits contact" class="starlight-aside starlight-aside--note">', 'Pilot aside');
rejectText(pilot, ':::note', 'Pilot aside');

const rejected = [
	'Loaded through',
	'Behavioral explanation wanted',
	'traced, reviewed explanation',
	'Generated specification',
	'Authored behavior',
	'extracted specification',
	'the generated fields',
	"the object's own entry",
	"the entry named by this object's Image=",
	"the campaign's own entry",
	"the sound's own entry",
	"the theme's own entry",
	'Help improve this page',
	'Browse the manual',
	"What's new",
	'Explanation wanted',
	'Evidence boundary',
	'source-traced; not runtime-tested',
	'illustrative, not recommended',
	'default or recommendation',
	'One action record. Replace values in angle brackets.',
	'There are no focused automated tests',
];
for (const relative of readdirSync(resolve('dist'), { recursive: true })) {
	if (!relative.endsWith('.html')) continue;
	const source = html(relative);
	for (const phrase of rejected) rejectText(source, phrase, relative);
}

console.log('OK       selector presentation and processed Markdown render contracts');
