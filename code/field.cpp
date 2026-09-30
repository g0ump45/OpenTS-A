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
 *                    File Name : FIELD.CPP                                *
 *                                                                         *
 *                   Programmer : Philip W. Gorrow                         *
 *                                                                         *
 *                   Start Date : 04/22/96                                 *
 *                                                                         *
 *                  Last Update : April 22, 1996 [PWG]                     *
 *                                                                         *
 *  Actual member function for the field class.                            *
 *-------------------------------------------------------------------------*
 * Functions:                                                              *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "field.h"

#include <cstring>


/// <summary>
/// Creates a field that carries a character value.
/// This routine, and its siblings below, are used by PacketClass as it builds up the
/// field list for a packet. The value is copied into a buffer the field owns.
/// </summary>
/// <param name="id">The four character identifier to tag this field with.</param>
FieldClass::FieldClass(char const *id, char data)
{
	strncpy(ID, id, sizeof(ID));
	DataType = TYPE_CHAR;
	Size		= sizeof(data);
	Data		= new char[Size];
	memcpy(Data, &data, Size);
	Next		= NULL;
}


/// <summary>
/// Creates a field that carries an unsigned character value.
/// The value is copied into a buffer the field owns. Character sized data needs no
/// swapping, so it survives the trip across the network untouched.
/// </summary>
/// <param name="id">The four character identifier to tag this field with.</param>
FieldClass::FieldClass(char const *id, unsigned char data)
{
	strncpy(ID, id, sizeof(ID));
	DataType = TYPE_UNSIGNED_CHAR;
	Size		= sizeof(data);
	Data		= new char[Size];
	memcpy(Data, &data, Size);
	Next		= NULL;
}


/// <summary>
/// Creates a field that carries a short value.
/// The value is copied into a buffer the field owns, and the recorded data type lets
/// the packet byte swap it when it travels to another machine.
/// </summary>
/// <param name="id">The four character identifier to tag this field with.</param>
FieldClass::FieldClass(char const *id, short data)
{
	strncpy(ID, id, sizeof(ID));
	DataType = TYPE_SHORT;
	Size		= sizeof(data);
	Data		= new char[Size];
	memcpy(Data, &data, Size);
	Next		= NULL;
}


/// <summary>
/// Creates a field that carries an unsigned short value.
/// The value is copied into a buffer the field owns, and the recorded data type lets
/// the packet byte swap it when it travels to another machine.
/// </summary>
/// <param name="id">The four character identifier to tag this field with.</param>
FieldClass::FieldClass(char const *id, unsigned short data)
{
	strncpy(ID, id, sizeof(ID));
	DataType = TYPE_UNSIGNED_SHORT;
	Size		= sizeof(data);
	Data		= new char[Size];
	memcpy(Data, &data, Size);
	Next		= NULL;
}


/// <summary>
/// Creates a field that carries a long value.
/// The value is copied into a buffer the field owns, and the recorded data type lets
/// the packet byte swap it when it travels to another machine.
/// </summary>
/// <param name="id">The four character identifier to tag this field with.</param>
FieldClass::FieldClass(char const *id, int data)
{
	strncpy(ID, id, sizeof(ID));
	DataType = TYPE_LONG;
	Size		= sizeof(data);
	Data		= new char[Size];
	memcpy(Data, &data, Size);
	Next		= NULL;
}


/// <summary>
/// Creates a field that carries an unsigned long value.
/// The value is copied into a buffer the field owns, and the recorded data type lets
/// the packet byte swap it when it travels to another machine.
/// </summary>
/// <param name="id">The four character identifier to tag this field with.</param>
FieldClass::FieldClass(char const *id, unsigned int data)
{
	strncpy(ID, id, sizeof(ID));
	DataType = TYPE_UNSIGNED_LONG;
	Size		= sizeof(data);
	Data		= new char[Size];
	memcpy(Data, &data, Size);
	Next		= NULL;
}


