---
key: Prefix
summary: Parsed country filename letter that the engine never uses.
no_effect: true
see_also: [Suffix, Name]
when_omitted:
  kind: value
  value: "A"
---

The name promises the letter that begins a country-specific filename. Only the first character of the value is kept — the read is given room for one character and a terminator — and no gameplay path consults the stored letter.
