---
key: MoveFlash
summary: The animation dropped on the cell a move order points at.
see_also: [YSortAdjust]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
MoveFlash=MOVEFLSH ; an AnimType registered in [Animations]
```

The animation is raised at the ordered cell, lifted to the local ground height or onto the bridge deck if there is one, each time the player gives a move order that is allowed to speak. It is the marker under the cursor rather than anything the moving object carries, so one is dropped per order however many objects took it.

A game played against other machines — over a network or the Internet — treats the marker differently, so that a purely local decoration cannot disturb what the other machines are counting on. It is given an identifier from outside the scenario's own sequence, taken straight back out of the ordinary animation list, and stepped from a separate list that only those game types walk. A campaign mission and a skirmish take the ordinary path.

:::danger[Leaving the animation unset crashes on the first move order]
The animation type is handed straight to the constructor, which reads the type's sort adjustment before checking anything. With no rules file naming the key the stored type is null, and the first move order the player gives dereferences it. The multiplayer path writes through the same null pointer one line earlier. There is no fallback and no safe absent state.
:::

:::danger[Sharing the animation type desynchronizes a multiplayer game]
Before creating the marker, a network or Internet game writes a sort adjustment of `-5000` onto the animation type itself so that the marker draws over everything around it. The write lands on the shared type rather than on the one animation, and is never undone. The marker is kept out of the synchronization checksum, but every other animation later created from that type copies the adjustment into its own sort position, and the ground layer the checksum walks is ordered by that position. A machine whose player has given a move order and one whose player has not then disagree, so pointing the key at an AnimType that anything else uses desynchronizes the game.
:::
