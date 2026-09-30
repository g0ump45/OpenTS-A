# Build OpenTS-A for Android

The Android port uses Java 17, Gradle 8.5, Android Gradle Plugin 8.2.2,
Android SDK 34, NDK 26.1.10909125 and CMake 3.31.6. Install those SDK tools
through Android Studio. Install Gradle 8.5 separately and put its bin directory
on PATH. The APK targets arm64-v8a and Android 8.0 or newer.

Clone with dependencies:

```sh
git clone --recurse-submodules https://github.com/g0ump45/OpenTS-A.git
cd OpenTS-A
```

Set JAVA_HOME to Java 17 and configure your Android SDK through
ANDROID_HOME or an untracked android/local.properties file. From Windows:

```powershell
gradle.bat -p android --no-daemon assembleDebug
```

The output is android/app/build/outputs/apk/debug/app-debug.apk. A debug
APK uses a local debug signing key. Public updates need a stable signing key;
never commit that key. Game assets are not needed to compile and are not
included in the APK.

This Android port is experimental. A successful build does not prove device
behavior. The upstream Windows build instructions are in [BUILDING.md](BUILDING.md).

Optional support links live in code/android_support.h. They open the system
browser with ACTION_VIEW; no payment SDK, tracking library or new permission
is added. The support page is reached through Options > About OpenTS-A during
a mission, or Options > Game Controls > About OpenTS-A from the main menu.
Donations do not alter gameplay or unlock content. The GitHub funding button
is configured in .github/FUNDING.yml. GitHub Sponsors requires enrollment by
the account owner.

## Release APK

Build the unsigned release variant with Gradle 8.5:

```powershell
gradle.bat -p android --no-daemon assembleRelease
```

Sign android/app/build/outputs/apk/release/app-release-unsigned.apk with
Android SDK Build Tools apksigner and a privately stored release keystore.
Pass passwords through protected environment variables, not command arguments.
Verify the result with apksigner verify --verbose --print-certs before publishing.
Keep the keystore and its password backed up privately; future updates must use
the same signing key. Never put either in the repository or release assets.

V1 uses versionName 1.0.0 and versionCode 2. It uses a different certificate from
the earlier debug APKs, so installing over those is not supported. Export saves
and game files before uninstalling a debug build.

Android native compilation enables Clang MS extensions in every configuration,
including the RelWithDebInfo configuration used by the APK release variant.

The corrected V1 APK uses versionName 1.0.1 and versionCode 4 with the original
release signing key. All Android configurations package the engine as
libGameD.so, matching the NativeActivity manifest. The original release APK
used a different native library filename and could not start. The hotfix also
checks for a missing source object before updating smoke effects.
