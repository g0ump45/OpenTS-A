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

#pragma once

#include "abstract.h"
#include "stringid.h"
#include "theater.h"

class CCINIClass;


/***************************************************************************
**	This is the abstract type class. It holds information common to all
**	objects that might exist. This contains the name of the object type.
*/
class AbstractTypeClass : public AbstractClass
{
		typedef AbstractClass BASECLASS;

	public:

		/*
		**	This is the internal control name of the object. This name does
		**	not change regardless of language specified. This is the name
		**	used in scenario control files and for other text based unique
		**	identification purposes.
		*/
		TStringID<24> IniName;

		/*
		**	The translated (language specific) text name number of this object.
		**	This number is used to fetch the object's name from the language
		**	text file. Whenever the name of the object needs to be displayed,
		**	this is used to determine the text string.
		*/
		TStringID<48> GivenName;

		AbstractTypeClass(char const * ininame = NULL);
		virtual ~AbstractTypeClass(void) override;

		bool operator == (char const * string) const { return(IniName == string); }
		bool operator != (char const * string) const { return(IniName != string); }

		virtual void Serialize(SaveStreamClass & stream) override;

		virtual void Compute_CRC(CRCEngine & crc) const override;

		virtual void Init_Theater(TheaterType theater) {}

		virtual bool Read_INI(CCINIClass const & ini);
		virtual bool Write_INI(CCINIClass & ini) const;

		const char * Full_Name(void) const {return(GivenName);}
		char const * Name(void) const {return(IniName);}
};

inline AbstractTypeClass * AbstractClass::As_AbstractTypeClass(void) { return(dynamic_cast<AbstractTypeClass *>(this)); }
inline AbstractTypeClass const * AbstractClass::As_AbstractTypeClass(void) const { return(dynamic_cast<AbstractTypeClass const *>(this)); }
