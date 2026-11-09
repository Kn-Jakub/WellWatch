add_executable(wellwatch_core_tests
    version_test.cpp)
target_link_libraries(wellwatch_core_tests PRIVATE wellwatch::core GTest::gmock_main)
target_compile_definitions(wellwatch_core_tests PRIVATE WELLWATCH_EXPECTED_VERSION="${PROJECT_VERSION}")
wellwatch_configure_target(wellwatch_core_tests)

include(GoogleTest)
# PRE_TEST: tests are listed when ctest runs, not at build time.
gtest_discover_tests(wellwatch_core_tests DISCOVERY_MODE PRE_TEST)
