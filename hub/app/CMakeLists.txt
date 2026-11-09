add_executable(wellwatch-hub main.cpp)
target_link_libraries(wellwatch-hub PRIVATE wellwatch::core)
wellwatch_configure_target(wellwatch-hub)
