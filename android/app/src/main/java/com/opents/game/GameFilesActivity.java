package com.opents.game;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.DocumentsContract;
import android.view.WindowManager;
import android.widget.*;
import java.io.*;
import java.util.*;
import java.util.zip.*;

public class GameFilesActivity extends Activity {
    private static final int FOLDER = 1, ZIP = 2;
    private TextView status;
    private Button folderButton, zipButton, downloadButton, doneButton, languageButton;
    private String gameLanguage = "en";
    private volatile boolean cancelDownload;
    private boolean downloading;
    private long lastProgress;
    private boolean busy, imported;
    private File destination;

    @Override public void onCreate(Bundle state) {
        super.onCreate(state);
        destination = getExternalFilesDir(null);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        LinearLayout layout = new LinearLayout(this);
        layout.setOrientation(LinearLayout.VERTICAL);
        layout.setPadding(dp(16), dp(12), dp(16), dp(12));
        layout.setBackgroundColor(0xff101a12);
        TextView heading = new TextView(this);
        heading.setText("Install game files");
        heading.setTextColor(0xffa8e89a); heading.setTextSize(22);
        heading.setPadding(0, 0, 0, dp(8));
        layout.addView(heading);
        ScrollView scroll = new ScrollView(this);
        layout.addView(scroll, new LinearLayout.LayoutParams(-1, 0, 1));
        LinearLayout content = new LinearLayout(this);
        boolean landscape = getResources().getConfiguration().orientation
            == android.content.res.Configuration.ORIENTATION_LANDSCAPE;
        content.setOrientation(landscape ? LinearLayout.HORIZONTAL : LinearLayout.VERTICAL);
        scroll.addView(content);
        status = new TextView(this);
        status.setTextColor(0xffa8e89a); status.setTextSize(16);
        status.setPadding(0, 0, landscape ? dp(20) : 0, dp(12));
        status.setText("Choose your game language, then download the freeware files or import an installation folder or ZIP.\n\nPhone settings and saves are kept. Use Wi-Fi for downloads and keep this screen open.");
        content.addView(status, landscape ? new LinearLayout.LayoutParams(0, -2, 1)
            : new LinearLayout.LayoutParams(-1, -2));
        LinearLayout actions = new LinearLayout(this);
        actions.setOrientation(LinearLayout.VERTICAL);
        content.addView(actions, landscape ? new LinearLayout.LayoutParams(0, -2, 1)
            : new LinearLayout.LayoutParams(-1, -2));
        gameLanguage = getPreferences(MODE_PRIVATE).getString("game-language", "en");
        if (!Arrays.asList(GameLanguage.CODES).contains(gameLanguage)) gameLanguage = "en";
        languageButton = button(actions, "Game language: " + GameLanguage.label(gameLanguage), () -> chooseLanguage());
        downloadButton = button(actions, "Download freeware game files", () -> confirmDownload());
        LinearLayout imports = new LinearLayout(this);
        imports.setOrientation(LinearLayout.HORIZONTAL);
        actions.addView(imports, new LinearLayout.LayoutParams(-1, -2));
        folderButton = button(imports, "Choose folder", () -> choose(FOLDER));
        folderButton.setLayoutParams(new LinearLayout.LayoutParams(0, -2, 1));
        zipButton = button(imports, "Choose ZIP", () -> choose(ZIP));
        zipButton.setLayoutParams(new LinearLayout.LayoutParams(0, -2, 1));
        doneButton = button(actions, "Back", () -> { if (downloading) cancelDownload = true; else leave(); });
        setContentView(layout);
        if (destination == null) { status.setText("Phone game storage is unavailable."); downloadButton.setEnabled(false); folderButton.setEnabled(false); zipButton.setEnabled(false); }
    }

    private int dp(int value) {
        return Math.round(value * getResources().getDisplayMetrics().density);
    }

    private Button button(LinearLayout layout, String title, Runnable action) {
        Button button = new Button(this); button.setText(title);
        button.setOnClickListener(v -> action.run()); layout.addView(button, new LinearLayout.LayoutParams(-1, -2));
        return button;
    }

    private void chooseLanguage() {
        if (busy) return;
        new AlertDialog.Builder(this).setTitle("Choose game language")
            .setSingleChoiceItems(GameLanguage.LABELS, Arrays.asList(GameLanguage.CODES).indexOf(gameLanguage), (dialog, which) -> {
                gameLanguage = GameLanguage.CODES[which];
                getPreferences(MODE_PRIVATE).edit().putString("game-language", gameLanguage).apply();
                languageButton.setText("Game language: " + GameLanguage.label(gameLanguage));
                status.setText(GameLanguage.summary(gameLanguage) + "\n\nOnly the selected language and shared game files are downloaded. Folder and ZIP imports keep the language files supplied in your installation.");
                dialog.dismiss();
            }).setNegativeButton("Cancel", null).show();
    }

