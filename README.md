# src2trs

Converts ZX Spectrum SCR file to TRS-80 charset map, which can be loaded to screen memory as characters

## How to build

```
mkdir build
cd build
cmake ../CMakeLists.txt
make 
```

## Usage

Run `scr2trs` with input SCR file:

```
scr2trs -i <in_filename> -o <out_filename> [-h]
Args:
        -i <in_filename> : input file
        -o <out_filename> : output file
        -v : verbose output
        -h : help
```

Result is binary output file which contains characters for be loaded to TRS-80 screen memory

**Author: Cizo2000 <cizo2000@gmail.com>**
