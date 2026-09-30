---
title: Restore Android campaign data discovery
category: fix
release: 0.2.0
breaking: false
targets:
- type: system
  id: campaign-progression
  effect: changed
credit: [g0ump45]
---

Android now scans its data directories using the platform file API and uses platform separators when reading deployment folders. Campaign initialization reports failed or incomplete MIX headers and records the loaded campaign count, while scenario startup rejects an unloaded campaign instead of substituting a hardcoded mission.

Campaign selection rejects missing campaign entries before reading their scenario names. MIX caching rejects invalid header state before allocating memory and reports short reads and digest mismatches through the engine log.

Android campaign startup skips color-scheme lighting and sidebar drawing conversion when no display surface exists, avoiding crashes during theater and side initialization. Palette remapping and sidebar artwork loading remain available.

Android house initialization uses the assigned palette color for radar when the color-scheme drawing conversion is unavailable, avoiding a crash while loading scenario houses.

Android sidebar layout leaves the background empty when its drawing surface is unavailable instead of crashing while sizing it.

Terrain lighting initialization tolerates a missing display surface and clears the previous map's cached lighting references. Android drawing surfaces allocate RGB565 pixel storage without Windows GDI; presenting those surfaces on the device remains unfinished.

Building depth artwork loads from loose files or uncached MIX entries instead of requiring an archive cache. Missing files and incomplete reads are logged and leave the depth artwork unavailable.

On-demand terrain loading rejects incomplete files, invalid grid dimensions, and record headers outside the file before generating previews. Rejected terrain files are named in the engine log.

Android filename construction inserts the dot before extensions such as `TEM`, allowing terrain artwork to be discovered as `CLEAR01.TEM`. Radar colors fall back to black when tile data is unavailable.

Android startup registers the engine's object and locomotor classes before loading scenarios, allowing vehicle movement objects to be created.

Android headers preserve compiler property declarations so object type lookups call their accessors instead of reading uninitialized pointer fields during vehicle creation.
