---
title: Android touch controls
summary: Choose and save Android touchscreen controls.
category: interface-controls
keys: []
source_files:
- code/android_controls.cpp
- code/android_controls.h
- code/android_main.cpp
- code/android_options.cpp
- code/scroll.cpp
---

Open **Options → Game Controls → Touch Controls** in the Android phone build. Changes take effect immediately and are saved after each adjustment. **Reset Controls** restores the defaults after confirmation. Rapid taps in these native menus remain left clicks, regardless of the double-tap setting.

| Setting | Default | Effect |
| --- | --- | --- |
| Double-tap gestures | On | Enables double-tap same-type selection and second-tap-drag camera panning. |
| Selection box | On | Holding and dragging can form a selection rectangle. Disabling it suppresses rectangle dragging, not tap selection. |
| Touch edge scroll | On | Holding a touch near the tactical view's edges scrolls the camera. |
| Camera speed | 8 | Sets the touch edge-scroll step from 1 to 16. Also scales second-tap-drag panning in Modern Touch. |
| Double-tap interval | 300 ms | Sets the maximum interval from the previous tap's release to the next press, from 150 to 500 ms. |

Modern Touch is the only enabled scheme. Original Touch, Classic Cursor and Advanced Touch are disabled. The **Controls Guide** lists Modern Touch gestures.

## Modern Touch

Tap a unit to select it, ground to move selected units, or an enemy to attack. Release a selection drag to finish the selection, even after a long hold or outside the game area. Cancellation or adding a second finger clears the box. Drag to form a selection box, double-tap a unit to select its type, or drag on the second tap to pan the camera. Pinch to zoom. Long-press ground for attack-move.

For a right click during gameplay, briefly place two fingers on the screen and lift both within 250 ms of the first touch. The click uses the first finger's starting position. Keep both fingers still: movement beyond the drag threshold, a third finger, or cancellation prevents the click. Pinch zoom begins when movement exceeds that threshold or the tap time expires. Two-finger right clicking is independent of the double-tap setting.

On the production sidebar, hold an icon still for at least half a second, then release to right-click it. This pauses active production; repeat on a paused item to cancel it. A short tap retains its normal left-click action. Battlefield long-press remains attack-move.

## Persistence

Settings are stored in `ANDROID-CONTROLS.cfg` in the game's user directory and loaded when the main menu first opens. Version 2 stores the scheme (0 for Original, 1 for Modern), three toggles, camera speed and double-tap interval. Version 1 and version 2 settings load with Modern Touch, including files that previously selected Original Touch. The file format and other saved adjustments remain compatible; the next save writes scheme 1. Missing, incomplete or unknown-version files use defaults; numeric speed and interval values are clamped to their supported ranges. A save failure displays a notice and leaves the changed settings active for the current session.

These settings do not change saved-game or network formats.

The minimap viewport box follows the camera position and visible battlefield crop during pinch zoom. Raised terrain does not shift its center. It shrinks when zooming in and stays within the minimap border.

Mission-triggered radar pings appear on the Android minimap even when the radar activation animation is inactive. Objective and drop-zone pings keep their original green colors and mission timing.

Pinch zoom applies to the battlefield before on-screen messages are drawn. The top bar, sidebar, and options menus keep their screen position and size.
