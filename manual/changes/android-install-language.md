---
title: Choose the game language during Android setup
category: feature
release: 0.2.0
targets:
- type: system
  id: android-touch-controls
  effect: added
credit:
- GEARS0FUMP45
---

Android setup offers English, Spanish, German and French before downloading. Spanish uses shared
base files and a community translation instead of the English movie packages.
The engine reads translated string resources as data, with English fallback for
missing or incompatible strings. Text resources load after the game-data folder
is selected; Android options labels use the selected language where translated. Accented characters map to the original font glyphs on Android. Existing installations and saves are retained.
See [Android game-file setup](../../docs/ANDROID-GAME-FILES.md) for sources,
storage requirements and remaining English content.

Spanish, French and German shell menus use translated text buttons in place of
English button artwork.

Faction opening movies resolve within their own movie archive when loose faction
copies are absent, preventing Nod intros from playing before GDI briefings.

The game selector retains the original icons. Campaign INTRO movies resolve by
the loaded player faction, without an extra opening before the map loads.

Spanish INTRON mission entries play the Nod opening through the faction lookup.

The first base-game mission retains its faction opening when both movie fields
are absent, including English installation data.

Touch input respects scripted mission control locks, including production tabs.

Spanish mission-map briefings retain their text, and unchanged base-game objective messages use Spanish fallbacks without downloading the pack again.
