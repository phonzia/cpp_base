cmake_minimum_required(VERSION 3.12)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

project(cppbase VERSION 1.0
        DESCRIPTION "user system of blog"
        LANGUAGES CXX)

include_directories(tools)

set(HEADERS cppbase.h
        tools/cppassert.h
        tools/macros.h
        tools/singleton.hpp
        tools/stringtool.h
        tools/defer.hpp)
set(SOURCE_FILES main.cpp
        tools/stringtool.cpp)

add_executable(cppbase ${SOURCE_FILES} ${HEADERS})
target_compile_features(cppbase PUBLIC cxx_std_17)
