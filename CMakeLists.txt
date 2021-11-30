cmake_minimum_required(VERSION 3.20)
project(lab_3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
set(CMAKE_CXX_FLAGS "-std=c++17 -fopenmp")

add_executable(lab_3 main.cpp menu.cpp menu.h prog1.cpp prog1.h prog2.cpp prog2.h)
