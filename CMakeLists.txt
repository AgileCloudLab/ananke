cmake_minimum_required(VERSION 3.15)

project(ananke VERSION 1.0.0 DESCRIPTION "Ananke a C++ wrapper for different compression algorithms")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")

add_library(ananke STATIC
  src/ananke/gzip_compressor.cpp
  )
