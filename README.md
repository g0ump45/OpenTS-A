# OpenTS-A

An Android port of [OpenTS](https://github.com/OpenTS-Developers/OpenTS), maintained by **GEARS0FUMP45**, for Command & Conquer: Tiberian Sun and Firestorm.

This port adds Modern Touch controls, phone menus, game-file importing, pinch zoom, campaign audio support and Android LAN multiplayer work. Development continues: sidebar video playback and minimap alignment need further device testing and refinement. More updates will follow, and more projects by GEARS0FUMP45 may come soon.

## Install

1. Use **Android 8.0 or newer on a 64-bit ARM device**. Download the APK from [Releases](https://github.com/g0ump45/OpenTS-A/releases/latest) and allow installation when Android asks.
2. On first launch, choose your game language and tap **Download freeware game files**. Keep the setup screen open until installation finishes. You can also import the game-files ZIP from [Releases](https://github.com/g0ump45/OpenTS-A/releases), or choose an existing game folder or ZIP.
3. Open **Options > Game Controls > Touch Controls > Controls Guide** for instructions. Mouse and keyboard instructions are included there too.

See [game-file requirements](docs/ANDROID-GAME-FILES.md) and [Android build instructions](docs/ANDROID-BUILD.md).

The V1 APK uses a release signing key. Earlier debug builds use a different key;
Android requires uninstalling those before installing V1. Export saves and game
files first, because uninstalling can remove app data.

## Modern Touch

Modern Touch is the enabled default; saved control adjustments remain compatible.

| Gesture | Action |
| --- | --- |
| Tap a unit | Select |
| Tap ground / enemy | Move / attack with selected units |
| Hold and drag | Pan the camera by default |
| Double-tap a unit | Select the same type |
| Drag on the second tap | Selection box by default |
| Pinch | Zoom the battlefield |
| Long-press ground | Attack-move |
| Stationary two-finger tap, lifting both within 250 ms | Right-click at the first finger's position |
| Hold a production icon for 0.5 seconds, then release | Pause production; repeat to cancel |
| Touch near a battlefield edge | Scroll, when enabled |

Tap **[+]** on the battlefield for groups 1-9. Tap a number to recall it or hold it for half a second and release to assign selected units. **Base** centres the camera. Set the panel to Bottom, Top or Hidden in Touch Controls.

USB and Bluetooth mice/keyboards use physical clicks, drag selection and standard game shortcuts. The mouse wheel zooms the battlefield. Shift/Ctrl/Alt combinations and US-layout text entry are supported; touch controls remain available.

Turn **Swap pan / box drag** off to use single-drag selection and second-tap camera panning.

See the [touch-control guide](manual/content/systems/android-touch-controls.md) for settings.

## Support

Support is optional. All features stay free; donations do not buy game files or content. Visit [Ko-fi](https://ko-fi.com/gears0fump45) or [GitHub Sponsors](https://github.com/sponsors/g0ump45). In a mission, open **Options > About OpenTS-A > Support Development**. From the main menu, open **Options > Game Controls > About OpenTS-A**.

## Credits and licence

Credit to the [OpenTS developers](https://github.com/OpenTS-Developers/OpenTS) for the engine this port builds on. **Westwood Studios** created Tiberian Sun and Firestorm; **Electronic Arts** published them. OpenTS-A is unofficial and is not affiliated with or endorsed by Electronic Arts.

See [LICENSE.md](LICENSE.md) for GPLv3 and additional terms, and the included third-party notices. Game names and assets belong to their respective rights holders.
