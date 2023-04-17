# Add the unit test source file
add_executable(TestDataBase test.cpp)

# Link against the module's source code and the GTest library
target_link_libraries(TestDataBase ${GTEST_BOTH_LIBRARIES} DataBase)

# Add the test to the suite
add_test(NAME TestDataBase COMMAND TestDataBase)
