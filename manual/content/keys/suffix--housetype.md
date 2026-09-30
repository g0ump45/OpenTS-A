---
key: Suffix
scope: housetype
label: Country filename extension
summary: Parsed country filename extension that the engine never uses.
no_effect: true
see_also: [Prefix, Name]
when_omitted:
  kind: unchanged
  note: The suffix already stored, which is empty until some rules file sets one.
---

The name promises the three-letter extension of a country-specific file. The value is cut to three characters as it is stored, and in a running game the only thing that reads it back composes a description of a team type for a debugging display, which a release build does not carry. No gameplay path reads it.

```ini title="rules.ini"
[GDI]
Suffix=GDI
```

Unlike its neighbors this key cannot be cleared: the read discards a result of no characters and leaves whatever an earlier rules file stored in place.
