# Android APK updates

From the main menu, open **Options**, then **Check for updates**. The check uses
GitHub's latest published stable release for `g0ump45/OpenTS-A`; drafts and
prereleases are excluded. A network or rate-limit failure can be retried.

The update screen shows the installed version and the newer release's notes.
Tap **Download update**, then confirm the download size. The APK is downloaded
to private app cache. It must match the release's size and SHA-256 digest, the
installed package name and signing certificate, and a newer Android version
code. Missing checksums or multiple APK assets stop automatic selection.

Android asks the player to approve installation. If necessary, enable **Allow
from this source** for OpenTS-A, then return to the update screen. Cancelling
leaves the current app installed. The updater does not uninstall the app or
change game files, language packs, saves or controls. It is disabled during a
mission; return to the main menu before updating.

**Check for updates on startup** is optional and off by default. Enabling it
opens the update screen before the game on later launches. Downloads require
confirmation. **Back** starts the game or returns to its main menu. Leaving
during a download cancels it; retry downloads the APK again. Updates need an
internet connection and free cache space. Downloads are limited to 64 MiB.

For a release, attach one signed APK with a higher version code. Keep the signing
certificate unchanged and verify GitHub supplies the asset's SHA-256 digest.
A stable release with the same numeric version as an installed preview is
eligible when its Android version code is higher.

Device checks: verify offline retry, up-to-date status, a newer signed download,
unknown-source permission denial and approval, installer cancellation, and
successful replacement with game files and settings retained. Host and build
checks do not establish these device results.

Certificate checks request both current and legacy signing information. If
Android omits the current signer details, the legacy certificate must still
match the installed app. Missing certificates stop installation with an error.
The staged download retains an APK extension for Android archive inspection.
