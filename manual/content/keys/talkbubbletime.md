---
key: TalkBubbleTime
summary: How long a scripted talk bubble stays above the unit that is speaking.
when_omitted:
  kind: value
  value: "5"
---

The figure is written in seconds, with fractions accepted, and multiplied by 60 as it is stored. The countdown it fills runs on the system clock rather than on game frames, and that clock advances 62.5 times a second, so a bubble is shown for slightly less time than the number written: `5` becomes 300 ticks, which run out after 4.8 seconds.

A bubble is placed by the [Talk Bubble...](/mapping/actions/taction-talk-bubble/) trigger action and the [Talk Bubble](/mapping/missions/tmission-talk-bubble/) team mission, both of which also reveal two cells of ground around the speaker so the player can see who is talking. Only one bubble exists at a time, and the trigger action clears it outright when no team is attached to the trigger. Nothing but the drawing of the bubble consults the countdown, so a bubble that runs out simply stops being drawn.
