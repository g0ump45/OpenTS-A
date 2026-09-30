# Android direct-IP multiplayer preview

The Android **Internet** button opens a two-player direct-IP lobby. It uses
the existing LAN setup, content checks, gameplay-port check, and match launch.
No relay server or room-code service is used. LAN discovery remains available
through **LAN**. Desktop menus and packet formats are unchanged by this feature.

## Connect two phones

1. Install the same build and game data on both phones.
2. Connect each phone to a network whose router you can configure. Reserve the
   phone's local address so forwarding rules continue to reach it.
3. On both routers, forward external **UDP 49153** to **UDP 49153** on the phone.
   On the host router, also forward **UDP 49152** to **UDP 49152** on the host phone.
4. The host opens **Internet > Host Lobby** and shares its router's public IPv4
   address with the other player.
5. The guest opens **Internet > Join by IP**, enters that address on the keypad,
   and taps **Connect**.
6. Wait for the gameplay connection and content checks, then both tap Ready.
   The host taps Start Game.

The guest's lobby socket uses an outgoing connection with replies to its observed
port. Gameplay currently uses the peer's observed IPv4 address with fixed port
49153; it does not discover a translated gameplay port. Both gameplay forwards
are therefore required for this initial implementation. IPv6, hostnames,
automatic router configuration, and NAT traversal are not implemented.

A router behind another NAT, including a carrier NAT, may not be reachable even
after configuring the local router. This build does not solve that situation.
Two phones on the same network should use LAN. For internet validation, use two
different networks with reachable forwarded ports.

## Failure and security limits

An unreachable lobby times out and asks the guest to return and check the address
and forwarding. Direct-IP mode does not fall back to broadcasting on local Wi-Fi.
If the lobby connects but gameplay checking does not finish, check UDP 49153 on
both networks. Different game data blocks readiness as in LAN mode.

The protocol is an experimental trusted-peer transport. There are no accounts,
passwords, encryption, or cryptographic peer authentication. Share an address
only with the intended player and remove forwarding rules when testing is over.

## Validation

The asset-free `android_lan_probe_test.cpp` exercises direct joining, strict
IPv4 parsing, the first connection on a device with a long uptime, timeout without
broadcast fallback, and the existing LAN readiness and launch state machine.
The Android arm64 Debug build checks integration. These checks do not establish
that a match works across real internet routers: test on two networks, launch a
match, issue commands from both phones, then leave and reconnect.

This build also chooses a wider battlefield from the phone window at startup.
The logical height stays at 480 pixels and the width is at least 640. Touch
mapping, render buffers, sidebar positions, and Android dialog centering follow
that width. Restart after changing the window size; live resizing is not supported.

## Host address display

In a host lobby, tap **Host IP** to open address details. The screen requests the current public IPv4 address from https://api.ipify.org over HTTPS and provides **Copy public IP** and **Refresh addresses**. Local interface IPv4 addresses are listed separately for LAN and router setup. Lookup failures leave copying disabled and allow retry. A VPN or carrier NAT can make the reported address unsuitable for incoming connections; the lookup does not test forwarded ports. Return to the lobby before starting the match.

## In-game instructions

Connection Help is available before hosting/joining and in both players' lobbies. It explains LAN, direct public-IP forwarding, the unverified Tailscale alternative for mobile networks, which address to enter, and connection troubleshooting. The scrollable page has a fixed Back to game button. Help is disabled during the launch handshake.
