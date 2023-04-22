# Add the unit test executable
add_executable(RunAllTests main.cpp)

# Set the output directory for the executable
set_target_properties(RunAllTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
)

# Link against the GTest library
target_link_libraries(RunAllTests ${GTEST_BOTH_LIBRARIES})

# Add subdirectories for each module's tests
add_subdirectory(../TestDataBase RunAllTests/TestDataBase)
add_subdirectory(../TestArchiveExtractor RunAllTests/TestArchiveExtractor)
add_subdirectory(../TestBookMetadata RunAllTests/TestBookMetadata)
add_subdirectory(../TestUtil RunAllTests/TestUtil)