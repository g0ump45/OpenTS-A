# Android game-file import

With game data installed, Android opens the Tiberian Sun / Firestorm selector.
The selector has no **Import Game Files** button. Firestorm requires its installed
expansion data. When game data is absent, the Android importer opens automatically
because the graphical selector itself needs game assets.

## Download during first-run setup

Choose **Game language** before downloading, then tap **Download freeware game
files** and confirm **Download**. English downloads about 1.24 GB from the
[C&C Communications Center installer](https://cnc-comm.com/tiberian-sun/downloads/the-game/installer)
and Tore's component server. Allow about 2.5 GB free.

Spanish uses the shared base game, campaign archives and music, followed by
[nacho-arg's community translation](https://forums.cncnet.org/topic/12189-spanish-translation-ts-client-605/).
It skips the three English movie packages. The total download is about 1.69 GB;
allow 4 GB free. The pack supplies Spanish game text, mission maps, speech and
movies. Firestorm movies have Spanish subtitles; some expansion content may
remain English. Some Android touch-settings and guide text remains English. German and French
use the separate verified packages described below.

Use Wi-Fi and keep the screen open. English and Spanish use their distributor packages; German and French use
prepared data-only ZIPs. Setup never executes a Windows installer. Folder and ZIP imports use the selected language
for game strings when `LANGUAGE.DLL` is supplied; that file is read as resource
data and never executed.

The screen reports download and extraction progress. **Cancel download** stops
at the next transfer or extraction checkpoint; a stalled network read can take
up to 30 seconds to time out. Retry with the same button. Partial downloads
resume when the server supports byte ranges; completed packages are retained
until setup finishes. Tap **Close game**, then reopen OpenTS-A after success.
Manual folder and ZIP import remain available through **Choose folder** and
**Choose ZIP**. Setup uses two columns in landscape and scrolls to keep text and
actions accessible on shorter screens.

Each HTTPS download has a pinned byte count and SHA-256 digest. The extractor
reads the pinned LZMA streams for shared files and verifies each game file's CRC before
staging it. If the distributor changes a package, setup stops rather than
using offsets from a different installer. Update `FreewareManifest.java` only
after checking the replacement source and extracting every listed file.

Files are staged under `.opents-freeware-downloads` in the app's external
files directory, then copied through the existing importer policy. The
`.opents-setup-pending` marker keeps interrupted setup on the import screen.
Settings, saves and executables are excluded. Staging is retained through the
final copy so retry can recover from cancellation; it is removed after success.
The APK contains the downloader and extractor, not the game data.

To test setup on a phone that already has game data, launch the exported
`.LauncherActivity` with boolean intent extra `setup_game_files=true`. This
opens the setup screen without clearing existing files. Cancelling before the
final copy leaves the installed game available.

The shared-file decoder uses [XZ for Java 1.10](https://tukaani.org/xz/java.html).
The Spanish RAR5 decoder uses libarchive 3.8.9 with a fixed file allowlist,
expected sizes and CRC checks. Its complete archive also has a pinned SHA-256.
Spanish staging uses `.opents-freeware-downloads-es`. The selected language is
saved in `.opents-game-language`; `.opents-language-managed` lists setup-owned
files so a later download can remove obsolete language files. Saves and settings
remain excluded. Existing English installations need no migration.

## Import from a ZIP on the phone

1. Copy a ZIP of your installed Tiberian Sun folder to the phone. It must contain
   `TIBSUN.MIX`; an installer, disc image, or encrypted ZIP is not supported.
2. Launch OpenTS without game data installed. On the automatic **Import Game Files**
   screen, tap **Choose ZIP**.
3. Select the ZIP once. OpenTS finds the installation inside it and copies the
   recognized game data automatically. No individual game-file selection is needed.
4. Wait for the imported-file count, tap **Close game**, then reopen OpenTS.

**Choose folder** provides the same automatic selection for a
folder accessible through Android's file picker, including supported USB storage.
Android controls which folders and storage providers the picker exposes.

## Files and storage

The destination is the app's external files directory, normally
`Android/data/com.opents.game/files`. The importer includes MIX archives,
movies, audio, maps, game definitions, and loose graphics from the installation.
It excludes executables, saved games, `SUN.INI`, `KEYBOARD.INI`, launcher spawn
files, and `DDRAW.INI`, preserving existing phone settings and saves.

The importer chooses the shallowest installation containing `TIBSUN.MIX`.
When that archive is in a client's `MIX` folder, the installation is its parent
folder, so sibling `INI` files and mission maps are included. Equally shallow
installations are ambiguous and must be supplied separately. Imported names
are uppercased and subfolders are flattened. Root files take priority, followed
by files directly inside `INI`, `MIX` or `Movies`, then other nested files.
This order applies to both folders and ZIPs. Conflicting copies at the same
priority still stop import.

Spanish mission-map briefings take priority over the shared English mission
briefing. Android supplies Spanish fallbacks for all 414 non-empty original
base-game and Firestorm tutorial message IDs: objectives, instructions, warnings,
status messages and scripted dialogue shown at the top left. Both original
wording sets and split-line messages are covered. Translated and custom text
remains unchanged; custom missions need their own translations.

The supplied Spanish package's 58 campaign maps contain no tutorial overrides;
they use this shared message set. The fallback is included in the APK, so an
existing Spanish pack needs no download. Source coverage does not replace
checking accents, line wrapping and timing during play.

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
settings and saves, root-file precedence in every scan order, ambiguous copies,
unsafe paths, and preservation of a destination after an
interrupted or oversized copy:

```powershell
javac -d "$env:TEMP/opents-import-tests" android/app/src/main/java/com/opents/game/GameFilePolicy.java tests/android_importer/GameFilePolicyTest.java
java -cp "$env:TEMP/opents-import-tests" com.opents.game.GameFilePolicyTest
```

On-device checks still cover the startup selector without an import button, automatic setup when data is absent,
Android folder and ZIP pickers, successful import, restart, and launching both
installed game modes. Use identical builds and game data on both LAN phones.

Translated engine strings are loaded after Android selects the installed game-data
folder. Early English lookups do not prevent later translated menu strings.

## German and French automatic setup

The prepared German and French downloads contain game data only. Each package
is pinned by size and SHA-256; every extracted file must match its manifest name,
size and CRC. Windows programs, settings and saves are excluded. Interrupted
downloads resume, and the selected language uses its own staging directory.

German uses original language data from MarkJFox's
[Tiberian Sun German 6.05 package](https://www.moddb.com/downloads/tiberiansungerman-605gerzip),
including names from `rulesGER.ini`. That client still supplies English unit
names; German voices, movies and string resources are included. Only `Name` values become
`LANGRULE.INI`; the client's gameplay rules are not imported.
French uses data extracted from Abandonware France's
[Tiberian Sun and Firestorm installer](https://www.abandonware-france.org/ltf_abandon/ltf_jeu.php?fic=liens&id=1262).
The Windows installer is never executed on Android.

The automatic ZIP URLs use the separate
[game-data download page](https://github.com/g0ump45/OpenTS-A/releases/tag/game-data).
Both uploaded assets match their pinned sizes and SHA-256 digests.

Android maps accented text to the original fonts using Windows-1252 and code page
437 glyph tables. Updating the APK does not require downloading the language pack again.

Spanish, French and German campaign menus use translated text buttons because the
original shell button pictures contain English labels. Game selection, campaign,
load, skirmish, network and options actions keep their existing identifiers.

On Android, missing faction aliases resolve INTRO.VQA within MOVIES01.MIX for
GDI and MOVIES02.MIX for Nod. Loose INTR1.VQA and INTR2.VQA still take precedence;
a missing faction intro does not fall back to the other faction.

The game selection screen keeps the original Tiberian Sun and Firestorm icons.
A campaign map requesting INTRO uses its player faction after the map loads;
Android does not play an additional faction intro before loading that map.

The Spanish client package contains a misleading embedded INTR1.VQA copy of
the Nod intro. Spanish faction aliases bypass that entry: GDI reads INTRO.VQA
from MOVIES01.MIX and Nod reads it from MOVIES02.MIX.

Spanish mission maps may call the Nod opening INTRON. Android recognises that
name as the faction intro; its archive content matches the Nod INTRO movie.

The first base-game campaign mission also plays its faction opening when the
map specifies neither an intro nor a briefing movie. Later missions and
Firestorm do not use this fallback.

Android touch input respects scripted mission input locks. Production and
battlefield gestures remain blocked until the mission restores control; touches
held across the unlock must be released before a new gesture starts.

Faction aliases resolve within their own movie archive for every Android language.
Options remains accessible during scripted input locks; battlefield and production
touches remain blocked.
