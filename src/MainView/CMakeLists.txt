add_library(MainView MainView.cpp)
target_include_directories(MainView PUBLIC include)

find_package(Qt5 COMPONENTS Widgets)
target_link_libraries(MainView PRIVATE ReaderView Qt::Widgets)
