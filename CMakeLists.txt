cmake_minimum_required(VERSION 3.23)
project(FloydAlgorithm)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(FloydAlgorithm main.cpp conio21/conio2.h conio21/conio.c interface.h appconsts.h)
