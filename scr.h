/*
  scr2trs - ZX Spectrum SCR to TRS-80 converter

  Copyright (c) 2023 Pavol Cizmarik (Cizo2000)

  This software is provided 'as-is', without any express or implied warranty.
  In no event will the authors be held liable for any damages arising from the
  use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it freely,
  subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim
     that you wrote the original software. If you use this software in a product,
     an acknowledgment in the product documentation would be appreciated but is
     not required.

  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.

  3. This notice may not be removed or altered from any source distribution.

*/

// scr.h

#ifndef __SCR_H
#define __SCR_H

#include "constants.h"

class Scr {
	private:
		unsigned char bitmap[3][64][32];
		unsigned char cols[3][8][32];
		
		unsigned char linearBitmap[6144];

	public:
		Scr();
		unsigned char* get_linear_bitmap() { return linearBitmap; }
		
		void clear_bitmap();
		void clear_linear_bitmap();
		void show_linear_bitmap();
		void to_linear();
		int rfile(const std::string& ifn);
};

#endif //__SCR_H