    private void choose(int mode) {
        Intent intent = new Intent(mode == FOLDER ? Intent.ACTION_OPEN_DOCUMENT_TREE : Intent.ACTION_OPEN_DOCUMENT);
        if (mode == ZIP) { intent.setType("*/*"); intent.addCategory(Intent.CATEGORY_OPENABLE); }
        intent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
        startActivityForResult(intent, mode);
    }

    @Override protected void onActivityResult(int request, int result, Intent data) {
        super.onActivityResult(request, result, data);
        if (result != RESULT_OK || data == null || data.getData() == null || busy) return;
        busy = true;
        languageButton.setEnabled(false);
        downloadButton.setEnabled(false); folderButton.setEnabled(false); zipButton.setEnabled(false); doneButton.setEnabled(false);
        Uri uri = data.getData();
        status.setText("Finding game files...");
        new Thread(() -> {
            String message;
            try {
                destination.mkdirs();
                int count = request == FOLDER ? importFolder(uri) : importZip(uri);
                GameLanguage.recordImported(destination, gameLanguage);
                new File(destination, FreewareSetup.PENDING).delete();
                imported = true;
                message = "Imported " + count + " game files.\n\nLocation: " + destination + "\n\nClose and reopen OpenTS to load the imported files.";
            } catch (Exception e) {
                message = "Import stopped: " + e.getMessage() + "\n\nAny completed files were kept. Existing files are replaced only after each copy finishes. Choose the source again to retry.";
            }
            String finalMessage = message;
            runOnUiThread(() -> {
                busy = false; status.setText(finalMessage);
                languageButton.setEnabled(true);
                downloadButton.setEnabled(true); folderButton.setEnabled(true); zipButton.setEnabled(true); doneButton.setEnabled(true);
                doneButton.setText(imported ? "Close game" : "Back");
            });
        }, "OpenTS-import").start();
    }

    private void confirmDownload() {
        if (busy || destination == null) return;
        new AlertDialog.Builder(this).setTitle("Install " + GameLanguage.label(gameLanguage) + "?")
            .setMessage(GameLanguage.summary(gameLanguage) + "\n\nShared files come from C&C Communications Center and Tore. Spanish uses nacho-arg's translation; German and French use verified game-data downloads. Use Wi-Fi and keep this screen open. Interrupted downloads can be resumed.")
            .setNegativeButton("Cancel", null)
            .setPositiveButton("Download", (dialog, which) -> downloadFiles()).show();
    }

    private void downloadFiles() {
        busy = true; downloading = true; cancelDownload = false; lastProgress = 0;
        languageButton.setEnabled(false);
        downloadButton.setEnabled(false); folderButton.setEnabled(false); zipButton.setEnabled(false);
        doneButton.setText("Cancel download");
        status.setText("Preparing game-file download...");
        new Thread(() -> {
            String message;
            try {
                int count = FreewareSetup.install(destination, gameLanguage, text -> {
                    if (cancelDownload) throw new java.io.InterruptedIOException("Download cancelled.");
                    long now = android.os.SystemClock.elapsedRealtime();
                    if (now - lastProgress >= 500) { progress(text); lastProgress = now; }
                });
                imported = true;
                message = "Installed " + count + " game files.\n\nTap Close game, then reopen OpenTS-A to play.";
            } catch (Exception e) {
                message = "Setup stopped: " + e.getMessage() + "\n\nTap Download freeware game files to retry. Completed packages and partial downloads are kept.";
            } catch (OutOfMemoryError e) {
                message = "Not enough memory to unpack game files. Close other apps and retry.";
            }
            String finalMessage = message;
            runOnUiThread(() -> {
                busy = false; downloading = false; status.setText(finalMessage);
                languageButton.setEnabled(true);
                downloadButton.setEnabled(true); folderButton.setEnabled(true); zipButton.setEnabled(true);
                doneButton.setText(imported ? "Close game" : "Back");
            });
        }, "OpenTS-freeware-setup").start();
    }

    @Override protected void onDestroy() {
        cancelDownload = true;
        super.onDestroy();
    }

    private void progress(String text) { runOnUiThread(() -> status.setText(text)); }

