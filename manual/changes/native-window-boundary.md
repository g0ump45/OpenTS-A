---
title: Separate native window handling from video presentation
category: internal
release: 0.2.0
targets: []
credit: [Krisztiaan]
---

The application shell now supplies the native window handle, physical drawable size, and display refresh rate to the video presenter. The presenter no longer owns Win32 window queries, and the bgfx backend alone translates the native handle into bgfx platform data. This is an internal boundary change; the supported target and video configuration are unchanged.
