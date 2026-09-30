---
title: How to read the manual
description: The kinds of page the manual contains and the conventions each kind follows.
---

The manual documents the OpenTS engine, the files it reads, and the source that implements it. Its pages fall into a few kinds, and each kind follows its own conventions.

## Kinds of page

- **Reference entries** describe one INI key, enum, trigger record, or command. Each pairs a compact specification with explanatory behavior notes.
- **Reference tables** list every setting accepted by a file, section, or object type, and link to the entry for each one.
- **Feature pages** describe one runtime behavior in the order the engine decides it, and link to the settings that control it.
- **Guides** state the steps of one task and the conditions under which it fails.
- **Format pages** describe a file's role, how the engine loads it, and the layout of its records.
- **Engine internals** describe the implementation behind a subsystem and the ownership boundaries it keeps. They assume repository familiarity.
- **Change records** state one deliberate OpenTS change and the migration it requires.

## Finding a page

The sidebar selects one part of the manual and then lists that part's pages. The page being read is marked. When that page is an entry the list does not name individually, the page that contains it is marked instead.

Search covers every page. Results can be narrowed to one part of the manual, and to one topic within it.

## Reading a reference entry

A reference entry combines a compact specification with explanatory behavior notes. These parts serve different purposes.

### Specifications

An INI key specification lists the exact spelling, file, section selector, applicable object types, and value type accepted by the current engine.

Section selectors are shown in INI syntax:

- `[General]` is a literal section name.
- `[<ObjectType ID>]` uses the ID of the object type being defined.
- `[<Image ID>]` uses the value of [`Image=`](/keys/image/). If `Image=` is omitted, the object type ID is used.

Some keys are read from more than one file or section. Their specifications list the read order and precedence rule.

Scripting specifications list the numeric ID, stable engine ID, editor metadata, parameters, and serialized INI record.

### Behavior notes

The prose on a page explains behavior, constraints, examples, and failure cases that are not contained in the specification. It does not replace or restate the specification fields.

### When omitted

Omission behavior can be a literal value, computed, inherited, unchanged, or context-dependent. A literal value is displayed as code. A literal empty string is displayed as **(empty)**.

**Not documented** means this page does not yet state the omission behavior. It does not mean that the engine has no default. **Partially documented** means that only some meanings of a multi-scope key have an omission record.

### Scopes

A scope is one engine reading of a key spelling: one kind of INI section, in one file, read for one purpose. Most keys have a single scope. Some spellings are read in several unrelated places — `Power` is a BuildingType's power figure in one scope and a Tiberium type's damage figure in another — and such a key's page carries one specification per scope.

Each scope has its own heading on the key page, titled by what that reading means, with a stable anchor other pages link to directly: [`Power`](/keys/power/#scope-tiberium) is the Tiberium reading. The specification fields — file, section, applicable types, value type — and the omission behavior belong to each scope separately, because the same spelling can default differently for each of its readers.

The summary at the top of a multi-scope page covers every scope in one sentence, and is what reference tables display; the differences live in the scope sections below it.

Spellings that differ only by uppercase or lowercase letters are distinct keys, not scopes of one key.

## Releases and history

Everything the engine accepted before OpenTS versioning began is the vanilla baseline, so baseline entities have no **Added in** label. An entity that OpenTS has added or changed carries an **Added in** or **Changed in** label, and the full timeline behind it sits at the foot of the page. Removed entities remain available at their established routes for exact searches and compatibility work.
