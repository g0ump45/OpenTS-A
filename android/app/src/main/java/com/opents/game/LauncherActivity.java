package com.opents.game;

import android.app.Activity;
import android.app.NativeActivity;
import android.content.Intent;
import android.os.Bundle;
import java.io.File;

public class LauncherActivity extends Activity {
    @Override public void onCreate(Bundle state) {
        super.onCreate(state);
        File directory = getExternalFilesDir(null);
        boolean available = false;
        File[] files = directory == null ? null : directory.listFiles();
        if (files != null) for (File file : files)
            if (file.isFile() && (file.getName().equalsIgnoreCase("TIBSUN.MIX") || file.getName().equalsIgnoreCase("RULES.INI"))) available = true;
        if (directory != null && new File(directory, FreewareSetup.PENDING).exists()) available = false;
        if (getIntent().getBooleanExtra("setup_game_files", false)) available = false;
        boolean updates = available && (getIntent().getBooleanExtra("check_updates", false)
            || getSharedPreferences("updates", MODE_PRIVATE).getBoolean("startup", false));
        Intent next = new Intent(this, updates ? UpdatesActivity.class : available ? GameActivity.class : GameFilesActivity.class);
        if (updates) next.putExtra("launch_game", true);
        startActivity(next);
        finish();
    }
}
