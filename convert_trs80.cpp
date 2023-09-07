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

// convert_trs80.cpp

#include <iostream>
#include <bitset>
#include <fstream>
#include <cstring>

#include "convert_trs80.h"
#include "my_utils.h"

unsigned char trs_memory[8192];

unsigned char* convert_trs80(unsigned char* bitmap, int verbose) {
    memset(trs_memory, 0x80, sizeof(trs_memory));
    
    if (verbose) {
        std::cout << "Conversion debug infomation:" << std::endl;
    }
    
    for(int y = 0; y < SCREEN_HEIGHT; y++) {
        for(int x = 0; x < SCREEN_WIDTH; x++) {
            int src_byte_index = y * (SCREEN_WIDTH / BLOCK_HEIGHT) + (x / BLOCK_WIDTH);
            int dest_byte_index = (y / CHUNK_HEIGHT) * (SCREEN_WIDTH / CHUNK_WIDTH) + (x / CHUNK_WIDTH);
            
                       
            unsigned char pixel_value = (bitmap[src_byte_index] >> (7 - x % BLOCK_WIDTH)) & 0x1;
            trs_memory[dest_byte_index] |= (pixel_value << ((y % CHUNK_HEIGHT) * CHUNK_WIDTH + x % CHUNK_WIDTH));
            
            if (verbose) {
                std::cout << "x: " << x << " y: " << y << " si: " << src_byte_index << " di: " << dest_byte_index << " c: " << ((y % CHUNK_HEIGHT) * CHUNK_WIDTH + x % CHUNK_WIDTH) << " sb: " <<  char_binary_string(bitmap[src_byte_index]) << " pv: " << char_binary_string(pixel_value) << " db: " << char_binary_string(trs_memory[dest_byte_index]) << " pm: " << char_binary_string(pixel_value << ((y % CHUNK_HEIGHT) * CHUNK_WIDTH + x % CHUNK_WIDTH)) << std::endl;
            }
        }
    }
    
    return trs_memory;
}

int save_trs80_memory(std::string filename, int verbose) {
    std::ofstream ofi;
    
    ofi.open(filename, std::ifstream::binary);
    
    if (!ofi.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return -1; // Return an error code
    }
    
    ofi.write(reinterpret_cast<const char*>(trs_memory), sizeof(trs_memory));
    
    ofi.close();
    
    if (verbose) {
        std::cout << std::endl << "Written out file: " << filename << std::endl;
    }
    
    return 0;
}
