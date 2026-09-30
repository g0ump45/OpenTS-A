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
        startActivity(new Intent(this, available ? NativeActivity.class : GameFilesActivity.class));
        finish();
    }
}
