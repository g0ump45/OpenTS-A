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
