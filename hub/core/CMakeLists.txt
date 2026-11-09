add_library(wellwatch_core
    src/version.cpp)
add_library(wellwatch::core ALIAS wellwatch_core)

target_include_directories(wellwatch_core PUBLIC include)
target_compile_definitions(wellwatch_core PRIVATE WELLWATCH_VERSION="${PROJECT_VERSION}")
wellwatch_configure_target(wellwatch_core)
