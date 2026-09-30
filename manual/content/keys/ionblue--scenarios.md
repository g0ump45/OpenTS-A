---
key: IonBlue
scope: scenarios
label: Scenario lighting
see_also: [Blue, IonRed, IonGreen, "system:ion-storms"]
when_omitted:
  kind: context-dependent
  note: The value this scenario's Blue key sets in the same section, read immediately before it. With neither key present that is 1, leaving the blue channel unchanged.
---

The three ion tints are applied to every tinted terrain palette the map has built, and to every color scheme with more than one intensity level, on the frame the storm breaks, and reversed on the frame it ends. Neither change is faded, so the whole map switches color in one step while its [ambient level](/keys/ionambient/) is still traveling.

Any tinted palette built while a storm is running also takes these values, so an object or overlay that first appears mid-storm matches the ones already on screen.