    private void scan(Uri tree, String id, String prefix, Map<String,Uri> files, Set<String> visited, int depth) throws IOException {
        if (depth > 12 || visited.size() > 10000) throw new IOException("Folder is too large. Select the game's own installation folder.");
        if (!visited.add(id)) return;
        Uri children = DocumentsContract.buildChildDocumentsUriUsingTree(tree, id);
        String[] columns = {DocumentsContract.Document.COLUMN_DOCUMENT_ID, DocumentsContract.Document.COLUMN_DISPLAY_NAME, DocumentsContract.Document.COLUMN_MIME_TYPE};
        try (Cursor cursor = getContentResolver().query(children, columns, null, null, null)) {
            if (cursor == null) throw new IOException("Cannot read the selected folder.");
            while (cursor.moveToNext()) {
                if (files.size() > 10000) throw new IOException("Too many files. Select the game's own installation folder.");
                String childId = cursor.getString(0), name = cursor.getString(1), type = cursor.getString(2);
                if (name == null || name.contains("/") || name.contains("\\")) throw new IOException("Invalid source filename.");
                String path = GameFilePolicy.normalize(prefix + name);
                if (DocumentsContract.Document.MIME_TYPE_DIR.equals(type)) scan(tree, childId, path + "/", files, visited, depth + 1);
                else files.put(path, DocumentsContract.buildDocumentUriUsingTree(tree, childId));
            }
        }
    }

    private int importFolder(Uri tree) throws IOException {
        Map<String,Uri> files = new LinkedHashMap<>();
        scan(tree, DocumentsContract.getTreeDocumentId(tree), "", files, new HashSet<>(), 0);
        Map<String,String> plan = GameFilePolicy.plan(files.keySet());
        long total = 0; int count = 0;
        for (Map.Entry<String,String> entry : plan.entrySet()) {
            progress("Copying " + (++count) + " of " + plan.size() + ": " + entry.getKey());
            try (InputStream source = getContentResolver().openInputStream(files.get(entry.getValue()))) {
                if (source == null) throw new IOException("Cannot open " + entry.getValue());
                total += GameFilePolicy.copyAtomic(source, destination, entry.getKey(), GameFilePolicy.MAX_BYTES - total);
                imported = true;
            }
        }
        return count;
    }

    private int importZip(Uri uri) throws IOException {
        File archive = File.createTempFile("opents-source-", ".zip", getCacheDir());
        try {
            progress("Reading ZIP. Large archives can take a few minutes...");
            try (InputStream input = getContentResolver().openInputStream(uri); FileOutputStream output = new FileOutputStream(archive)) {
                if (input == null) throw new IOException("Cannot open ZIP.");
                byte[] buffer = new byte[65536]; int length; long total = 0;
                while ((length = input.read(buffer)) != -1) {
                    total += length;
                    if (total > GameFilePolicy.MAX_BYTES) throw new IOException("ZIP is too large.");
                    output.write(buffer, 0, length);
                }
            }
            try (ZipFile zip = new ZipFile(archive)) {
                Map<String,ZipEntry> entries = new LinkedHashMap<>();
                Enumeration<? extends ZipEntry> iterator = zip.entries();
                int scanned = 0;
                while (iterator.hasMoreElements()) {
                    if (++scanned > 10000) throw new IOException("ZIP contains too many entries.");
                    ZipEntry entry = iterator.nextElement();
                    GameFilePolicy.normalize(entry.getName());
                    if (!entry.isDirectory() && entries.put(entry.getName(), entry) != null) throw new IOException("ZIP contains duplicate paths.");
                }
                Map<String,String> plan = GameFilePolicy.plan(entries.keySet());
                long required = 0;
                for (String path : plan.values()) {
                    long size = entries.get(path).getSize();
                    if (size <= 0 || size > GameFilePolicy.MAX_BYTES - required) throw new IOException("ZIP has invalid or oversized game files.");
                    required += size;
                }
                if (required > destination.getUsableSpace()) throw new IOException("Not enough free space to import this ZIP.");
                int count = 0; long total = 0;
                for (Map.Entry<String,String> entry : plan.entrySet()) {
                    progress("Importing " + (++count) + " of " + plan.size() + ": " + entry.getKey());
                    try (InputStream source = zip.getInputStream(entries.get(entry.getValue()))) {
                        total += GameFilePolicy.copyAtomic(source, destination, entry.getKey(), GameFilePolicy.MAX_BYTES - total);
                        imported = true;
                    }
                }
                return count;
            }
        } finally { archive.delete(); }
    }

    @Override public void onBackPressed() { if (downloading) cancelDownload = true; else if (!busy) leave(); }

    private void leave() {
        if (imported) { finishAffinity(); android.os.Process.killProcess(android.os.Process.myPid()); }
        else finish();
    }
}
