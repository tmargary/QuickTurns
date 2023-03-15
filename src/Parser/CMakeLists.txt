add_executable(Parser Parser.cpp)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(Parser PRIVATE Qt5::Widgets)