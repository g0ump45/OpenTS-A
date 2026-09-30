---
key: Inert
summary: Strips all damage out of the scenario's weapons.
when_omitted:
  kind: unchanged
  note: The scenario's special options are set up once when the game starts and are not reset between missions, so a campaign mission that omits the key keeps whatever the previously played mission established. Only the first mission of a session finds the initial value, no.
---

Two routines carry the whole effect: the one that converts a weapon's raw damage into damage against a particular armor returns zero, and the one that spreads an explosion over the objects around a point returns before it collects anything. Nothing on the map can then be destroyed by weapon fire. Everything else about firing carries on — weapons still reload, projectiles still travel, and the report and impact effects still play.

Damage delivered as forced skips the warhead conversion altogether and is untouched, so an infantryman standing in Tiberium still dies of it.

:::caution[The entry is read in campaigns only]
The `[SpecialFlags]` block is read from the map only in a single-player mission or with the map debugger active, and every other game type replaces the scenario's whole set of flags with the one the lobby settled on once the map has been read.
:::
