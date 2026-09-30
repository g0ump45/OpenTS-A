package com.opents.game;

import android.app.Activity;
import android.os.Bundle;
import android.widget.*;

public class ConnectionHelpActivity extends Activity {
    @Override public void onCreate(Bundle state) {
        super.onCreate(state);
        LinearLayout layout = new LinearLayout(this);
        layout.setOrientation(LinearLayout.VERTICAL);
        layout.setPadding(24, 16, 24, 16);
        layout.setBackgroundColor(0xff101a12);
        ScrollView scroll = new ScrollView(this);
        TextView instructions = new TextView(this);
        instructions.setTextColor(0xffa8e89a);
        instructions.setTextSize(18);
        instructions.setTextIsSelectable(true);
        instructions.setText(
            "CONNECTION HELP\n\n" +
            "Before you start\n" +
            "Both phones need the same OpenTS-A build and matching game files. Keep the game open on both phones.\n\n" +
            "Same Wi-Fi: use LAN\n" +
            "1. Connect both phones to the same Wi-Fi.\n" +
            "2. One player selects LAN > Host Lobby.\n" +
            "3. The other selects LAN > Find LAN Hosts and joins.\n" +
            "Guest Wi-Fi may block phones from connecting to each other.\n\n" +
            "Mobile data or no router access: try Tailscale\n" +
            "1. Install the official Tailscale app on both phones (tailscale.com).\n" +
            "2. Add both phones to the same private Tailscale network, using your own account or an invitation from its owner.\n" +
            "3. Enable Tailscale on both phones and accept Android's VPN connection prompt.\n" +
            "4. Find the host phone's 100.x.x.x IPv4 address in Tailscale.\n" +
            "5. In OpenTS-A, the host selects Internet > Host Lobby. The guest selects Internet > Join by IP and enters that Tailscale address.\n" +
            "Use the Tailscale address, NOT the public address from Host IP. Router port forwarding is not needed for this option. OpenTS-A with Tailscale is an unverified testing option; relay connections may add delay.\n\n" +
            "Internet with router access: direct public IP\n" +
            "1. Reserve each phone's local IP address in its router settings.\n" +
            "2. On BOTH routers, forward UDP port 49153 to port 49153 on the phone.\n" +
            "3. On the HOST router, also forward UDP port 49152 to port 49152 on the host phone.\n" +
            "4. The host selects Internet > Host Lobby > Host IP, then copies the public IPv4 address for the guest.\n" +
            "5. The guest selects Internet > Join by IP and enters that public address.\n" +
            "Mobile/carrier networks may block incoming connections even if an address is shown. A public-IP lookup does not check whether the ports are reachable.\n\n" +
            "Start the match\n" +
            "Return to the lobby. Wait for connection and matching-content checks. Both players tap Ready, then the host taps Start Game.\n\n" +
            "If it will not connect\n" +
            "Timed out: check the host address and that the host lobby is open. For Tailscale, check both phones are connected to the same private network.\n" +
            "Gameplay check stuck: for public-IP play, check UDP 49153 on BOTH routers.\n" +
            "Content mismatch: use matching builds, maps and game files.\n" +
            "Changed network: return to the menu, check the new address and host again.\n\n" +
            "Tailscale reference: tailscale.com/docs/reference/faq/firewall-ports\n");
        scroll.addView(instructions);
        layout.addView(scroll, new LinearLayout.LayoutParams(-1, 0, 1));
        Button back = new Button(this);
        back.setText("Back to game"); back.setOnClickListener(v -> finish());
        layout.addView(back);
        setContentView(layout);
    }
}
