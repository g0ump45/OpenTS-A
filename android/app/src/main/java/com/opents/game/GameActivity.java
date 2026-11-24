package com.opents.game;

import android.app.NativeActivity;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.view.PointerIcon;
import android.view.WindowInsets;
import android.view.WindowInsetsController;

public class GameActivity extends NativeActivity {
    private boolean systemPointerHidden;
    public void setSystemPointerHidden(boolean hidden) {
        runOnUiThread(() -> {
            systemPointerHidden = hidden;
            if (!isFinishing() && !isDestroyed()) applyPointer(getWindow().getDecorView(),
                PointerIcon.getSystemIcon(this, hidden ? PointerIcon.TYPE_NULL : PointerIcon.TYPE_DEFAULT));
        });
    }
    private void applyPointer(View view, PointerIcon icon) {
        view.setPointerIcon(icon);
        if (view instanceof ViewGroup) {
            ViewGroup group = (ViewGroup)view;
            for (int i = 0; i < group.getChildCount(); ++i) applyPointer(group.getChildAt(i), icon);
        }
    }
    @Override public void onCreate(Bundle state) {
        super.onCreate(state);
        hideSystemBars();
    }

    @Override protected void onResume() {
        super.onResume();
        hideSystemBars();
    }

    @Override public void onWindowFocusChanged(boolean focused) {
        super.onWindowFocusChanged(focused);
        if (focused) { hideSystemBars(); setSystemPointerHidden(systemPointerHidden); }
    }

    private void hideSystemBars() {
        if (Build.VERSION.SDK_INT >= 30) {
            getWindow().setDecorFitsSystemWindows(false);
            WindowInsetsController controller = getWindow().getInsetsController();
            if (controller != null) {
                controller.setSystemBarsBehavior(
                    WindowInsetsController.BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE);
                controller.hide(WindowInsets.Type.systemBars());
            }
        } else {
            getWindow().getDecorView().setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_FULLSCREEN
                | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
                | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION);
        }
    }
}
