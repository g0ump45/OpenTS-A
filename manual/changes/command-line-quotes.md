---
title: Strip quotes from launch options
category: fix
release: 0.1.0
targets: []
credit: [ZivDero, tomsons26]
---

A launch option written with double quotes around it, or around part of it, is now matched
as though the quotes were not there. Arguments were compared exactly as the shell handed
them over, so quoting one — which a path containing a space obliges — stopped it being
recognized.
