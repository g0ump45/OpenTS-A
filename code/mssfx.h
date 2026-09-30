/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

class MSSfx
{
	public:
		MSSfx(char const * name, char const * file_name);
		~MSSfx(void);
		char const * Get_Name(void) {return(Name);}
		void Play(int volume);

	private:
		/*
		 * This is the name that this sound effect is played by, so that the screen asking
		 * for it need not know which sample file it lives in.
		 */
		char * Name;

		/*
		 * This points to the raw sample data that gets handed to the audio system. It is
		 * NULL when there is no audio or the sample could not be found, in which case
		 * asking this effect to play is quietly ignored.
		 */
		void * Sample;

		/*
		 * If the sample had to be read off disk rather than being found in a mixfile, then
		 * this flag will be true. The buffer then belongs to this object and is freed
		 * along with it, whereas a mixfile resident sample is merely pointed at.
		 */
		bool Loaded;
};
