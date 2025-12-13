cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(IC746cat C CXX ASM)

pico_sdk_init()

add_executable(example
	example.cpp
	IC746.cpp
)

target_link_libraries(example pico_stdlib)

#generate uf2
pico_add_extra_outputs(example)

pico_enable_stdio_usb(example 1)
	
