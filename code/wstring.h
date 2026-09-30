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

/****************************************************************************\
*        C O N F I D E N T I A L --- W E S T W O O D   S T U D I O S         *
******************************************************************************
Project Name: Carpenter  (The RedAlert ladder creator)
File Name   : main.cpp
Author      : Neal Kettler
Start Date  : June 1, 1997
Last Update : June 17, 1997
\****************************************************************************/

#pragma once

#include <cstdio>
#include <cstdlib>

class Wstring
{
public:
	Wstring(void);
	Wstring(const Wstring& other);
	Wstring(char const* string);
	~Wstring(void);

	void			clear(void);

	char			cat(char const* string);
	char			cat(unsigned int size, char const* string);
	char			cat(Wstring const& string);

	void			cellCopy(char* dest, unsigned int len) const;
	char			remove(int pos, int count);
	char			removeChar(char c);
	void			removeSpaces(void);
	char*			get(void) const;
	char			get(unsigned int index);
	unsigned int	length(void) const;
	char			insert(char c, unsigned int pos);
	char			insert(char const* instring, unsigned int pos);
	char			replace(char const* replaceThis, char const* withThis);
	char			set(char const* str);
	char			set(unsigned int size, char const* str);
	char			set(char c, unsigned int index);
	void			setSize(int bytes);  // create an empty string
	void			toLower(void);
	void			toUpper(void);
	char			truncate(unsigned int len);
	char			truncate(char c);  // trunc after char c
	int				getToken(int offset, char const* delim, Wstring& out) const;
	int				getLine(int offset, Wstring& out) const;

	bool			operator==(char const* other) const;
	bool			operator==(Wstring const& other) const;
	bool			operator!=(char const* other) const;
	bool			operator!=(Wstring const& other) const;

	Wstring&		operator=(char const* other);
	Wstring&		operator=(Wstring const& other);
	Wstring&		operator+=(char const* other);
	Wstring&		operator+=(Wstring const& other);
	Wstring			operator+(char const* other) const;
	Wstring			operator+(Wstring const& other) const;

private:
	char*			str;    // Pointer to allocated string.
};
