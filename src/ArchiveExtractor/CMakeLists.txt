add_library(ArchiveExtractor ArchiveExtractor.cpp)
target_include_directories(ArchiveExtractor PUBLIC include)

find_package(libzip CONFIG REQUIRED)
find_package(libzippp CONFIG REQUIRED)

target_link_libraries(ArchiveExtractor PUBLIC libzip::zip libzippp::libzippp)
