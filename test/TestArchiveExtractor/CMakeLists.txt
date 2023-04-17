# Add the unit test executable
add_executable(TestArchiveExtractor test.cpp)

# Link against the module's source code and the GTest library
target_link_libraries(TestArchiveExtractor ${GTEST_BOTH_LIBRARIES} ArchiveExtractor Util)

# Add the test to the suite
add_test(NAME TestArchiveExtractor COMMAND TestArchiveExtractor)