cmake_minimum_required(VERSION 3.21)
project(TP_AEDS_II)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

set(SOURCE_FILES NossaPaty.c NossaPaty.h novaHash.c novaHash.h indicePaty.c indicePaty.h indiceHash.c indiceHash.h main.c)

add_executable(TP_AEDS_II ${SOURCE_FILES})

target_link_libraries(TP_AEDS_II PRIVATE m)
