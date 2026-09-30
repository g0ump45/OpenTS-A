---
key: XVelocity
summary: One horizontal axis of the spread of speeds a spark is thrown at.
see_also: ["YVelocity", "MinZVelocity", "ZVelocityRange", "BehavesLike"]
when_omitted:
  kind: value
  value: "1"
---

```ini title="rules.ini"
[MYSPARK] ; a ParticleType registered in [Particles]
BehavesLike=Spark
MaxEC=500
XVelocity=10 ; sparks are thrown up to 10 leptons a frame along this axis, either way
YVelocity=10
MinZVelocity=40
ZVelocityRange=15
```

Every spark in a burst is thrown at its own random speed along this axis — anything up to this figure, either way — measured in leptons a frame. The three axis settings do two jobs at once: together they fix how fast the spark travels, and they fix which way it goes. Whichever direction the holding system then applies — its own spawn direction, or one random direction shared by the whole burst — is added to that vector and the result is scaled back to the speed the three settings produced, so widening the spread makes a burst both faster and looser.

Only [`Spark`](/keys/behaveslike/#scope-particletype) particles are thrown this way. Every other behavior takes its speed from [`Velocity`](/keys/velocity/) and ignores the three axis settings. A negative figure behaves as its magnitude does, since the spread is symmetrical either way.

:::danger[Zero stops the game]
The random speed is drawn by dividing by this figure, so `XVelocity=0` divides by zero and the game stops the moment a spark system holding the type fires its first burst. The same applies to [`YVelocity`](/keys/yvelocity/) and [`ZVelocityRange`](/keys/zvelocityrange/), each of which is divided by separately.
:::
