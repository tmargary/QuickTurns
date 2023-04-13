add_subdirectory(MainView)
add_subdirectory(ReaderView)
add_subdirectory(ArchiveExtractor)
add_subdirectory(Util)

add_executable(QuickTurns main.cpp)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

target_link_libraries(QuickTurns PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
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

# Define the test data files to be copied
set(copy_source_dir "${CMAKE_SOURCE_DIR}/test/data/")
set(copy_dest_dir "${CMAKE_BINARY_DIR}/test/data/")
set(copy_file_name "sample.epub")

add_custom_command(
    TARGET QuickTurns POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${copy_dest_dir}
)
add_custom_command(
    TARGET QuickTurns POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy "${copy_source_dir}/${copy_file_name}" "${copy_dest_dir}/${copy_file_name}"
    COMMENT "Copying ${copy_file_name} to build directory")
