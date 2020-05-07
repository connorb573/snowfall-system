cmake_minimum_required(VERSION 3.14)
project(Graphics_Project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DMACOS -framework GLUT -framework OpenGL") # compiler version and compiler flags.

set(SOURCE_FILES particles.cpp string.h frames.h printvalues.h) # which files should be compiled

add_executable(Graphics_Project ${SOURCE_FILES}) # which files should produce executables

