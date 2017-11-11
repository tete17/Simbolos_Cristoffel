cmake_minimum_required(VERSION 3.8)
project(Simbolos_Cristoffel)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "-Drestrict=")

set(SOURCE_FILES main.cpp FTensor.hpp)
include_directories(FTensor Symbolics)
add_executable(Simbolos_Cristoffel ${SOURCE_FILES})