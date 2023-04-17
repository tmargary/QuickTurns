add_library(DataBase DataBase.cpp)
target_include_directories(DataBase PUBLIC include)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(DataBase PUBLIC unofficial::sqlite3::sqlite3)