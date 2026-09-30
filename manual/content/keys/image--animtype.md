---
key: Image
scope: animtype
label: Animation Image ID
see_also: [End, Theater, NewTheater]
when_omitted:
  kind: computed
  note: Uses the AnimType ID as the animation Image ID.
---

The shape named here is applied over artwork the type is already holding. An animation is loaded from `<AnimType ID>.SHP` as soon as its type is created, and this setting replaces that shape only when a file under the new name is actually present; a name that matches nothing leaves the animation drawing its own ID's artwork. An animation that never found a shape under either name draws nothing and is otherwise undisturbed.

Replacing the shape does not re-measure the stage count. It was taken from the first shape the type got hold of and is kept, which [`End`](/keys/end/) covers, so an animation that already had artwork of its own plays as many stages as that artwork had however long the new shape is. The two theater paths treat this setting differently in turn: [`Theater=yes`](/keys/theater/#scope-animtype) renames the AnimType ID and ignores it, while [`NewTheater=yes`](/keys/newtheater/#scope-animtype) rewrites the name given here.
