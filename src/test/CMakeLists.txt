# Each regression fixture is a separately addressable CTest test.
find_program(BASH_PROGRAM bash REQUIRED)
file(GLOB ELVEX_REGRESSION_RULES CONFIGURE_DEPENDS
     "${PROJECT_SOURCE_DIR}/data/regression/*.rules")
foreach(fixture IN LISTS ELVEX_REGRESSION_RULES)
    get_filename_component(case_name "${fixture}" NAME_WE)
    foreach(cache_mode IN ITEMS 0 1)
        add_test(NAME "regression.${case_name}.cache_${cache_mode}"
                 COMMAND "${BASH_PROGRAM}" "${CMAKE_CURRENT_SOURCE_DIR}/run-regression.sh"
                         "$<TARGET_FILE:elvex>" "$<TARGET_FILE:elvexlexicon>")
        set_tests_properties("regression.${case_name}.cache_${cache_mode}" PROPERTIES
            ENVIRONMENT "ELVEX_TEST_CASE=${case_name};ELVEX_LEXICON_CACHE=${cache_mode}"
            LABELS "regression;cache_${cache_mode}"
            TIMEOUT 120)
    endforeach()
endforeach()

# End-to-end forest/diagnostics smoke test (XML output enabled in ELVEX CMake).
add_test(NAME regression.forest.progress
         COMMAND "${BASH_PROGRAM}" "${CMAKE_CURRENT_SOURCE_DIR}/check-forest.sh"
                 "$<TARGET_FILE:elvex>" "${PROJECT_SOURCE_DIR}/data/regression")
set_tests_properties(regression.forest.progress PROPERTIES
    LABELS "regression;forest"
    TIMEOUT 60)
