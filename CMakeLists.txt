cmake_minimum_required(VERSION 3.25)

project(WellWatch
    VERSION 0.1.0
    DESCRIPTION "Water level monitoring for a well and a reservoir"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(WELLWATCH_WARNINGS_AS_ERRORS "Treat compiler warnings as errors (on in CI)" OFF)
option(WELLWATCH_CLANG_TIDY "Run clang-tidy on WellWatch targets while compiling" OFF)

include(cmake/ProjectOptions.cmake)

include(CTest)
if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.tar.gz
        URL_HASH SHA256=65fab701d9829d38cb77c14acdc431d2108bfdbf8979e40eb8ae567edf10b27c
        SYSTEM)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

add_subdirectory(hub)
