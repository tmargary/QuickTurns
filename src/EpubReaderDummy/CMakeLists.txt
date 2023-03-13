cmake_minimum_required(VERSION 3.0)

project(EpubReader)
set(CMAKE_CXX_STANDARD 20)

include("/home/tigran/vcpkg/scripts/buildsystems/vcpkg.cmake")

add_executable(EpubReader EpubReader.cpp)

find_package(ZLIB REQUIRED)
find_package(libzip CONFIG REQUIRED)
find_package(libzippp CONFIG REQUIRED)
find_package(Boost 1.36.0 COMPONENTS iostreams filesystem zip)

include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(EpubReader ${Boost_LIBRARIES} ZLIB::ZLIB libzip::zip libzippp::libzippp)
