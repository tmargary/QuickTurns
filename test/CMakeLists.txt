# Include the GTest library
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Add subdirectory for AllTests
add_subdirectory(AllTests)
