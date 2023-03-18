set(TEST_SOURCES main.cpp)

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(QuickTurnsTest ${TEST_SOURCES})

target_link_libraries(QuickTurnsTest PRIVATE 
  GTest::GTest
  ArchiveExtractor
  Util
)

gtest_discover_tests(QuickTurnsTest)

# Set output directories for all configurations to be the same
set_target_properties(QuickTurnsTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/test"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/test"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/test"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/test"
)