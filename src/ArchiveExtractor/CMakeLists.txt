add_library(ArchiveExtractor ArchiveExtractor.cpp)
target_include_directories(ArchiveExtractor PUBLIC include)

find_package(libzip CONFIG REQUIRED)
find_package(libzippp CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS iostreams filesystem)

target_link_libraries(ArchiveExtractor PUBLIC Boost::iostreams Boost::filesystem libzip::zip libzippp::libzippp)
