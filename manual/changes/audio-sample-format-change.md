---
title: Play samples whose format differs from the mixer's
category: fix
release: 0.2.0
targets:
- type: format
  id: aud
  effect: changed
credit:
- ZivDero
---

A sample whose rate, bit depth or channel count differed from 22050 hertz sixteen bit mono did not play, and the sound channel it was given stayed silent for every later sound. Such a sample now plays in its own format.
