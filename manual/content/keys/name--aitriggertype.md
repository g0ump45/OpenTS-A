---
key: Name
scope: aitriggertype
label: Type display name
see_also: [Multiplay, SidebarCameoText]
when_omitted:
  kind: computed
  note: The section name, copied into the display name as the type is created.
---

Every registered type carries two names: the section it is declared under, which is what everything else in the rules refers to it by, and this one, which is what a person is shown. The value is held in a 49-byte field, so it is cut off after 48 characters, and it is displayed literally rather than being looked up as a translatable label.

```ini title="rules.ini"
[GAPOWR]
Name=GDI Power Plant
```

It reaches the screen wherever an object or a choice has to be identified: the sidebar's build label and price line, the name shown for the object under the cursor, and the country box in the skirmish and multiplayer setup screens. A country's display name is also matched, alongside its section name, whenever a house is looked up by name — so a house list that names `Civilian` finds the country declared as `[Neutral]`.

There is no way to clear a display name back to nothing. An assignment with no value at all is discarded while the file is being read, so `Name=` on its own leaves whatever was already stored in place.
