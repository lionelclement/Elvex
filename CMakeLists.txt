cmake_minimum_required(VERSION 3.12)

project(elvex VERSION 2.28.0)

# Optional experimental instrumentation.
# Both options are OFF by default and do not affect normal builds.
option(ELVEX_EXPERIMENT_METRICS
       "Collect per-generation runtime/chart/forest/saturation metrics" OFF)
option(ELVEX_ABLATE_SYNTHESIZED_HANDOFF
       "Disable synthesized-feature handoff during REDUCE (experimental ablation)" OFF)

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_STANDARD 11)
include_directories(BEFORE "${CMAKE_CURRENT_BINARY_DIR}/generated")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/main")

find_package(BISON REQUIRED)
if (BISON_FOUND)
    BISON_TARGET(rulesyacc src/main/rulesyacc.y ${CMAKE_CURRENT_BINARY_DIR}/generated/rulesyacc.cc
            DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/generated/rulesyacc.hpp
            COMPILE_FLAGS "-p rules")
else()
    message("bison not found")
endif()

find_package(FLEX REQUIRED)
if (FLEX_FOUND)
    FLEX_TARGET(ruleslex src/main/ruleslex.l ${CMAKE_CURRENT_BINARY_DIR}/generated/ruleslex.cc
            COMPILE_FLAGS "-Prules")
else()
    message("flex not found")
endif()

ADD_FLEX_BISON_DEPENDENCY(ruleslex rulesyacc)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(ELVEX_COMMON_SOURCES
        ${BISON_rulesyacc_OUTPUTS}
        ${FLEX_ruleslex_OUTPUTS}
        src/main/bitset.cc
        src/main/bitset.hpp
        src/main/compacted-lexicon-buffer.cc
        src/main/compacted-lexicon-buffer.hpp
        src/main/compacted-lexicon-fsa.cc
        src/main/compacted-lexicon-fsa.hpp
        src/main/compacted-lexicon-info.cc
        src/main/compacted-lexicon-info.hpp
        src/main/compacted-lexicon-tree.cc
        src/main/compacted-lexicon-tree.hpp
        src/main/compacted-lexicon.cc
        src/main/compacted-lexicon.hpp
        src/main/entries.cc
        src/main/entries.hpp
        src/main/entry.cc
        src/main/entry.hpp
        src/main/environment.cc
        src/main/environment.hpp
        src/main/facade.cc
        src/main/facade.hpp
        src/main/fatal_exception.cc
        src/main/fatal_exception.hpp
        src/main/feature.cc
        src/main/feature.hpp
        src/main/features.cc
        src/main/features.hpp
        src/main/flags.cc
        src/main/flags.hpp
        src/main/forest.cc
        src/main/forest.hpp
        src/main/forestidentifier.cc
        src/main/forestidentifier.hpp
        src/main/forestmap.cc
        src/main/forestmap.hpp
        src/main/generator.cc
        src/main/generator.hpp
        src/main/item.cc
        src/main/item.hpp
        src/main/itemset.cc
        src/main/itemset.hpp
        src/main/lexicon.cc
        src/main/lexicon.hpp
        src/main/listfeatures.cc
        src/main/listfeatures.hpp
        src/main/memoization-map.cc
        src/main/memoization-map.hpp
        src/main/memoization-value.cc
        src/main/memoization-value.hpp
        src/main/messages.hpp
        src/main/node.cc
        src/main/node.hpp
        src/main/orderspec.cc
        src/main/orderspec.hpp
        src/main/orderspecs.cc
        src/main/orderspecs.hpp
        src/main/pairp.cc
        src/main/pairp.hpp
        src/main/parser.cc
        src/main/parser.hpp
        src/main/parser_exception.cc
        src/main/parser_exception.hpp
        src/main/rule.cc
        src/main/rule.hpp
        src/main/rules.cc
        src/main/rules.hpp
        src/main/serializable.cc
        src/main/serializable.hpp
        src/main/shared_ptr.hpp
        src/main/statement.cc
        src/main/statement.hpp
        src/main/statements.cc
        src/main/statements.hpp
        src/main/terms.cc
        src/main/terms.hpp
        src/main/uniq-id.cc
        src/main/uniq-id.hpp
        src/main/usage_exception.cc
        src/main/usage_exception.hpp
        src/main/value.cc
        src/main/value.hpp
        src/main/variableflag.cc
        src/main/variableflag.hpp
        src/main/vartable.cc
        src/main/vartable.hpp)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/generated")
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main/config.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/generated/config.hpp"
    @ONLY)

