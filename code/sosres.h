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

/****************************************************************************

   File              : sosres.h

   Programmer(s)     : Don Fowler, Nick Skrepetos
   Date              :

   Purpose           : Include Files For Zortech C++ Compiler

   Last Updated      :

****************************************************************************
               Copyright(c) 1993,1994 Human Machine Interfaces
                            All Rights Reserved
****************************************************************************/

#define  _SOS_RESOURCE
#ifndef  _SOS_RESOURCE
#define  _SOS_RESOURCE

// structure for resource file header
struct _RES_FILE_HEADER
{
   // file version
   WORD     wVersion;

   // file size
   LONG     dwFileSize;

   // number of resources in file
   WORD     wResCount;

   // offset of resource data from top of file
   LONG     dwResOffset;

   // offset of sync track from top of file
   LONG     dwSyncTrackOffset;

};

// structure for resource block header
struct _RES_BLOCK_HEADER
{
   // resource id
   WORD     wID;

   // resource type
   WORD     wResType;

   // offset of next block
   LONG     dwNextBlock;

   // size of the current resource information
   LONG     dwResSize;

   // rate to play block at
   WORD     wBlockRate;

   // id for the sync track to use
   WORD     wSyncTrackID;

};

// structure for sync mark tag
struct _RES_SYNCMARK
{
   // ID of the type of mark being used
   WORD  wID;

   // location in data of sync mark
   LONG  dwSyncOffset;

   // length of sync block
   LONG  dwSyncSize;

   // start sample data
   _SOS_START_SAMPLE sampleData;

};

typedef union
{
   // structure for sync mark tag
   _RES_SYNCMARK  syncMark;

} _RES_TAG;

// union for filter information for prepareWave
typedef union
{
   // filter type
   WORD     wFilterID;

   // structure for volume
   struct   volume
   {
      WORD  wVolume;
   };

   // structure for delay
   struct   delay
   {
      WORD  wDelaySamples;
   };

} _SOS_FILTER;


#endif
