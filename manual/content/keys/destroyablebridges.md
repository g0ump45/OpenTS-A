---
key: DestroyableBridges
summary: Whether a wall-destroying blast can bring a bridge span down.
see_also: [BridgeStrength, IonCannonWarhead, C4Warhead]
when_omitted:
  kind: unchanged
  note: The scenario's special options are set up once when the game starts and are not reset between missions, so a campaign mission that omits the key keeps whatever the previously played mission established. Only the first mission of a session finds the initial value, yes.
---

The switch is the first half of the test a blast makes when it reaches a span; the warhead's own ability to destroy walls is the other half. With the switch off, spans absorb everything and no bridge on the map can be brought down by fire. [`BridgeStrength`](/keys/bridgestrength/) covers the roll that follows once both halves pass, and the demolition charge an infantryman leaves on a deck is unaffected either way.

:::caution[The entry is read in campaigns only]
The `[SpecialFlags]` block is read from the map only in a single-player mission or with the map debugger active, and every other game type replaces the scenario's whole set of flags with the one the lobby settled on once the map has been read. Outside a campaign, bridge destruction follows the lobby's own option.
:::
