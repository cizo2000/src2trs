cmake_minimum_required(VERSION 3.18.0)

project(scr2trs)

add_executable(scr2trs main.cpp scr.cpp scr.h convert_trs80.h convert_trs80.cpp my_utils.h my_utils.cpp)

install(TARGETS scr2trs RUNTIME DESTINATION bin)
