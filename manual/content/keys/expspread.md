---
key: ExpSpread
summary: Divisor that turns an exploding object's collateral damage into the radius of its death blast.
see_also: ["Explodes", "CollateralDamageCoefficient", "Strength", "MaxDamage"]
when_omitted:
  kind: value
  value: ".5"
---

The blast belongs to an object carrying [`Explodes=yes`](/keys/explodes/#scope-aircrafttype), or one that has earned the explodes ability, and goes off at its center as it dies. Its strength is the object's full [`Strength`](/keys/strength/#scope-aircrafttype) multiplied by its [`CollateralDamageCoefficient`](/keys/collateraldamagecoefficient/) — the object's damaged state does not enter into it. A building adds its stored tiberium on top: the amount held of each type multiplied by that type's [`Power`](/keys/power/#scope-tiberium). The figure `Strength` alone yields is therefore only a floor for a building, and a full refinery blows up far harder than an empty one.

The blast carries the warhead of the object's primary weapon — the one [`Primary`](/keys/primary/) names, or the one [`Elite`](/keys/elite/) names once the object is elite. An object with that slot empty has no warhead to carry, and the wide-area routine returns on entry: no cell is damaged, and no explosion animation or flash is produced either.

The radius is that strength divided by a hundred, divided again by this figure, and read as cells. A larger figure therefore makes a smaller blast. The division by a hundred is a whole-number one, so an object whose collateral strength falls short of a hundred is left with no radius at all and takes the floor of the clamp described next.

The radius is then held between one lepton and three cells, and the blast covers every cell within it once rounded up to whole cells — one ring of cells at the small end and three at the large. The damage delivered is the collateral strength multiplied by the radius in whole cells rounded **down**, held at a minimum of one — while the area covered rounds the same radius **up**. The two agree only where the radius lands on an exact cell boundary; between boundaries the blast covers a ring more than it multiplies for.

:::caution[A wide blast is weakest just off its center]
Each cell's share of the damage is scaled by how far it lies from the middle, and the scale rises with that distance instead of falling away with it. The cells just off center take a fraction of the figure and the ones at the rim take all of it or more; the center cell is exempt and takes the full figure. A blast one ring of cells across is unaffected, since every cell in it counts as being at the rim.
:::
