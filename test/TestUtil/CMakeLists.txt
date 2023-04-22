# Add the unit test source file
target_sources(RunAllTests PRIVATE testStringOp.cpp testChecksum.cpp)

# Link against the module's source code
target_link_libraries(RunAllTests Util)
