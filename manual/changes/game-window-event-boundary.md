---
title: Separate game window responses from native events
category: internal
release: 0.2.0
targets: []
credit: [Krisztiaan]
---

The Win32 window procedure now translates paint, right-button release, and mouse-wheel messages into native-independent game callbacks. Game responses live with the callbacks, while Win32-specific validation and message decoding remain in the application shell. The video presenter accepts refresh-rate updates directly instead of handling a native display-change event. Controls and rendering configuration are unchanged.
