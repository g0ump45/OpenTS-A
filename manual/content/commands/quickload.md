---
command_id: QuickLoad
---

Loads the quick save for the kind of game being played: `QUICKSAVE.SAV` in a campaign or `QUICKSAVE_SKIRMISH.SAV` in a skirmish. When that file is missing or was written by another version, the message list says there is no quick save to load and nothing changes. Otherwise the load runs when the frame ends, in place of the options menu, and play resumes in the restored game. A file that fails partway through the restore leaves the player in the options menu behind an error box, as a failed load from the load dialog does. The command does nothing in a game against other machines, during a scripted sequence that has locked input, or once the game is being won or lost.
