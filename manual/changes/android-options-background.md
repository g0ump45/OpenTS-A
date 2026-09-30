---
title: Preserve the Android Options background
category: fix
release: 0.2.0
targets:
- type: command
  id: Options
  effect: changed
credit:
- g0ump45
---

The Android in-game Options menu displayed a black background behind Resume Mission. It now retains the paused gameplay frame, including its displayed zoom and screen shake.

The Android Options menu uses the original dialog backdrop, side rails, and button artwork. Its main screen shows the seven campaign options in a compact panel; submenus share the same artwork. The paused gameplay frame remains visible around the panel.

Android startup now opens the original graphical main menu. New Campaign opens campaign and difficulty selection, Load Mission opens saved games, Options opens settings, and Skirmish opens match setup. LAN opens a two-player Wi-Fi lobby with names, sides, host map selection, and ready status. The host can launch an experimental 1v1 match after both devices confirm matching content and gameplay connectivity. Internet and Serial / Modem remain unavailable. See [Android LAN connection preview](../../docs/ANDROID-LAN.md) for the test workflow and limits.
Android main-menu button artwork and touch areas now use the original centered 640x400 movie coordinates, correcting the displaced rectangular patches when the still backdrop includes letterboxing.

Android now renders mission shroud and fog without requiring a Windows window handle. Sidebar scroll arrows and cameo touch areas are positioned even when desktop tooltips are unavailable.

Android startup opens the Tiberian Sun / Firestorm selector when game data is present. Import Game Files opens automatic import from an installation folder or ZIP; first-run setup opens the importer when game data is absent. See [Android game-file import](../../docs/ANDROID-GAME-FILES.md) for sources, storage, and restart behavior.

Android campaign results now present the animated score screen to the phone display and accept a tap to continue. High scores use the name Player on Android, avoiding desktop keyboard entry before the normal campaign transition. Desktop score entry and campaign mission selection remain unchanged.

Android now loads PCX title-screen backgrounds and their palettes. This restores the campaign results backdrop and supplies its palette to the animated score panels.

The Android launcher now displays the name OpenTS-A and the supplied app artwork as its icon. The application ID and game-data storage location are unchanged.

Android chooses a landscape game width from the phone window at startup, keeping 480 logical pixels vertically and at least 640 horizontally. Wider screens reveal more battlefield; rendering and touch mapping use the selected dimensions. Sidebar controls and Android dialogs follow the wider layout. Movies retain their aspect ratio. Window-size changes during a session require restarting the app.

Android's Internet menu now offers direct IPv4 hosting and joining through the existing two-player lobby. It requires configured UDP forwarding and does not use a relay. See [Android direct-IP multiplayer](../../docs/ANDROID-INTERNET.md) for setup and test limits.

Android host lobbies now include Host IP, with public IPv4 lookup, copying, refresh, and separately labeled local interface addresses.

Android network menus and lobbies include Connection Help with LAN, port-forwarding, mobile-network Tailscale instructions, and troubleshooting.

Android rebuilds its cached terrain, depth, and alpha layers when cells or shroud regions are flagged for redraw, carrying the full redraw through the split render passes. This addresses stale shroud pixels that otherwise clear only after scrolling. The broader refresh can increase rendering work while exploring; stationary-camera visibility changes and performance still require phone testing.

Android manual saves now prompt for a name using an on-screen keyboard. Names accept up to 32 characters with spaces, case switching, delete, clear, and cancel. Save lists show the description before the filename. New saves keep automatically allocated filenames, and overwriting still requires confirmation. Existing save formats are unchanged.
