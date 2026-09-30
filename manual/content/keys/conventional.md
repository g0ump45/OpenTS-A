---
key: Conventional
summary: A blast landing on water plays a splash from the shared list instead of the warhead's own animations.
see_also: [AnimList, SplashList, EMEffect]
when_omitted:
  kind: value
  value: "no"
---

Only the impact animation changes. Damage, cratering, particles and every other effect of the blast are the same over water as anywhere else.

```ini title="rules.ini"
[MyShellWH] ; example WarheadType
Conventional=yes
AnimList=MYBANG16,MYBANG24 ; skipped over water
```

The splash entries divide the damage into 35-point bands, a wider ladder than the 25-point bands [`AnimList`](/keys/animlist/) uses. The substitution is made from the land type under the impact, and it is skipped for a blast standing above a bridge deck, which plays the warhead's own animation instead.

:::danger[There is no fallback to the warhead's own list]
A blast that takes the splash branch and finds [`SplashList`](/keys/splashlist/) empty produces no animation at all rather than reverting to `AnimList`. The explosions that do not check for a missing animation then crash exactly as [an empty `AnimList`](/keys/animlist/) makes them crash.
:::
