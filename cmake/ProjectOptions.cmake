# Settings shared by every WellWatch target (not by third-party code).

add_library(wellwatch_warnings INTERFACE)
target_compile_options(wellwatch_warnings INTERFACE
    -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow
    $<$<BOOL:${WELLWATCH_WARNINGS_AS_ERRORS}>:-Werror>)

if(WELLWATCH_CLANG_TIDY)
    find_program(WELLWATCH_CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)
endif()

# Call for each of our own targets: adds the warnings and, if enabled, clang-tidy.
function(wellwatch_configure_target target)
    target_link_libraries(${target} PRIVATE wellwatch_warnings)
    if(WELLWATCH_CLANG_TIDY)
        set_target_properties(${target} PROPERTIES CXX_CLANG_TIDY "${WELLWATCH_CLANG_TIDY_EXE}")
    endif()
endfunction()
