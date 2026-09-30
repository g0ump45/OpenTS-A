---
title: Keep a voxel shadow drawn while its object flashes
category: fix
release: 0.1.0
targets: []
credit: [ZivDero, AlexB]
---

A voxel object's shadow now stays on the ground while the object flashes. The shadow was
skipped on every lit phase of the flash, so ordering a vehicle around, or any other flash,
made its shadow blink along with it. A cloaked object and one whose voxel artwork failed to
load still draw no shadow.
