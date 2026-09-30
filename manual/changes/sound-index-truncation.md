---
title: Compare sound entries without truncating the index
category: fix
release: 0.1.0
targets: []
credit: [ZivDero, tomsons26]
---

An animation may name any sound in the sound list, however far down it sits. The checks for
"no sound" narrowed the entry to a single byte first, so entry 255 matched the no-sound
marker and was silently skipped, and writing such an entry back out recorded it as none. The
shipped sound list already runs past that point, and a mod that adds sounds meets the same
collision again every 256 entries.
