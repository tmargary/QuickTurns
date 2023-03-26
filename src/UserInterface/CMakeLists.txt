find_package(Qt6 COMPONENTS Core Widgets WebEngineWidgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(UserInterface STATIC
    StackedView.cpp
    HomeView.cpp
    ReaderView.cpp
    Server.cpp
)

target_include_directories(UserInterface PUBLIC include)

target_link_libraries(UserInterface PRIVATE Qt6::Core Qt6::Widgets Qt6::WebEngineWidgets)
