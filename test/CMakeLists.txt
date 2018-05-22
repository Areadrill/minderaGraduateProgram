enable_testing()

add_executable(tests tests.cpp $<TARGET_OBJECTS:ccl>)

target_link_libraries(tests gtest gtest_main)