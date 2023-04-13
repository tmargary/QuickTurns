add_library(ReaderView ReaderView.cpp)
target_include_directories(ReaderView PUBLIC include)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

target_link_libraries(ReaderView PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

