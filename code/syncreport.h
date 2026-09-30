/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

class EventClass;

void Print_CRCs(EventClass const * events, int count, unsigned const * crc_ring, unsigned ring_size);
bool Report_Out_Of_Sync(EventClass const * events, int count, unsigned const * crc_ring, unsigned ring_size);
void Sync_Report_Reset(void);

bool Sync_Is_Out_Of_Sync(int house_id);
void Sync_Mark_Out_Of_Sync(int house_id);
