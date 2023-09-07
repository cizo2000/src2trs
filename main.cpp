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

// main.cpp


#include <cstdlib>
#include <bitset>
#include <string>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include <iostream>

#include "scr.h"
#include "convert_trs80.h"


void help(char *name) {
	std::cout << name << " -i <in_filename> -o <out_filename> [-h]" << std::endl;
	std::cout << "Args:" << std::endl;
	std::cout << "	-i <in_filename> : input file" << std::endl;
	std::cout << "	-o <out_filename> : output file" << std::endl;
	std::cout << "	-v : verbose output" << std::endl;
	std::cout << "	-h : help" << std::endl;
}

int main(int argc, char** argv)
{
	std::string ifile;
	std::string ofile;
	int opt;
    
    int verbose = 0;

	while((opt = getopt(argc, argv, "i:o:hv")) != -1)
	{
		switch(opt)
		{
			case 'i':
				if(optarg[0] != '-')
					ifile = optarg;
				else
				{
					std::cerr << "ERROR: filename needed" << std::endl;
					exit(1);
				}
				break;

			case 'o':
				if(optarg[0] != '-')
					ofile = optarg;
				else
				{
					std::cerr << "ERROR: filename needed" << std::endl;
					exit(1);
				}
				break;
			case ':':
				std::cerr << std::endl << "ERROR: option argument needed" << std::endl;
				exit(1);
				break;

			case '?':
				if (optopt == 'i' || optopt == 'o' ) {
					std::cerr << "ERROR: filename needed" << std::endl;
				}
				exit(1);
            case 'v':
                verbose = 1;
                break;

			case 'h':
				help(argv[0]);
				exit(1);

			default:
				help(argv[0]);
				exit(1);
				break;
		}
	} 

	if(optind < argc || argc < 5) {
		help(argv[0]);
		exit(1);
	}
	
	Scr screen;

	if(screen.rfile(ifile)) {
        return -1;
    }
    screen.to_linear();
    
    if (verbose) {
        std::cout << "Loaded SCR bitmap:" << std::endl;
        screen.show_linear_bitmap();
    }
    
    auto bitmap = screen.get_linear_bitmap();
    
    unsigned char* trs_memory = convert_trs80(bitmap, verbose);

    if (verbose) {
        std::cout << std::endl << "Resulting bytes in BASIC: " << std::endl;
		
		int line = 100;
        
        for(int i = 0; i < 8192; i++) {
			if ( i % 8 == 0 ) {
				std::cout << std::endl << line++ << " DATA ";
			}
			
            std::cout << static_cast<int>(trs_memory[i]);
			
			if (i % 8 != 7) {
				std::cout << ",";
			}
        }
        
        std::cout << std::endl;
    }
    
    save_trs80_memory(ofile, verbose);
    
    if (verbose) {
        std::cout << std::endl << "All done..." << std::endl;
    }

	return 0;
}
