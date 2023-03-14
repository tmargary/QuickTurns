add_subdirectory(MainView)
add_subdirectory(ReaderView)
add_subdirectory(ArchiveExtractor)
add_subdirectory(Util)

add_executable(QuickTurns main.cpp)

find_package(Qt5 COMPONENTS Widgets)

target_link_libraries(QuickTurns PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Widgets
    ReaderView
    MainView
    ArchiveExtractor
)

set_target_properties(QuickTurns PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS QuickTurns
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
