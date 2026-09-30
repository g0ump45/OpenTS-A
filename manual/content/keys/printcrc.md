---
key: PrintCRC
summary: The playback frame at which the game writes a synchronization dump and quits.
see_also: ["Frame", "Type", "CheckHeap"]
when_omitted:
  kind: value
  value: "2147483647"
---

Recording playback compares the frame counter against this number just after computing each frame's checksum. On reaching it the game writes the [out-of-sync report](/using/out-of-sync-reports/) into the `Debug` folder beside the executable and then exits. It is the same report a live network game writes when it detects a divergence: the build details, the session identity and seed, the recent frame-checksum ring, the network settings in force, and per-object and per-heap checksums keyed to each object's stable identifier, which is what makes two machines' reports comparable.

:::caution[Arming playback normally skips the read that raises this number]
The sync-bug settings are read as the multiplayer menu is entered, and only while playback is armed. Arming playback with a readable recording present makes the game bypass that menu and start the playback directly, leaving the number at the `0` it was constructed with. The comparison then succeeds on the very first frame, so the dump is written and the game exits before the recording has played anything.
:::
