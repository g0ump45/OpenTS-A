# OpenTS-A

An Android port of [OpenTS](https://github.com/OpenTS-Developers/OpenTS), maintained by **GEARS0FUMP45**, for Command & Conquer: Tiberian Sun and Firestorm.

This port adds Modern Touch controls, phone menus, game-file importing, pinch zoom, campaign audio support and Android LAN multiplayer work. Development continues: sidebar video playback and minimap alignment need further device testing and refinement. More updates will follow, and more projects by GEARS0FUMP45 may come soon.

## Install

1. Use **Android 8.0 or newer on a 64-bit ARM device**. Install the OpenTS-A APK and allow installation from your file manager when Android asks. Download [V1 - Welcome Back Commander](https://github.com/g0ump45/OpenTS-A/releases/tag/v1.0.0).
2. Supply your own Tiberian Sun files, plus expansion files for Firestorm. Keep movie and speech archives for videos and spoken objectives. Game assets are not included here.
3. Put the game files in a ZIP. Open the app: when files are missing, the importer opens automatically. Choose the ZIP, finish importing, then start the game.
4. Open **Options > Game Controls > Touch Controls > Controls Guide** for help. Back up saves before replacing test builds.

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
| Drag | Selection box; release to finish |
| Double-tap a unit | Select the same type |
| Drag on the second tap | Pan the camera |
| Pinch | Zoom the battlefield |
| Long-press ground | Attack-move |
| Stationary two-finger tap, lifting both within 250 ms | Right-click at the first finger's position |
| Hold a production icon for 0.5 seconds, then release | Pause production; repeat to cancel |
| Touch near a battlefield edge | Scroll, when enabled |

See the [touch-control guide](manual/content/systems/android-touch-controls.md) for settings.

## Support

Support is optional. All features stay free; donations do not buy game files or content. Visit [Ko-fi](https://ko-fi.com/gears0fump45) or [GitHub Sponsors](https://github.com/sponsors/g0ump45). In a mission, open **Options > About OpenTS-A > Support Development**. From the main menu, open **Options > Game Controls > About OpenTS-A**.

## Credits and licence

Credit to the [OpenTS developers](https://github.com/OpenTS-Developers/OpenTS) for the engine this port builds on. **Westwood Studios** created Tiberian Sun and Firestorm; **Electronic Arts** published them. OpenTS-A is unofficial and is not affiliated with or endorsed by Electronic Arts.

See [LICENSE.md](LICENSE.md) for GPLv3 and additional terms, and the included third-party notices. Game names and assets belong to their respective rights holders.
