cmake_minimum_required(VERSION 3.10)

project(phil-common-remap)

add_executable(phil-common-remap phil-common-remap.c)
target_compile_options(phil-common-remap PRIVATE -Wall -Wextra)

install(TARGETS phil-common-remap RUNTIME DESTINATION bin)

