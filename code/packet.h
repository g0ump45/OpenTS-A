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

/***************************************************************************
 *                                                                         *
 *                 Project Name : Westwood Auto Registration App           *
 *                                                                         *
 *                    File Name : PACKET.H                                 *
 *                                                                         *
 *                   Programmer : Philip W. Gorrow                         *
 *                                                                         *
 *                   Start Date : 04/19/96                                 *
 *                                                                         *
 *                  Last Update : April 19, 1996 [PWG]                     *
 *                                                                         *
 * This header defines the functions for the PacketClass.  The packet      *
 * class is used to create a linked list of field entries which can be     *
 * converted to a linear packet in a COMMS API compatible format.          *
 *                                                                         *
 * Packets can be created empty and then have fields added to them or can  *
 * be created from an existing linear packet.                              *
 *                                                                         *
 *-------------------------------------------------------------------------*
 * Functions:                                                              *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once


#include "field.h"

class PacketClass {
	public:
		PacketClass(short id = 0)
		{
			Size 			= 0;
			ID				= id;
			Head			= 0;
		}
		PacketClass(char *cur_buf);
		~PacketClass(void);

		//
		// This function allows us to add a field to the start of the list.  As the field is just
		//   a big linked list it makes no difference which end we add a member to.
		//
		void Add_Field(FieldClass *field);

		//
		// These conveniance functions allow us to add a field directly to the list without
		// having to worry about newing one first.
		//
		void Add_Field(char const *field, char data) {Add_Field(new FieldClass(field, data));};
		void Add_Field(char const *field, unsigned char data) {Add_Field(new FieldClass(field, data));};
		void Add_Field(char const *field, short data) {Add_Field(new FieldClass(field, data));};
		void Add_Field(char const *field, unsigned short data) {Add_Field(new FieldClass(field, data));};
		void Add_Field(char const *field, int data) {Add_Field(new FieldClass(field, data));};
		void Add_Field(char const *field, unsigned int data) {Add_Field(new FieldClass(field, data));};
		void Add_Field(char const *field, char const *data) {Add_Field(new FieldClass(field, data));};
		void Add_Field(char const *field, void *data, int length) {Add_Field(new FieldClass(field, data, length));};

		//
		// These functions search for a field of a given name in the list and
		// return the data via a reference value.
		//
		FieldClass *Find_Field(char const *id);
		bool Get_Field(char const *id, char &data);
		bool Get_Field(char const *id, unsigned char &data);
		bool Get_Field(char const *id, short &data);
		bool Get_Field(char const *id, unsigned short &data);
		bool Get_Field(char const *id, int &data);
		bool Get_Field(char const *id, unsigned int &data);
		bool Get_Field(char const *id, char *data);
		bool Get_Field(char const *id, void *data, int &length);

		char *Create_Comms_Packet(int &size);

	private:
		unsigned short 	Size;
		short 				ID;
		FieldClass			*Head;
		FieldClass			*Current;
};
