add_library(ReaderView ReaderView.cpp)

find_package(Qt5 COMPONENTS Widgets)

target_link_libraries(ReaderView PRIVATE Qt::Widgets)
target_include_directories(ReaderView PUBLIC include)
