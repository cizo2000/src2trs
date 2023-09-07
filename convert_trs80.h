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

// convert_trs80.h

#ifndef __CONVERT_TRS80__H
#define __CONVERT_TRS80__H

#include "constants.h"

unsigned char* convert_trs80(unsigned char* bitmap, int verbose=0);
int save_trs80_memory(std::string filename, int verbose=0);

#endif // __CONVERT_TRS80__H
