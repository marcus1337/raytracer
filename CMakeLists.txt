cmake_minimum_required(VERSION 3.10)
if(UNIX)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
endif()
project(raytracer)

include(cmake/Flags.cmake)
include(cmake/FindLibs.cmake)
include(cmake/Target.cmake)

