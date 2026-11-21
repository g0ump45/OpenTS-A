package com.opents.game;

import android.app.*;
import android.content.*;
import android.content.pm.*;
import android.net.Uri;
import android.os.*;
import android.provider.Settings;
import android.widget.*;
import org.json.*;
import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.util.*;

public class UpdatesActivity extends Activity {
    private TextView status;
    private Button check, update;
    private volatile boolean cancelled;
    private boolean busy, waitingPermission, ready;
    private String address, digest, latest;
    private long bytes;
    private File apk;

    @Override public void onCreate(Bundle state) {
        super.onCreate(state);
        apk = new File(getCacheDir(), "update.apk");
        LinearLayout content = new LinearLayout(this);
        content.setOrientation(LinearLayout.VERTICAL);
        content.setPadding(24, 24, 24, 24);
        ScrollView scroll = new ScrollView(this); scroll.addView(content); setContentView(scroll);
        status = new TextView(this); status.setTextSize(18); content.addView(status);
        CheckBox startup = new CheckBox(this); startup.setText("Check for updates on startup");
        startup.setChecked(getSharedPreferences("updates", MODE_PRIVATE).getBoolean("startup", false));
        startup.setOnCheckedChangeListener((v, selected) -> getSharedPreferences("updates", MODE_PRIVATE).edit().putBoolean("startup", selected).apply());
        content.addView(startup);
        check = new Button(this); check.setText("Check for updates"); content.addView(check);
        check.setOnClickListener(v -> check());
        update = new Button(this); update.setText("Download update"); update.setEnabled(false); content.addView(update);
        update.setOnClickListener(v -> { if (ready) install(); else new AlertDialog.Builder(this).setTitle("Download " + latest + "?")
            .setMessage("Download size: " + ((bytes + 1048575) / 1048576) + " MB. Android will ask you to confirm installation. Game files and saves are kept.")
            .setNegativeButton("Cancel", null).setPositiveButton("Download", (d, w) -> download()).show(); });
        Button back = new Button(this); back.setText("Back"); content.addView(back); back.setOnClickListener(v -> leave());
        check();
    }
    private String current() throws PackageManager.NameNotFoundException {
        return getPackageManager().getPackageInfo(getPackageName(), 0).versionName;
    }
    private void show(String text) { runOnUiThread(() -> { if (!isFinishing() && !isDestroyed()) status.setText(text); }); }
    private void active(boolean value) {
        busy = value; check.setEnabled(!value); update.setEnabled(!value && address != null);
    }
    private HttpURLConnection connection(String url) throws IOException {
        URL target = new URL(url);
        if (!"https".equals(target.getProtocol())) throw new IOException("Update requires HTTPS.");
        HttpURLConnection c = (HttpURLConnection)target.openConnection();
        c.setConnectTimeout(15000); c.setReadTimeout(30000);
        c.setRequestProperty("User-Agent", "OpenTS-A updater");
        c.setRequestProperty("Accept", "application/vnd.github+json");
        return c;
    }
    private void check() {
        if (busy) return;
        address = null; ready = false; update.setText("Download update"); active(true); show("Checking published GitHub releases...");
        new Thread(() -> {
            try {
                HttpURLConnection c = connection("https://api.github.com/repos/g0ump45/OpenTS-A/releases/latest");
                String json;
                try {
                    if (c.getResponseCode() != 200) throw new IOException("Update check unavailable (HTTP " + c.getResponseCode() + "). Retry later.");
                    try (InputStream input = c.getInputStream(); ByteArrayOutputStream output = new ByteArrayOutputStream()) {
                        byte[] buffer = new byte[8192]; int count;
                        while ((count = input.read(buffer)) != -1) {
                            if (cancelled) return;
                            if (output.size() + count > 1024 * 1024) throw new IOException("Release information is too large.");
                            output.write(buffer, 0, count);
                        }
                        json = output.toString(StandardCharsets.UTF_8.name());
                    }
                } finally { c.disconnect(); }
                JSONObject release = new JSONObject(json);
                if (release.getBoolean("draft") || release.getBoolean("prerelease")) throw new IOException("No stable release is available.");
                latest = release.getString("tag_name");
                if (UpdatePolicy.compare(latest, current()) <= 0) { show("Installed: " + current() + "\nYou are up to date."); return; }
                JSONArray assets = release.getJSONArray("assets"); JSONObject candidate = null;
                for (int i = 0; i < assets.length(); i++) {
                    JSONObject item = assets.getJSONObject(i);
                    if (!item.getString("name").endsWith(".apk") || !"uploaded".equals(item.getString("state"))) continue;
                    if (candidate != null) throw new IOException("Release has multiple APKs. Please choose one on GitHub.");
                    candidate = item;
                }
                if (candidate == null) throw new IOException("This release has no APK attached.");
                String url = candidate.getString("browser_download_url"), hash = candidate.getString("digest");
                long size = candidate.getLong("size"); UpdatePolicy.asset(url, size, hash);
                bytes = size; digest = hash.substring(7); address = url;
                show("Installed: " + current() + "\nAvailable: " + latest + "\n\n" + release.optString("body", ""));
            } catch (Exception e) { show("Could not check for updates: " + e.getMessage()); }
            finally { runOnUiThread(() -> active(false)); }
        }, "OpenTS-update-check").start();
    }
    private void download() {
        if (busy || address == null) return;
        active(true); ready = false;
        new Thread(() -> {
            File temporary = new File(getCacheDir(), "update.part.apk");
            try {
                if (getCacheDir().getUsableSpace() < bytes * 2) throw new IOException("Not enough free space for this update.");
                MessageDigest hash = MessageDigest.getInstance("SHA-256");
                HttpURLConnection c = connection(address);
                try {
                    if (c.getResponseCode() != 200) throw new IOException("APK download failed (HTTP " + c.getResponseCode() + ").");
                    long total = 0, last = 0;
                    try (InputStream input = c.getInputStream(); FileOutputStream output = new FileOutputStream(temporary)) {
                        byte[] buffer = new byte[65536]; int count;
                        while ((count = input.read(buffer)) != -1) {
                            if (cancelled) throw new IOException("Download cancelled.");
                            total += count; if (total > bytes) throw new IOException("APK size does not match the release.");
                            hash.update(buffer, 0, count); output.write(buffer, 0, count);
                            long now = SystemClock.elapsedRealtime();
                            if (now - last > 500) { show("Downloading update: " + (total * 100 / bytes) + "%"); last = now; }
                        }
                        output.getFD().sync();
                    }
                    if (total != bytes) throw new IOException("APK download is incomplete.");
                } finally { c.disconnect(); }
                StringBuilder actual = new StringBuilder();
                for (byte b : hash.digest()) actual.append(String.format(Locale.ROOT, "%02x", b & 255));
                if (!digest.equals(actual.toString())) throw new IOException("APK checksum does not match the release.");
                verify(temporary);
                java.nio.file.Files.move(temporary.toPath(), apk.toPath(), java.nio.file.StandardCopyOption.REPLACE_EXISTING);
                runOnUiThread(() -> { if (!cancelled) { ready = true; update.setText("Install downloaded update"); show("Download verified. Ready to install."); active(false); install(); } });
            } catch (Exception e) { show("Update stopped: " + e.getMessage()); runOnUiThread(() -> active(false)); }
            finally { temporary.delete(); }
        }, "OpenTS-update-download").start();
    }
    @SuppressWarnings("deprecation")
    private void verify(File file) throws Exception {
        int flags = PackageManager.GET_SIGNATURES;
        if (Build.VERSION.SDK_INT >= 28) flags |= PackageManager.GET_SIGNING_CERTIFICATES;
        PackageInfo downloaded = getPackageManager().getPackageArchiveInfo(file.getPath(), flags);
        PackageInfo installed = getPackageManager().getPackageInfo(getPackageName(), flags);
        if (downloaded == null || !getPackageName().equals(downloaded.packageName)
            || UpdatePolicy.compare(downloaded.versionName, latest) != 0
            || (Build.VERSION.SDK_INT >= 28 ? downloaded.getLongVersionCode() <= installed.getLongVersionCode()
                : downloaded.versionCode <= installed.versionCode)) throw new IOException("APK is not a newer OpenTS-A update.");
        Signature[] a = signers(downloaded);
        Signature[] b = signers(installed);
        if (a == null || b == null || a.length == 0 || a.length != b.length || !new HashSet<>(Arrays.asList(a)).equals(new HashSet<>(Arrays.asList(b))))
            throw new IOException("APK signing certificate does not match this installation.");
    }
    @SuppressWarnings("deprecation")
    private static Signature[] signers(PackageInfo info) {
        if (info == null) return null;
        if (Build.VERSION.SDK_INT >= 28 && info.signingInfo != null) {
            Signature[] signatures = info.signingInfo.getApkContentsSigners();
            if (signatures != null && signatures.length > 0) return signatures;
        }
        return info.signatures;
    }
    private void install() {
        if (!ready || busy) return;
        try {
            verify(apk);
            if (!getPackageManager().canRequestPackageInstalls()) {
                new AlertDialog.Builder(this).setTitle("Allow OpenTS-A updates")
                    .setMessage("Enable Allow from this source in Android settings, then return here to install the verified update.")
                    .setNegativeButton("Cancel", null).setPositiveButton("Open settings", (d, w) -> {
                        waitingPermission = true;
                        startActivity(new Intent(Settings.ACTION_MANAGE_UNKNOWN_APP_SOURCES, Uri.parse("package:" + getPackageName())));
                    }).show(); return;
            }
            Uri uri = Uri.parse("content://" + getPackageName() + ".updates/update.apk");
            Intent intent = new Intent(Intent.ACTION_VIEW).setDataAndType(uri, "application/vnd.android.package-archive")
                .addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
            intent.setClipData(ClipData.newRawUri("OpenTS-A update", uri)); startActivity(intent);
        } catch (Exception e) { show("Could not install update: " + e.getMessage()); }
    }
    @Override protected void onResume() {
        super.onResume();
        if (waitingPermission) { waitingPermission = false; if (getPackageManager().canRequestPackageInstalls()) install(); }
    }
    private void leave() {
        cancelled = true;
        if (getIntent().getBooleanExtra("launch_game", false)) startActivity(new Intent(this, GameActivity.class));
        finish();
    }
    @Override public void onBackPressed() { leave(); }
    @Override protected void onDestroy() { cancelled = true; super.onDestroy(); }
}
