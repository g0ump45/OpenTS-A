---
title: Hold the ion blast's warp inside the view
category: fix
release: 0.1.0
targets: []
credit: [ZivDero]
---

An ion cannon blast near the edge of the view no longer risks a crash at the highest
detail level. The blast's shockwave warps the scene by replacing each pixel it covers
with a neighbor fetched up to eight pixels sideways and sixteen rows up or down, and a
blast close enough to the view's edge could fetch that neighbor from past the end of the
frame or from the interface beside the view. A fetch that would come from outside the
view is now refused and the pixel is left alone, so the warp covers exactly the pixels
it always did.
