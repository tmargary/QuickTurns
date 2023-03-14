add_library(Util Util.cpp)
target_include_directories(Util PUBLIC include)

find_package(Boost REQUIRED COMPONENTS iostreams filesystem)
target_link_libraries(Util PUBLIC Boost::iostreams Boost::filesystem)
