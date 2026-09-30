/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2025 Electronic Arts Inc.
 * Copyright 2026 OpenTS contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

/* $Header: /CounterStrike/DROP.CPP 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : DROP.CPP                                                     *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 01/24/96                                                     *
 *                                                                                             *
 *                  Last Update : January 24, 1996 [JLB]                                       *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "drop.h"

#include "font.h"
#include "shapeset.h"


/// <summary>
/// Creates a drop down list gadget.
/// This routine builds an edit box with a list box and a drop button attached to it.
/// The list box remains detached from the display until the button is pressed, at
/// which point it is dropped down beneath the edit box.
/// </summary>
/// <param name="id">The button ID reported to the dialog when a selection is made.</param>
/// <param name="text">Buffer that holds the text of the currently selected item.</param>
/// <param name="max_len">The maximum number of characters the text buffer can hold.</param>
/// <param name="flags">The text print flags to render the edit box and list with.</param>
/// <param name="h">The pixel height of the list box when it is dropped down.</param>
/// <param name="up">The shape for the list's scroll up arrow.</param>
/// <param name="down">The shape for the list's scroll down arrow and for the drop button.</param>
DropListClass::DropListClass(int id, char * text, int max_len, TextPrintType flags, int x, int y, int w, int h, ShapeSet const * up, ShapeSet const * down) :
	BASECLASS(id, text, max_len, flags, x, y, w, 18, ALPHANUMERIC),
	IsDropped(false),
	ListHeight(h),
	DropButton(0, down, x+w, y),
	List(0, x, y+down->Get_Height(), w+down->Get_Width(), h, flags, up, down)
{
	FontClass *font = Font_From_TPF(flags);
	BASECLASS::Height = font->Get_Height()+1;
	List.Make_Peer(*this);
	DropButton.Make_Peer(*this);
}


/// <summary>
/// Detaches the drop list from the display.
/// The list is collapsed first, then the list box, the drop button, and the edit box
/// itself are all zapped so that none of them refer to a display that is going away.
/// </summary>
void DropListClass::Zap(void)
{
	Collapse();
	List.Zap();
	DropButton.Zap();
	BASECLASS::Zap();
}


/// <summary>
/// Adds this drop list to a gadget list.
/// The drop button is linked in alongside the edit box so that the dialog processes
/// both halves of the gadget.
/// </summary>
/// <param name="object">The gadget list to attach this drop list to.</param>
/// <returns>Returns with a reference to the head of the gadget list.</returns>
LinkClass & DropListClass::Add(LinkClass & object)
{
	DropButton.Add(object);
	return((DropListClass &)BASECLASS::Add(object));
}


/// <summary>
/// Adds this drop list to the end of a gadget list.
/// The drop button is linked in alongside the edit box so that the dialog processes
/// both halves of the gadget.
/// </summary>
/// <param name="object">The gadget list to attach this drop list to.</param>
/// <returns>Returns with a reference to the head of the gadget list.</returns>
LinkClass & DropListClass::Add_Tail(LinkClass & object)
{
	DropButton.Add_Tail(object);
	return((DropListClass &)BASECLASS::Add_Tail(object));
}


/// <summary>
/// Adds this drop list to the head of a gadget list.
/// The drop button is linked in alongside the edit box so that the dialog processes
/// both halves of the gadget.
/// </summary>
/// <param name="object">The gadget list to attach this drop list to.</param>
/// <returns>Returns with a reference to the head of the gadget list.</returns>
LinkClass & DropListClass::Add_Head(LinkClass & object)
{
	DropButton.Add_Head(object);
	return((DropListClass &)BASECLASS::Add_Head(object));
}


/// <summary>
/// Removes this drop list from the gadget list.
/// The list box is collapsed first, so that a dropped down list does not linger on
/// the display after the drop list that owns it has gone.
/// </summary>
/// <returns>Returns with a pointer to the head of the gadget list, or NULL if nothing
/// remains in it.</returns>
LinkClass * DropListClass::Remove(void)
{
	if (IsDropped) {
		Collapse();
	}
	DropButton.Remove();
	return((DropListClass *)BASECLASS::Remove());
}


/// <summary>
/// Adds an item to the drop down list.
/// The text added also becomes the displayed contents of the edit box, so the item
/// most recently added is the one the player sees.
/// </summary>
/// <param name="text">The text of the item to add.</param>
/// <returns>Returns with the index the item was added at.</returns>
int DropListClass::Add_Item(char const * text)
{
	strncpy(String, text, MaxLength);
	Flag_To_Redraw();
	return(List.Add_Item(text));
}


/// <summary>
/// Fetches the text of the currently selected item.
/// </summary>
/// <returns>Returns with a pointer to the text of the selected item.</returns>
char const * DropListClass::Current_Item(void)
{
	return(List.Current_Item());
}


/// <summary>
/// Fetches the index of the currently selected item.
/// </summary>
/// <returns>Returns with the list index of the selected item.</returns>
int DropListClass::Current_Index(void)
{
	return(List.Current_Index());
}


/// <summary>
/// Sets the currently selected item by index.
/// The text of the item picked becomes the contents of the edit box. An index that
/// falls outside the list clears the edit box instead.
/// </summary>
/// <param name="index">The index of the item to select.</param>
void DropListClass::Set_Selected_Index(int index)
{
	if ((unsigned)index < (unsigned)List.Count()) {
		List.Set_Selected_Index(index);
		strcpy(String, List.Get_Item(Current_Index()));
	} else {
		String[0] = '\0';
	}
}


/// <summary>
/// Clears the input focus from this gadget.
/// The dropped down list is collapsed, since a drop list that has lost the focus has
/// no business covering the display.
/// </summary>
void DropListClass::Clear_Focus(void)
{
	Collapse();
}


/// <summary>
/// Handles input events from the attached list box and drop button.
/// This routine is how the drop list learns that its button was clicked or that an
/// item was picked. The button toggles the list between expanded and collapsed, and
/// a pick copies the item text into the edit box and reports the drop list's own
/// button ID back to the dialog.
/// </summary>
/// <param name="flags">The input event flags that triggered this notification.</param>
/// <param name="key">The key code returned to the dialog; set when a selection is made.</param>
/// <param name="whom">The peer gadget that generated the event.</param>
void DropListClass::Peer_To_Peer(unsigned flags, KeyNumType & key, ControlClass & whom)
{
	if (&whom == &DropButton) {
		if (flags & LEFTRELEASE) {
			if (IsDropped) {
				Collapse();
				key = (KeyNumType)(ID | KN_BUTTON);
			} else {
				Expand();
			}
		}
	}

	if (&whom == &List) {
		strncpy(String, List.Current_Item(), MaxLength);
		Flag_To_Redraw();
		key = (KeyNumType)(ID | KN_BUTTON);
	}
}


/// <summary>
/// Drops the list box down so that it is visible.
/// The list box is positioned under the edit box and linked into the same gadget
/// list, so it will be drawn and will process input until it is collapsed again.
/// </summary>
void DropListClass::Expand(void)
{
	if (!IsDropped) {
		List.X = X;
		List.Y = Y+18;
		List.Width = Width;
		List.Height = ListHeight;
		List.Add(Head_Of_List());
		List.Flag_To_Redraw();
		IsDropped = true;
	}
}


/// <summary>
/// Hides the dropped down list box.
/// The list box is unlinked from the gadget list, but its contents are left intact
/// so that the drop list can be expanded again later.
/// </summary>
void DropListClass::Collapse(void)
{
	if (IsDropped) {
		List.Remove();
		IsDropped = false;
	}
}


/// <summary>
/// Assigns another drop list to this one.
/// The peer links are rebuilt so that the copied list box and drop button report
/// their events to this drop list rather than to the original.
/// </summary>
/// <param name="list">The drop list to copy.</param>
/// <returns>Returns with a reference to this drop list.</returns>
DropListClass & DropListClass::operator = (DropListClass const & list)
{
	if (this == &list) return(*this);
	BASECLASS::operator =(list);
	List = list.List;
	IsDropped = list.IsDropped;
	ListHeight = list.ListHeight;
	DropButton = list.DropButton;
	List.Make_Peer(*this);
	DropButton.Make_Peer(*this);
	return(*this);
}


/// <summary>
/// Creates a copy of an existing drop list.
/// The peer links are rebuilt so that the copied list box and drop button report
/// their events to this drop list rather than to the original.
/// </summary>
/// <param name="list">The drop list to copy.</param>
DropListClass::DropListClass(DropListClass const & list) :
	BASECLASS(list),
	IsDropped(list.IsDropped),
	ListHeight(list.ListHeight),
	DropButton(list.DropButton),
	List(list.List)
{
	List.Make_Peer(*this);
	DropButton.Make_Peer(*this);
}


/// <summary>
/// Sets the pixel position of the drop list.
/// The list box and the drop button are moved along with the edit box so that the
/// gadget stays assembled.
/// </summary>
/// <param name="x">The new pixel X coordinate of the edit box.</param>
/// <param name="y">The new pixel Y coordinate of the edit box.</param>
void DropListClass::Set_Position(int x, int y)
{
	BASECLASS::Set_Position(x, y);
	List.Set_Position(x, y + DropButton.Get_Shape_Data()->Get_Height());
	DropButton.Set_Position(x + Width, y);
}


/// <summary>
/// Sets the currently selected item by name.
/// This routine is used when the caller knows the text of the item but not its
/// position in the list. The comparison ignores case, and a name that is not in the
/// list leaves the current selection alone.
/// </summary>
/// <param name="text">The text of the item to select.</param>
void DropListClass::Set_Selected_Index(char const * text)
{
	if (text) {
		for (int index = 0; index < Count(); index++) {
			if (stricmp(text, List.Get_Item(index)) == 0) {
				Set_Selected_Index(index);
				break;
			}
		}
	}
}
