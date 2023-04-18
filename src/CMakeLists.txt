add_subdirectory(ArchiveExtractor)
add_subdirectory(UserInterface)
add_subdirectory(BookMetadata)
add_subdirectory(DataBase)
add_subdirectory(Util)

add_executable(QuickTurns 
    main.cpp 
    resources.qrc
)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

target_link_libraries(QuickTurns PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    UserInterface
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

# Copy the files after building the target
file(COPY "${CMAKE_SOURCE_DIR}/src/UserInterface/Server.py" DESTINATION "${CMAKE_BINARY_DIR}/src/UserInterface/")
file(COPY "${CMAKE_SOURCE_DIR}/test/data/sample.epub" DESTINATION "${CMAKE_BINARY_DIR}/test/data/")