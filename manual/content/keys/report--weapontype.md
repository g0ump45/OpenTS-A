---
key: Report
scope: weapontype
label: Firing sounds
see_also: ["Anim", "DropPodWeapon"]
when_omitted:
  kind: value
  value: ""
---

Which entry is played at the muzzle is decided once, when the firing object is created, and never again: the object draws a number then and uses it to index the list for the rest of its life. A list of several entries therefore gives one sound per object rather than variety between shots, and two objects of the same type may well pick the same one.

```ini title="rules.ini"
[MyGatling] ; example WeaponType
Report=TSGUN4,CHAINGN1,INFGUN3 ; registered sound names
```

An entry that does not match a registered sound is dropped without complaint, so `Report=none` produces an empty list rather than an error, and a misspelling quietly shortens the list. Writing the key with nothing after the `=` is a different thing: the read finds no value and keeps whatever an earlier rules file set, so an inherited list cannot be cleared that way.

Three other paths play the list, and all three pick from it afresh each time rather than using the object's fixed choice: an EM pulse cannon firing at its stored destination, a Tiberium floater that has just stung something — which plays it again for every cell of the sweep still to come — and a descending drop pod laying [covering fire](/keys/droppodweapon/) on the cell below it.

:::danger[An empty list crashes those three paths]
The ordinary firing path checks that the list holds something before picking from it. The EM pulse cannon, the floater's sting and the drop pod's covering fire do not, and dividing by the length of an empty list stops the game. A weapon reached by any of those paths must carry at least one entry that resolves to a registered sound.
:::
