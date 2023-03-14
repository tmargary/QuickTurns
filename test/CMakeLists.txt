set(TEST_SOURCES
        main.cpp
)

find_package(GTest REQUIRED)
include(GoogleTest)
#find_package(QuickTurnsLib REQUIRED)

add_executable(QuickTurnsTest ${TEST_SOURCES})

target_link_libraries(QuickTurnsTest PRIVATE 
  GTest::GTest
  ArchiveExtractor
  Util
)

gtest_discover_tests(QuickTurnsTest)
