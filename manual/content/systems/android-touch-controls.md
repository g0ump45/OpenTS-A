---
title: Android touch controls
summary: Choose and save Android touchscreen controls.
category: interface-controls
keys: []
source_files:
- code/android_controls.cpp
- code/android_controls.h
- code/android_main.cpp
- code/foot.cpp
- code/android_options.cpp
- code/scroll.cpp
---

Open **Options ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ Game Controls ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ Touch Controls** in the Android phone build. Changes take effect immediately and are saved after each adjustment. **Reset Controls** restores the defaults after confirmation. Rapid taps in these native menus remain left clicks, without waiting for the double-tap interval.

| Setting | Default | Effect |
| --- | --- | --- |
| Swap pan / box drag | On | Swaps battlefield drag gestures: hold-and-drag pans; second-tap-and-drag selects a box. |
| Touch edge scroll | On | Holding a touch near the tactical view's edges scrolls the camera. |
| Camera speed | 8 | Sets the touch edge-scroll step from 1 to 16. Also scales drag panning in either Modern Touch layout. |
| Double-tap interval | 300 ms | Sets the maximum interval from the previous tap's release to the next press, from 150 to 500 ms. |

Modern Touch is the only enabled scheme. Original Touch, Classic Cursor and Advanced Touch are disabled. The **Controls Guide** lists Modern Touch gestures.

## Modern Touch

Tap a unit to select it, ground to move selected units, or an enemy to attack. Release a selection drag to finish the selection, even after a long hold or outside the game area. Cancellation or adding a second finger clears the box. By default, hold and drag to pan; drag on the second tap to form a selection box. Double-tap a unit to select its type. Pinch to zoom. Long-press ground for attack-move.

For a right click during gameplay, briefly place two fingers on the screen and lift both within 250 ms of the first touch. The click uses the first finger's starting position. Keep both fingers still: movement beyond the drag threshold, a third finger, or cancellation prevents the click. Pinch zoom begins when movement exceeds that threshold or the tap time expires. Two-finger right clicking does not use the double-tap interval.

On the production sidebar, hold an icon still for at least half a second, then release to right-click it. This pauses active production; repeat on a paused item to cancel it. A short tap retains its normal left-click action. Battlefield long-press remains attack-move.

With **Swap pan / box drag** enabled, hold and drag once to pan; tap, then hold
and drag the second touch to draw a selection box. A stationary long-press
still issues attack-move. Tap orders, pinch zoom, sidebar holds and two-finger
right-click keep their existing actions. The swap only applies to touches
starting in the battlefield. Box selection and double-tap gestures are always enabled. Battlefield taps wait for the configured double-tap interval before issuing an order; dragging the second tap cancels the first order. Menus and production taps remain immediate.

## Tactical shortcuts

Tap **[+]** to open groups 1â€“9. Hold a number for half a second and release to assign selected units; tap it to recall the group. Tap **[-]** to fold the panel away or **Base** to centre on your base. Dragging away, adding a finger or cancelling the touch cancels the shortcut.

In **Touch Controls**, cycle **Tactical shortcuts** between Bottom (default), Top and Hidden. Buttons stay fixed during zoom and are disabled during videos, menus and scripted input locks.

## Persistence

Settings are stored in `ANDROID-CONTROLS.cfg`. Version 3 adds shortcut placement after the existing swap-drag field (0 hidden, 1 bottom, 2 top). Version 1 and 2 files retain their gesture settings and default to bottom placement. Modern Touch remains the only enabled scheme. Missing or incomplete files use defaults; numeric settings are clamped. The next save writes version 3. Older versions cannot read version 3 and reset controls to defaults. Game files and saves are unchanged.

These settings do not change saved-game or network formats.

The minimap viewport box follows the camera position and visible battlefield crop during pinch zoom. Raised terrain does not shift its center. It shrinks when zooming in and stays within the minimap border.

Mission-triggered radar pings appear on the Android minimap even when the radar activation animation is inactive. Objective and drop-zone pings keep their original green colors and mission timing.

Pinch zoom applies to the battlefield before on-screen messages are drawn. The top bar, sidebar, and options menus keep their screen position and size.

## Fullscreen play

The game hides Android's status and navigation bars, including Back, Home and
Recent Apps. Swipe from a screen edge to reveal them temporarily. They hide
again after returning to the game. File import screens keep normal navigation.

Audio pauses when the app loses focus or enters the background and resumes when the game returns to the foreground.

Attack-move continues toward its destination when the patrol scan finds no enemy. A cleared combat target follows the existing rescan and return behavior.

## Game-file setup

Choose the game language before downloading files. See
[Android game-file setup](../../../docs/ANDROID-GAME-FILES.md) for available
languages, source downloads and storage requirements.

## Mouse and keyboard

USB and Bluetooth hardware input uses mouse movement, left/right/middle buttons, left-drag selection and keyboard commands. The wheel zooms the battlefield. Letter, number, function, navigation and modifier keys use the engine shortcuts. Text fields support US-layout letters and punctuation. Device system buttons remain with Android. Touch controls remain available. Held keys and buttons clear when the app loses focus.

## Hardware pointer and display

Physical mice use the game cursor artwork in menus and on the battlefield, including targeting and animated action cursors. Android's pointer remains available if the artwork cannot be loaded. The cursor is drawn after battlefield zoom and does not leave marks in the cached map image.

Mouse edge scrolling uses the outermost pixels of the visible battlefield. The production sidebar and letterbox space never count as battlefield edges. Touch scrolling keeps its wider drag zones.

The keyboard shortcut picker includes Up, Down, Left and Right on the function-key page. Arrow bindings support Shift, Ctrl and Alt and use the existing KEYBOARD.INI format.

Open **Game Controls > Display** to choose Auto, the current native display size, a common phone/tablet resolution, or a custom width and height. The screen shows active and saved dimensions separately and marks pending changes as requiring an app restart. Returning to the main menu does not apply them.

The custom editor accepts on-screen digits, keyboard digits and number-pad digits. Select Width or Height, or use Tab/Left/Right to switch fields; Backspace deletes and Enter saves. The first digit replaces the selected value. Valid sizes are landscape or square, at least 640x480, no greater than 3840x2400, and at most 8,294,400 pixels. High resolutions use more memory and can reduce performance.

Exact sizes retain their aspect ratio; black bars fill unused screen space. Higher sizes show more battlefield. Menus use a separate 640x480 presentation canvas scaled to the window, so text and buttons stay readable at native and custom resolutions. Mouse and touch positions follow the same menu transform. Pinch zoom remains independent. ANDROID-DISPLAY.cfg stores either an old preset number (0-3), or `4 width height` for an exact size. Old preset files remain readable; invalid exact sizes fall back to Auto. Changes apply after fully stopping and restarting the app.

Menu headings, labels and enabled options use white text with a black font shadow. Disabled actions remain grey. Menu scaling and pointer hit positions are independent of the selected battlefield resolution.
