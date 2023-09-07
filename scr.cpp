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

// src.cpp

#include <iostream>
#include <fstream>
#include <cstring>

#include "scr.h"
#include "my_utils.h"

Scr::Scr() {
	clear_bitmap();
	clear_linear_bitmap();
}

int Scr::rfile(const std::string& ifn) {
	std::ifstream ifi;
	
	ifi.open(ifn, std::ifstream::binary);

	if(!ifi.is_open()) {
		std::cerr << "Failed to open file: " << ifn << std::endl;
		return 1;
	}
	
	for(int p = 0; p < 3 ;p++)
		for(int mr = 0; mr < 8; mr++)
			for(int r = 0; r < 8;r++)
				for(int s = 0; s < 32; s++) {
					if(ifi.good()) {
						bitmap[p][mr + r * 8][s] = ifi.get();
					}
				}

	for(int p = 0;p < 3;p++)
		for(int r = 0;r < 8;r++)
			for(int s = 0; s < 32; s++)
				if (ifi.good()) { 
					cols[p][r][s] = ifi.get();
				}

	ifi.close();
	return 0;
}

void Scr::show_linear_bitmap() {
	for(int y = 0; y < SCREEN_HEIGHT; y++) {
		for(int x = 0; x < (SCREEN_WIDTH / BLOCK_WIDTH); x++) {
			std::cout << char_binary_string(linearBitmap[x + y * (SCREEN_WIDTH / BLOCK_WIDTH)]);
		}
		std::cout << std::endl;
		
		if (y % 3 == 2) {
			std::cout << std::endl;
		}
	}
}

void Scr::to_linear() {
	int index = 0;
	
	for(int p = 0; p < 3; p++)
		for(int r = 0; r < 64; r++)
			for(int s = 0; s < 32; s++) {
				linearBitmap[index++] = bitmap[p][r][s];
			}
}

void Scr::clear_linear_bitmap() {
	memset(linearBitmap, 0, sizeof(linearBitmap));
}

void Scr::clear_bitmap() {
	memset(bitmap, 0, sizeof(bitmap));
}

