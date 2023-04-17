# Include the GTest library
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add subdirectories for each module's tests
add_subdirectory(TestDataBase)
add_subdirectory(TestArchiveExtractor)