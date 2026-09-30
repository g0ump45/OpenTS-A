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

bool Receive_Remote_File ( char *file_name, unsigned int file_length, unsigned int crc);
bool Send_Remote_File ( char const *file_name, bool send_to_all, bool show_progress );
bool Get_Scenario_File_From_Host(char *return_name);
bool Find_Local_Scenario (char *filename, unsigned int length, char *digest, bool official);
bool Get_File_From_Host(char *return_name, bool show_progress);
