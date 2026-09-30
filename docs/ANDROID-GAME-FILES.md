# Android game-file import

With game data installed, Android opens the Tiberian Sun / Firestorm selector.
The selector has no **Import Game Files** button. Firestorm requires its installed
expansion data. When game data is absent, the Android importer opens automatically
because the graphical selector itself needs game assets.

## Import from a ZIP on the phone

1. Copy a ZIP of your installed Tiberian Sun folder to the phone. It must contain
   `TIBSUN.MIX`; an installer, disc image, or encrypted ZIP is not supported.
2. Launch OpenTS without game data installed. On the automatic **Import Game Files**
   screen, tap **Choose installation ZIP**.
3. Select the ZIP once. OpenTS finds the installation inside it and copies the
   recognized game data automatically. No individual game-file selection is needed.
4. Wait for the imported-file count, tap **Close game**, then reopen OpenTS.

**Choose installation folder** provides the same automatic selection for a
folder accessible through Android's file picker, including supported USB storage.
Android controls which folders and storage providers the picker exposes.

## Files and storage

The destination is the app's external files directory, normally
`Android/data/com.opents.game/files`. The importer includes MIX archives,
movies, audio, maps, game definitions, and loose graphics from the installation.
It excludes executables, saved games, `SUN.INI`, `KEYBOARD.INI`, launcher spawn
files, and `DDRAW.INI`, preserving existing phone settings and saves.

The importer chooses the shallowest folder containing `TIBSUN.MIX`. Equally
shallow installations are ambiguous and must be supplied separately. Imported
names are uppercased and subfolders are flattened; a root-level file takes
precedence over a nested file of the same name. Other filename collisions are
rejected rather than guessed.

A ZIP is temporarily copied into app cache before extraction. Leave enough
space for this copy and the imported files. ZIP size and total copied data are
each limited to 8 GiB, with at most 10,000 ZIP entries. Folder scanning also
limits depth and entry counts.

Each destination file is replaced only after its copy finishes. If an import
stops, completed files remain; retry the source to finish. The entire import is
not a single transaction. After any files are copied, close and reopen the game
to reload its asset caches. Import success reports copying, not a complete
validation of the supplied installation.

## Mission speech and movies

Mission objective narration is loaded from `VoiceOver` entries in `MISSION.INI` and the expansion mission INI. Restate Briefing plays the referenced AUD file from the options menu. Mission-scripted speech retains its original timing; Android adds no extra startup recording. A missing entry or file leaves the text briefing available in the menu.

Keep both `SIDECD01.MIX` and `SIDECD02.MIX` for base-game narration, and `MOVIES01.MIX`, `MOVIES02.MIX` and `MOVIES03.MIX` for base-game and Firestorm FMVs. The faction opening movies share the name `INTRO.VQA` in their separate archives; loose `INTR1.VQA` and `INTR2.VQA` copies let the player select the matching opening movie in a combined installation. Import accepts these AUD, VQA and MIX files.

## Validation

The asset-free Java test checks automatic selection, root detection, excluded
settings and saves, unsafe paths, and preservation of a destination after an
interrupted or oversized copy:

```powershell
javac -d "$env:TEMP/opents-import-tests" android/app/src/main/java/com/opents/game/GameFilePolicy.java tests/android_importer/GameFilePolicyTest.java
java -cp "$env:TEMP/opents-import-tests" com.opents.game.GameFilePolicyTest
```

On-device checks still cover the startup selector without an import button, automatic setup when data is absent,
Android folder and ZIP pickers, successful import, restart, and launching both
installed game modes. Use identical builds and game data on both LAN phones.
