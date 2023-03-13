# add_library(EpubReader EpubReader.cpp)

# target_include_directories(EpubReader PUBLIC include)

find_package(ZLIB REQUIRED)
target_link_libraries(EpubReader PRIVATE ZLIB::ZLIB)

add_executable(EpubReader EpubReader.cpp)