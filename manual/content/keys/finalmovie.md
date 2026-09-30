---
key: FinalMovie
summary: The movie that plays once a campaign's closing mission is won.
see_also: ["Scenario", "Description", "CD"]
when_omitted:
  kind: value
  value: none
---

The movie plays at the moment a won scenario declares itself the end of the game, just before the credits roll. The value is matched against the registered movie names without regard to letter case; a name that matches none of them, `<none>` included, leaves the campaign on the movie it already had.
