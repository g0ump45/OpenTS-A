# Android LAN match test

Install the same **LAN Match - Test 3** APK and game data on both Android devices. Use Wi-Fi that permits peer traffic. One device chooses **Host Lobby**; the other chooses **Find LAN Hosts** and joins. Test 3 uses protocol version 3; Test 1 and Test 2 peers are ignored. Update both devices to migrate.

Names and sides remain editable, and the host chooses an installed multiplayer map. Each device opens gameplay UDP port 49153 and verifies traffic with the other device before allowing Ready. The lobby compares a digest of the map bytes, engine packet sizes, active expansion, and the engine's rule/art/AI identifiers. Missing or mismatched content blocks readiness. This check is not authentication or a guarantee that all installed assets and executable behavior match.

Both players tap Ready, then the host taps **Start Game**. Setup locks during the start handshake. The guest prepares, the host commits, and the guest acknowledges while entering the loading screen. Messages are retransmitted, including while loading. The host leaves its lobby after receiving the commit acknowledgement. The existing engine loading-progress barrier waits for both devices, then the engine uses its reliable event transport and synchronized command queues.

Test 3 fixes the match settings: two humans, no AI, bases enabled, 10000 credits, tech level 10, one starting-unit count, speed setting 2, short game, destructible bridges, and MCV redeployment. Crates, fog, and other optional modes are off. Players use distinct colors (host gold, guest red); the engine chooses start positions from the shared seed. In-game names are prefixed `H:` and `G:` to keep them distinct even if both lobby names match. Names are temporary and not saved to settings.

This intentionally adds experimental Android match launch. Desktop menus and gameplay packet layouts are unchanged. Two-phone match behavior still needs runtime testing; successful compilation and transport-state tests alone do not establish synchronized gameplay.

## Lifetime and failure behavior

Lobby discovery uses UDP host port 49152 and an ephemeral client port. Gameplay uses port 49153 on both devices. The existing `SocketClass` and `Ipx.Configure_Direct_Peers` paths provide the two transports. The Android callback keeps start acknowledgements flowing during scenario loading. Returning to the Android main menu releases both transports.

Changing setup before launch clears readiness. A lost lobby peer times out after five seconds; during loading the launch control channel allows 120 seconds. Loading progress uses a 120-second no-progress timeout. A failed two-player loading barrier returns to the menu. Gameplay uses the engine's network timeouts and CRC checks. Android now supplies a real monotonic millisecond network clock and removes departed peers from the roster. A detected desync ends the match and shows a message on return to the menu; the desktop desync recovery dialog is not available on Android.

The match remains an initial 1v1 test. Host-configurable match options, map transfer, cross-version play, mobile background/resume recovery, and multiplayer save/load are not validated. Keep both apps in the foreground while testing.

## Lobby wire format

All lobby messages begin with a 12-byte header: ASCII `OTLP`, version 3, type, two reserved zero bytes, and a big-endian 32-bit client nonce. Types 1 DISCOVER, 2 OFFER, 3 HELLO, and 4 ACK contain only the header. Discovery and HELLO retry every second; HELLO/ACK also provide heartbeats. Replies must match the selected address, port, and nonce. A host admits one guest, and discovery retains at most five hosts. Each poll processes at most 32 datagrams.

Types 5 CLIENT_STATE and 6 HOST_STATE are exactly 172 bytes:

| Offset | Field |
| --- | --- |
| 12 | Host setup revision, unsigned 32-bit big-endian |
| 16 | Sender state sequence, unsigned 32-bit big-endian |
| 20 | Ready, byte 0 or 1 |
| 21 | Local availability and gameplay-port check, byte 0 or 1 |
| 22 | Player name, 24-byte NUL-terminated printable ASCII |
| 46 | Side identifier, 32-byte NUL-terminated printable ASCII |
| 78 | Map filename, 64-byte NUL-terminated printable ASCII |
| 142 | Shared seed, unsigned 32-bit big-endian |
| 146 | Launch stage: 0 lobby, 1 host request, 2 guest prepared, 3 host commit, 4 loading |
| 147 | Reserved zero byte |
| 148 | Last accepted peer state sequence, unsigned 32-bit big-endian |
| 152 | 20-byte content digest |

Connected peers repeat full state every 250 milliseconds. Older sequences and setup revisions, malformed fields, wrong lengths, unknown versions, and unmatched endpoints are rejected. The host owns the setup revision, map, and seed. Ready status applies to the current setup and matching content. Both-ready additionally requires acknowledgment of the local state. Launch stages advance only through the host/guest handshake with ready peers. Settings cannot change while starting.

Gameplay preflight sends a separate 12-byte `OTGAME3` marker and shared seed through the engine's global channel to the fixed peer endpoint. These probes are consumed in the lobby; gameplay uses the engine's existing packet types afterward.

## Validation

`tests/android_lan_probe_test.cpp` runs the production lobby state machine with fake sockets and address method doubles. It covers discovery, joining, content mismatch, readiness, host map ownership, setup changes, packet reordering, malformed packets, launch cancellation, lost request/commit/ack recovery, frozen launch settings, timeouts, stale nonce rejection, and socket-open failure. Compile with C++20, `code/android_lan.cpp`, and a quote-only include path for `code/`; do not link `ipxaddr.cpp` into this standalone test.

`tests/android_nettime_test.cpp`, compiled with `code/android_network_clock.cpp` and `__ANDROID__` defined, verifies that the production network clock advances and elapsed-time arithmetic handles wrapping. These native tests require no game assets.

Build the Android arm64-v8a Debug APK using the existing Gradle project. Then test on two devices: connect, change settings, ready, start, wait for both maps, deploy and move units, construct a building, and issue commands from each phone. Confirm that each phone controls its own side, opposing actions agree where visible, and several minutes pass without freezing or a desync message. Finally leave one match, return to LAN, and test a fresh match. Capture both devices' logs if loading stalls or synchronization fails.
