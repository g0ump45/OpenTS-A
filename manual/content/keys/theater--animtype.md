---
key: Theater
scope: animtype
label: Theater-specific animation artwork
see_also: ["NewTheater", "Image"]
when_omitted:
  kind: value
  value: "no"
---

Once the scenario's theater is settled, the animation's artwork is resolved as its own AnimType ID with the theater's extension — `.TEM` in temperate, `.SNO` in snow — and falls back to `<AnimType ID>.SHP` when that file is absent. The animation is re-resolved on every later theater change unless it is loaded on demand.

```ini title="art.ini"
[MYBLAST] ; an AnimType ID
Theater=yes ; draws MYBLAST.TEM or MYBLAST.SNO, and MYBLAST.SHP if neither is there
```

:::caution[This path ignores the animation's Image ID]
A theater animation is named after its AnimType ID on the path that runs once the theater is known, so an [`Image=`](/keys/image/#scope-animtype) pointing at some other art is not consulted there and the substituted file will not be found under that other name.
:::

The flag is tested before [`NewTheater`](/keys/newtheater/) and wins outright, so an animation marked with both is only ever renamed by extension.
