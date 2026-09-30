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

/* $Header: /CounterStrike/DROP.H 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : DROP.H                                                       *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 07/05/96                                                     *
 *                                                                                             *
 *                  Last Update : July 5, 1996 [JLB]                                           *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "dialog.h"
#include "edit.h"
#include "font.h"
#include "list.h"
#include "shapeset.h"

class ShapeSet;

class DropListClass : public EditClass {
		typedef EditClass BASECLASS;

	public:
		DropListClass(int id, char * text, int max_len, TextPrintType flags, int x, int y, int w, int h, ShapeSet const * up, ShapeSet const * down);
		virtual ~DropListClass(void) override {};

		virtual LinkClass & Add(LinkClass & object) override;
		virtual LinkClass & Add_Tail(LinkClass & object) override;
		virtual LinkClass & Add_Head(LinkClass & object) override;
		virtual LinkClass * Remove(void) override;
		virtual void Zap(void) override;

		virtual int Add_Item(char const * text);
		virtual char const * Current_Item(void);
		virtual int Current_Index(void);
		virtual void Set_Selected_Index(int index);
		virtual void Set_Selected_Index(char const * text);
		virtual void Peer_To_Peer(unsigned flags, KeyNumType &, ControlClass & whom) override;
		virtual void Clear_Focus(void) override;
		virtual int Count(void) const {return(List.Count());};
		virtual char const * Get_Item(int index) const {return(List.Get_Item(index));};

		void Expand(void);
		void Collapse(void);

		virtual void Set_Position(int x, int y) override;

		DropListClass & operator = (DropListClass const & list);
		DropListClass(DropListClass const & list);

		/*
		**	Indicates whether the list box has dropped down or not.
		*/
		bool IsDropped;

		/*
		**	Height of list box when it is expanded.
		*/
		int ListHeight;

		/*
		**	Drop down button.
		*/
		ShapeButtonClass DropButton;

		/*
		**	List object when it is expanded.
		*/
		ListClass List;
};


/*
 * The templated equivalent of DropListClass, built on TListClass. T must
 * behave like a pointer and provide Description() for the edit field text
 * in addition to TListClass's Draw_It() requirement.
 */
template<class T>
class TDropListClass : public EditClass {
		typedef EditClass BASECLASS;

	public:
		TDropListClass(int id, char * text, int max_len, TextPrintType flags, int x, int y, int w, int h, ShapeSet const * up, ShapeSet const * down);
		TDropListClass(TDropListClass<T> const & list);
		virtual ~TDropListClass(void) override {};

		T operator [] (int index) const {return(List[index]);};
		T & operator [] (int index) {return(List[index]);};

		virtual LinkClass & Add(LinkClass & object) override;
		virtual LinkClass & Add_Tail(LinkClass & object) override;
		virtual LinkClass & Add_Head(LinkClass & object) override;
		virtual LinkClass * Remove(void) override;
		virtual void Zap(void) override;

		virtual int Add_Item(T item);
		virtual T Current_Item(void);
		virtual int Current_Index(void);
		virtual void Set_Selected_Index(int index);
		virtual void Set_Selected_Index(T item);
		virtual void Peer_To_Peer(unsigned flags, KeyNumType &, ControlClass & whom) override;
		virtual void Clear_Focus(void) override;
		virtual int Count(void) const {return(List.Count());};
		virtual T Get_Item(int index) const {return(List.Get_Item(index));};

		void Expand(void);
		void Collapse(void);

		virtual void Set_Position(int x, int y) override;

		TDropListClass<T> & operator = (TDropListClass<T> const & list);

		/*
		**	Indicates whether the list box has dropped down or not.
		*/
		bool IsDropped;

		/*
		**	Height of list box when it is expanded.
		*/
		int ListHeight;

		/*
		**	Drop down button.
		*/
		ShapeButtonClass DropButton;

		/*
		**	List object when it is expanded.
		*/
		TListClass<T> List;
};


template<class T>
TDropListClass<T>::TDropListClass(int id, char * text, int max_len, TextPrintType flags, int x, int y, int w, int h, ShapeSet const * up, ShapeSet const * down) :
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


template<class T>
void TDropListClass<T>::Zap(void)
{
	Collapse();
	List.Zap();
	DropButton.Zap();
	BASECLASS::Zap();
}


template<class T>
LinkClass & TDropListClass<T>::Add(LinkClass & object)
{
	DropButton.Add(object);
	return(BASECLASS::Add(object));
}


template<class T>
LinkClass & TDropListClass<T>::Add_Tail(LinkClass & object)
{
	DropButton.Add_Tail(object);
	return(BASECLASS::Add_Tail(object));
}


template<class T>
LinkClass & TDropListClass<T>::Add_Head(LinkClass & object)
{
	DropButton.Add_Head(object);
	return(BASECLASS::Add_Head(object));
}


template<class T>
LinkClass * TDropListClass<T>::Remove(void)
{
	if (IsDropped) {
		Collapse();
	}
	DropButton.Remove();
	return(BASECLASS::Remove());
}


template<class T>
int TDropListClass<T>::Add_Item(T item)
{
	strncpy(String, item->Description(), MaxLength);
	Flag_To_Redraw();
	return(List.Add_Item(item));
}


template<class T>
T TDropListClass<T>::Current_Item(void)
{
	return(List.Current_Item());
}


template<class T>
int TDropListClass<T>::Current_Index(void)
{
	return(List.Current_Index());
}


template<class T>
void TDropListClass<T>::Set_Selected_Index(int index)
{
	if ((unsigned)index < (unsigned)List.Count()) {
		List.Set_Selected_Index(index);
		strncpy(String, List.Get_Item(Current_Index())->Description(), MaxLength);
	} else {
		String[0] = '\0';
	}
}


template<class T>
void TDropListClass<T>::Clear_Focus(void)
{
	Collapse();
}


template<class T>
void TDropListClass<T>::Peer_To_Peer(unsigned flags, KeyNumType & key, ControlClass & whom)
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
		strncpy(String, List.Current_Item()->Description(), MaxLength);
		Flag_To_Redraw();
		key = (KeyNumType)(ID | KN_BUTTON);
	}
}


template<class T>
void TDropListClass<T>::Expand(void)
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


template<class T>
void TDropListClass<T>::Collapse(void)
{
	if (IsDropped) {
		List.Remove();
		IsDropped = false;
	}
}


template<class T>
TDropListClass<T> & TDropListClass<T>::operator = (TDropListClass<T> const & list)
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


template<class T>
TDropListClass<T>::TDropListClass(TDropListClass<T> const & list) :
	BASECLASS(list),
	IsDropped(list.IsDropped),
	ListHeight(list.ListHeight),
	DropButton(list.DropButton),
	List(list.List)
{
	List.Make_Peer(*this);
	DropButton.Make_Peer(*this);
}


template<class T>
void TDropListClass<T>::Set_Position(int x, int y)
{
	BASECLASS::Set_Position(x, y);
	List.Set_Position(x, y + DropButton.Get_Shape_Data()->Get_Height());
	DropButton.Set_Position(x + Width, y);
}


template<class T>
void TDropListClass<T>::Set_Selected_Index(T item)
{
	for (int index = 0; index < Count(); index++) {
		if (item == List.Get_Item(index)) {
			Set_Selected_Index(index);
			break;
		}
	}
}