/// <summary>
/// Creates a field that carries a text string.
/// The string is copied into the field along with its terminating null, so the caller
/// is free to discard the original.
/// </summary>
/// <param name="id">The four character identifier to tag this field with.</param>
FieldClass::FieldClass(char const *id, char const *data)
{
	strncpy(ID, id, sizeof(ID));
	DataType = TYPE_STRING;
	Size		= (unsigned short)(strlen(data)+1);
	Data		= new char[Size];
	memcpy(Data, data, Size);
	Next		= NULL;
}


/// <summary>
/// Creates a field that carries an arbitrary block of data.
/// Use this routine when the payload is not one of the simple types -- the block is
/// copied verbatim and is not byte swapped when the packet crosses the network.
/// </summary>
/// <param name="id">The four character identifier to tag this field with.</param>
/// <param name="data">Pointer to the block of data to copy into the field.</param>
/// <param name="length">The length of the data block in bytes.</param>
FieldClass::FieldClass(char const *id, void *data, int length)
{
	strncpy(ID, id, sizeof(ID));
	DataType = TYPE_CHUNK;
	Size		= (unsigned short)length;
	Data		= new char[Size];
	memcpy(Data, data, Size);
	Next		= NULL;
}


/// <summary>
/// Destroys the field and releases its data buffer.
/// The field does not unlink itself, so the packet that owns the field list must detach
/// it before deleting it.
/// </summary>
FieldClass::~FieldClass(void)
{
	delete[](Data);
	Data=NULL;
}


/**************************************************************************
 * PACKETCLASS::HOST_TO_NET_FIELD -- Converts host field to net format    *
 *                                                                        *
 * INPUT:      FIELD    * to the data field we need to convert            *
 *                                                                        *
 * OUTPUT:     none                                                       *
 *                                                                        *
 * HISTORY:                                                               *
 *   04/22/1996 PWG : Created.                                            *
 *========================================================================*/
void FieldClass::Host_To_Net(void)
{
	//
	// Before we convert the data type, we should convert the actual data
	//  sent.
	//
	switch (DataType) {
		case TYPE_CHAR:
		case TYPE_UNSIGNED_CHAR:
		case TYPE_STRING:
		case TYPE_CHUNK:
			break;

		case TYPE_SHORT:
		case TYPE_UNSIGNED_SHORT:
			*((unsigned short *)Data) = htons(*((unsigned short *)Data));
			break;

		case TYPE_LONG:
		case TYPE_UNSIGNED_LONG:
			*((unsigned int *)Data) = htonl(*((unsigned int *)Data));
			break;

		//
		// Might be good to insert some type of error message here for unknown
		//   datatypes -- but will leave that for later.
		//
		default:
			break;
	}
	//
	// Finally convert over the data type and the size of the packet.
	//
	DataType = htons(DataType);
	Size 	 	= htons(Size);
}
/**************************************************************************
 * PACKETCLASS::NET_TO_HOST_FIELD -- Converts net field to host format    *
 *                                                                        *
 * INPUT:      FIELD    * to the data field we need to convert            *
 *                                                                        *
 * OUTPUT:     none                                                       *
 *                                                                        *
 * HISTORY:                                                               *
 *   04/22/1996 PWG : Created.                                            *
 *========================================================================*/
void FieldClass::Net_To_Host(void)
{
	//
	// Convert the variables to host order.  This needs to be converted so
	// the switch statement does compares on the data that follows.
	//
	Size 	 	= ntohs(Size);

	DataType = ntohs(DataType);

	//
	// Before we convert the data type, we should convert the actual data
	//  sent.
	//
	switch (DataType) {
		case TYPE_CHAR:
		case TYPE_UNSIGNED_CHAR:
		case TYPE_STRING:
		case TYPE_CHUNK:
			break;

		case TYPE_SHORT:
		case TYPE_UNSIGNED_SHORT:
			*((unsigned short *)Data) = ntohs(*((unsigned short *)Data));
			break;

		case TYPE_LONG:
		case TYPE_UNSIGNED_LONG:
			*((unsigned int *)Data) = ntohl(*((unsigned int *)Data));
			break;

		//
		// Might be good to insert some type of error message here for unknown
		//   datatypes -- but will leave that for later.
		//
		default:
			break;
	}
}