add_executable(elvex ${ELVEX_COMMON_SOURCES} src/main/elvex.cc src/main/fatal_exception.cc src/main/fatal_exception.hpp)

if (ELVEX_EXPERIMENT_METRICS)
    target_compile_definitions(elvex PRIVATE ELVEX_EXPERIMENT_METRICS)
    message(STATUS "ELVEX_EXPERIMENT_METRICS enabled")
endif()

if (ELVEX_ABLATE_SYNTHESIZED_HANDOFF)
    target_compile_definitions(elvex PRIVATE ELVEX_ABLATE_SYNTHESIZED_HANDOFF)
    message(STATUS "ELVEX_ABLATE_SYNTHESIZED_HANDOFF enabled")
endif()

target_compile_options(elvex PUBLIC -O4 -Wall -Wextra -Wno-deprecated -Wno-sign-compare -Wno-missing-field-initializers
#target_compile_options(elvex PUBLIC -g -Wall -Wextra -Wno-deprecated -Wno-sign-compare -Wno-missing-field-initializers
#-DDEBUGYACC\(x\)=x 
#-DDEBUGLEX\(x\)=x 
)

find_package(LibXml2 REQUIRED)
if (LibXml2_FOUND)
    target_compile_definitions(elvex PUBLIC
            MAXFLAGS=16
            OUTPUT_XML
            MAXLENGTH=12000
            MAXUSAGES=12000
            MAXITEMS=12000
            MAXATTEMPTS=1200
            #TRACE_ENVIRONMENT
            #TRACE_BUILD_ENVIRONMENT
            #TRACE_ENABLE_STATEMENT
            #TRACE_APPLY_STATEMENT
            #TRACE_FEATURES
            #TRACE_STEP
            #TRACE_PASS
            #TRACE_UNFOLD
            #TRACE_MEMOIZATION
            #TRACE_LEXICON
        )
    target_link_libraries(elvex PUBLIC ${LIBXML2_LIBRARIES})
    target_include_directories(elvex PUBLIC ${LIBXML2_INCLUDE_DIR})
else()
    message("libxml2 not found")
endif()

add_executable(elvexlexicon ${ELVEX_COMMON_SOURCES} src/main/buildlexicon.cc)
target_compile_options(elvexlexicon PUBLIC -O4 -Wall -Wextra -Wno-deprecated -Wno-sign-compare  -Wno-missing-field-initializers)
target_compile_definitions(elvexlexicon PUBLIC
        #TRACE_DIFF
)

FLEX_TARGET(postedition_en src/main/postedition_en.l ${CMAKE_CURRENT_BINARY_DIR}/generated/postedition_en.cc)
add_executable(elvexpostedition_en ${FLEX_postedition_en_OUTPUTS})
target_compile_options(elvexpostedition_en PUBLIC -O4 -Wall -Wextra -Wno-deprecated -Wno-sign-compare  -Wno-missing-field-initializers)

FLEX_TARGET(postedition_fr src/main/postedition_fr.l ${CMAKE_CURRENT_BINARY_DIR}/generated/postedition_fr.cc)
add_executable(elvexpostedition_fr ${FLEX_postedition_fr_OUTPUTS})
target_compile_options(elvexpostedition_fr PUBLIC -O4 -Wall -Wextra -Wno-deprecated -Wno-sign-compare  -Wno-missing-field-initializers)

install(TARGETS elvex elvexlexicon elvexpostedition_en elvexpostedition_fr
        RUNTIME DESTINATION bin)

# Tests are managed from src/test; fixtures are versioned under data/regression.
include(CTest)
if (BUILD_TESTING)
    add_subdirectory(src/test)
endif()
