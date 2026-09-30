package com.opents.game;

import android.app.Activity;
import android.os.Bundle;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.widget.*;
import java.net.*;
import java.io.*;
import java.util.*;
import javax.net.ssl.HttpsURLConnection;

public class HostAddressActivity extends Activity {
    private TextView publicAddress, localAddresses;
    private Button refresh, copy;
    private String address;

    @Override public void onCreate(Bundle state) {
        super.onCreate(state);
        ScrollView scroll = new ScrollView(this);
        LinearLayout layout = new LinearLayout(this);
        layout.setOrientation(LinearLayout.VERTICAL);
        layout.setPadding(32, 24, 32, 24);
        layout.setBackgroundColor(0xff101a12);
        scroll.addView(layout);
        text(layout, "Host IP address", 24);
        publicAddress = text(layout, "", 22);
        text(layout, "Give the public IPv4 address to the internet player. Lookup uses api.ipify.org over HTTPS. A VPN can change the address shown; this is not a port-reachability test.", 16);
        copy = button(layout, "Copy public IP", () -> {
            if (address == null) return;
            ((ClipboardManager)getSystemService(CLIPBOARD_SERVICE)).setPrimaryClip(ClipData.newPlainText("Host IPv4", address));
            Toast.makeText(this, "IP address copied", Toast.LENGTH_SHORT).show();
        });
        refresh = button(layout, "Refresh addresses", this::lookup);
        localAddresses = text(layout, "", 18);
        text(layout, "Router setup: forward UDP 49152 and 49153 to the host phone. The guest also needs UDP 49153 forwarded. Local addresses below are for LAN/router setup, not internet joining.", 16);
        button(layout, "Back to lobby", this::finish);
        setContentView(scroll);
        lookup();
    }

    private TextView text(LinearLayout parent, String value, int size) {
        TextView view = new TextView(this);
        view.setText(value); view.setTextSize(size); view.setTextColor(0xffa8e89a);
        view.setPadding(0, 8, 0, 8); view.setTextIsSelectable(true);
        parent.addView(view); return view;
    }

    private Button button(LinearLayout parent, String value, Runnable action) {
        Button view = new Button(this); view.setText(value);
        view.setOnClickListener(v -> action.run()); parent.addView(view); return view;
    }

    private void lookup() {
        address = null; copy.setEnabled(false); refresh.setEnabled(false);
        publicAddress.setText("Public IPv4: checking...");
        localAddresses.setText("Local IPv4 addresses: checking...");
        new Thread(() -> {
            StringBuilder local = new StringBuilder("Local IPv4 addresses:\n");
            try {
                Enumeration<NetworkInterface> interfaces = NetworkInterface.getNetworkInterfaces();
                while (interfaces != null && interfaces.hasMoreElements()) {
                    NetworkInterface item = interfaces.nextElement();
                    if (!item.isUp() || item.isLoopback()) continue;
                    for (InetAddress ip : Collections.list(item.getInetAddresses()))
                        if (ip instanceof Inet4Address && !ip.isLoopbackAddress())
                            local.append(item.getName()).append(": ").append(ip.getHostAddress()).append('\n');
                }
            } catch (Exception e) { local.append("Unavailable\n"); }
            String localText = local.toString();
            runOnUiThread(() -> { if (!isFinishing() && !isDestroyed()) localAddresses.setText(localText); });
            String result = null;
            HttpsURLConnection connection = null;
            try {
                connection = (HttpsURLConnection)new URL("https://api.ipify.org").openConnection();
                connection.setConnectTimeout(5000); connection.setReadTimeout(5000);
                connection.setInstanceFollowRedirects(false);
                if (connection.getResponseCode() != 200) throw new IOException();
                ByteArrayOutputStream bytes = new ByteArrayOutputStream();
                try (InputStream input = connection.getInputStream()) {
                    int value;
                    while ((value = input.read()) != -1) {
                        if (bytes.size() >= 64) throw new IOException();
                        bytes.write(value);
                    }
                }
                String candidate = bytes.toString("US-ASCII").trim();
                String[] parts = candidate.split("\\.", -1);
                if (parts.length != 4) throw new IOException();
                for (String part : parts)
                    if (!part.matches("[0-9]{1,3}") || Integer.parseInt(part) > 255) throw new IOException();
                int first = Integer.parseInt(parts[0]);
                if (first == 0 || first == 127 || first >= 224) throw new IOException();
                result = candidate;
            } catch (Exception e) {
                // Leave the local addresses available when the public lookup fails.
            } finally { if (connection != null) connection.disconnect(); }
            String found = result;
            runOnUiThread(() -> {
                if (isFinishing() || isDestroyed()) return;
                address = found;
                publicAddress.setText(found == null ? "Public IPv4 unavailable. Check internet access and retry, or read the WAN address in your router settings." : "Public IPv4: " + found);
                copy.setEnabled(found != null); refresh.setEnabled(true);
            });
        }, "OpenTS-host-address").start();
    }
}
