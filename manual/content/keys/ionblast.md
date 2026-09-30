---
key: IonBlast
summary: The ring of fire drawn where an ion cannon strike meets the ground.
see_also: [IonBeam, IonCannonDamage, IonCannonWarhead, SplashList, "system:superweapons"]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
IonBlast=MYIONRING ; an AnimType registered in [Animations]
```

The animation is created five leptons above the impact point on the frame the strike lands, centered on that point and pinned to the view, ahead of the damage and the combat lighting. A strike that comes down on water takes the last entry of [`SplashList`](/keys/splashlist/) in its place, so this is the land effect only; [`IonBeam`](/keys/ionbeam/) is drawn over both.

The GDI Ion Cannon superweapon and the scripted ion-blast trigger action both arrive through the same routine, so both draw it.

:::danger[An unset animation crashes the game at the first strike on land]
The ring is created without first checking that an animation was named, so with the key unset the game crashes as soon as an ion cannon comes down anywhere but water.
:::
