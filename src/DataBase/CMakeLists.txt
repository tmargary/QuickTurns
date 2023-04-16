cmake_minimum_required(VERSION 3.16)

project(QuickTurns VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the path to the vspkg.json file
set(VSPKG_JSON_PATH "${CMAKE_SOURCE_DIR}/vcpkg.json")

# Include the vcpkg toolchain file
if(EXISTS "${VSPKG_JSON_PATH}")
    include("/home/nina/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

add_executable(bookDB 
    bmain.cpp
    bookDB.cpp
)

target_link_libraries(bookDB sqlite3)