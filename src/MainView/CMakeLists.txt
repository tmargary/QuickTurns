add_library(MainView MainView.cpp)
target_include_directories(MainView PUBLIC include)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

target_link_libraries(MainView PRIVATE ReaderView Qt${QT_VERSION_MAJOR}::Widgets)
