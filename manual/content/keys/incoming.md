---
key: Incoming
summary: The projectile speed below which infantry fire sends the target cell's occupants running for cover.
see_also: ["Speed", "Primary", "PlayerScatter", "Scatter"]
when_omitted:
  kind: value
  value: "0"
---

This figure is consulted in one place: infantry fire, on the frame its firing animation reaches the point where the shot leaves. Aircraft fire warns the target's cell too, without consulting it. The speed compared is that of the weapon in the infantry type's first slot, [`Primary`](/keys/primary/), regardless of which weapon actually fired, and it must be strictly below this figure — equal is not enough. The occupants of the target's cell are then told a threat is coming.

Whether any of them actually moves is a separate question; [`PlayerScatter`](/keys/playerscatter/) covers what a warned cell does with its occupants.

The figure is written on the same zero-to-a-hundred scale as a weapon's [`Speed`](/keys/speed/#scope-weapontype), and values outside that range are clamped into it. An unguided weapon does not keep the speed written on it: its launch speed is worked out from its range and the world's gravity once the rules have been read, and that derived figure is what this is compared against.

With the key unwritten the figure is zero, no weapon is below it, and no shot ever raises the warning.
