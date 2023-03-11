cmake_minimum_required(VERSION 3.16)

project(QuickTurns VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the path to the vspkg.json file
set(VSPKG_JSON_PATH "${CMAKE_SOURCE_DIR}/vcpkg.json")

# Include the vcpkg toolchain file
if(EXISTS "${VSPKG_JSON_PATH}")
    include("${CMAKE_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_program(CMAKE_CXX_CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
if (NOT CMAKE_CXX_CLANG_TIDY_EXECUTABLE)
  message("clang-tidy not found")
else()
  message("clang-tidy found")
  set(CMAKE_CXX_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY_EXECUTABLE})
endif()

set(PROJECT_SOURCES
        main.cpp
        QuickTurns.cpp
        ReaderView.cpp
)

add_executable(QuickTurns ${PROJECT_SOURCES})

target_link_libraries(QuickTurns PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(QuickTurns PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS QuickTurns
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

find_package(GTest REQUIRED)
target_link_libraries(QuickTurns PRIVATE GTest::GTest GTest::Main)