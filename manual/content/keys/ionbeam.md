---
key: IonBeam
summary: The column of light drawn where an ion cannon strike lands.
see_also: [IonBlast, IonCannonDamage, IonCannonWarhead, SplashList, "system:superweapons"]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
IonBeam=MYIONBEAM ; an AnimType registered in [Animations]
```

The animation is created five leptons above the impact point on the frame the strike lands, centered on that point and pinned to the view, ahead of the damage and the combat lighting. It plays over every surface: unlike [`IonBlast`](/keys/ionblast/), which water replaces with a splash, the beam is drawn wherever the strike comes down.

The GDI Ion Cannon superweapon and the scripted ion-blast trigger action both arrive through the same routine, so both draw it.

:::danger[An unset animation crashes the game at the first ion cannon strike]
The beam is created without first checking that an animation was named, so with the key unset the game crashes as soon as an ion cannon fires, whether the superweapon or a trigger sent it.
:::
