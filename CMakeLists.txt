cmake_minimum_required(VERSION 3.16)

project(QuickTurns VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Set the path to the vspkg.json file
set(VSPKG_JSON_PATH "${CMAKE_SOURCE_DIR}/vcpkg.json")

# Include the vcpkg toolchain file
if(EXISTS "${VSPKG_JSON_PATH}")
    include("${CMAKE_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

find_program(CMAKE_CXX_CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
if (NOT CMAKE_CXX_CLANG_TIDY_EXECUTABLE)
  message("clang-tidy not found")
else()
  message("clang-tidy found")
  set(CMAKE_CXX_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY_EXECUTABLE})
endif()

add_subdirectory(src)
add_subdirectory(test)