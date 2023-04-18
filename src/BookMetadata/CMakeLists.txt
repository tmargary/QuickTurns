add_library(BookMetadata BookMetadata.cpp)
target_include_directories(BookMetadata PUBLIC include)

find_package(tinyxml2 CONFIG REQUIRED)
target_link_libraries(BookMetadata PRIVATE tinyxml2::tinyxml2)
