add_library(Util STATIC Checksum.cpp Dirs.cpp)
target_include_directories(Util PUBLIC include)

find_package(OpenSSL REQUIRED)
target_link_libraries(Util PUBLIC OpenSSL::SSL OpenSSL::Crypto)
