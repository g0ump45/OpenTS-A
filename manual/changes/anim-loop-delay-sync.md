---
title: Draw animation loop delays from the synchronized generator
category: fix
release: 0.1.0
targets: []
credit: [ZivDero, tomsons26]
---

An animation that waits a random spell between loops now draws that delay from the
generator every machine in a networked game shares. It used the local generator, whose
results differ from one machine to the next, and the delay it produced is both stored in
saved games and folded into the checksum the game compares between players, so the first
time such an animation looped the machines disagreed and the game reported a
desynchronization.
