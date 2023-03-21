find_package(Qt5 COMPONENTS Widgets)

add_library(UserInterface STATIC
    StackedView.cpp
    HomeView.cpp
    ReaderView.cpp
)

target_include_directories(UserInterface PUBLIC include)

target_link_libraries(UserInterface PRIVATE Qt::Widgets)
