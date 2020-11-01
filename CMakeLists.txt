cmake_minimum_required(VERSION 3.5)

project(elvex VERSION 2.15.0)

set(CMAKE_CXX_STANDARD 11)
include_directories(src)

find_package(BISON)
if (BISON_FOUND)
    BISON_TARGET(rulesyacc src/rulesyacc.y ${CMAKE_CURRENT_BINARY_DIR}/src/rulesyacc.cc
            DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/src/rulesyacc.hpp
            COMPILE_FLAGS "-p rules")
else()
    message("bison not found")
endif()

find_package(FLEX)
if (FLEX_FOUND)
    FLEX_TARGET(ruleslex src/ruleslex.l ${CMAKE_CURRENT_BINARY_DIR}/src/ruleslex.cc
            COMPILE_FLAGS "-Prules")
else()
    message("flex not found")
endif()

ADD_FLEX_BISON_DEPENDENCY(ruleslex rulesyacc)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(ELVEX_COMMON_SOURCES
        ${BISON_rulesyacc_OUTPUTS}
        ${FLEX_ruleslex_OUTPUTS}
        src/bitset.cc
        src/bitset.hpp
        src/compacted-lexicon-buffer.cc
        src/compacted-lexicon-buffer.hpp
        src/compacted-lexicon-fsa.cc
        src/compacted-lexicon-fsa.hpp
        src/compacted-lexicon-info.cc
        src/compacted-lexicon-info.hpp
        src/compacted-lexicon-tree.cc
        src/compacted-lexicon-tree.hpp
        src/compacted-lexicon.cc
        src/compacted-lexicon.hpp
        src/config.hpp
        src/entries.cc
        src/entries.hpp
        src/entry.cc
        src/entry.hpp
        src/environment.cc
        src/environment.hpp
        src/fatal_exception.cpp
        src/fatal_exception.hpp
        src/feature.cc
        src/feature.hpp
        src/features.cc
        src/features.hpp
        src/flags.cc
        src/flags.hpp
        src/forest.cc
        src/forest.hpp
        src/forestidentifier.cc
        src/forestidentifier.hpp
        src/forestmap.cc
        src/forestmap.hpp
        src/grammar.cc
        src/grammar.hpp
        src/uniq-id.cc
        src/uniq-id.hpp
        src/item.cc
        src/item.hpp
        src/itemset.cc
        src/itemset.hpp
        src/lexicon.cc
        src/lexicon.hpp
        src/list.cc
        src/list.hpp
        src/listfeatures.cc
        src/listfeatures.hpp
        src/memoization-map.cc
        src/memoization-map.hpp
        src/memoization-value.cc
        src/memoization-value.hpp
        src/messages.hpp
        src/node.cc
        src/node.hpp
        src/parser.cc
        src/parser.hpp
        src/rule.cc
        src/rule.hpp
        src/serializable.cc
        src/serializable.hpp
        src/shared_ptr.hpp
        src/statement.cc
        src/statement.hpp
        src/statements.cc
        src/statements.hpp
        src/synthesizer.cc
        src/synthesizer.hpp
        src/terms.cc
        src/terms.hpp
        src/value.cc
        src/value.hpp
        src/variableflag.cc
        src/variableflag.hpp
        src/vartable.cc
        src/vartable.hpp)

configure_file(
        src/config.hpp.in
        src/config.hpp
        @ONLY)

add_executable(elvex ${ELVEX_COMMON_SOURCES} src/elvex.cc src/fatal_exception.cpp src/fatal_exception.hpp)
target_compile_options(elvex PUBLIC -std=c++11 -O3 -Wall -Wextra -Wno-deprecated -Wno-sign-compare -Wno-missing-field-initializers)
add_executable(elvexdebug  ${ELVEX_COMMON_SOURCES} src/elvex.cc)
target_compile_options(elvexdebug PUBLIC -std=c++11 -O3 -Wall -Wextra -Wno-deprecated -Wno-sign-compare  -Wno-missing-field-initializers)

find_package(LibXml2 REQUIRED)
if (LibXml2_FOUND)
    target_compile_definitions(elvex PUBLIC
            OUTPUT_XML
            MEMOIZATION
            RESTORE_MEMORY
            MAXLENGTH=1000
            MAXUSAGES=10000
            MAXCARDINAL=1000000
            MAXATTEMPTS=100
            #MAXBITS=512
            )
    target_link_libraries(elvex PUBLIC ${LIBXML2_LIBRARIES})
    target_include_directories(elvex PUBLIC ${LIBXML2_INCLUDE_DIR})
    target_compile_definitions(elvexdebug PUBLIC OUTPUT_XML
        TRACE_OPTION
        #TRACE_MEMOIZATION
        #TRACE_EVAL
)
    target_link_libraries(elvexdebug PUBLIC ${LIBXML2_LIBRARIES})
    target_include_directories(elvexdebug PUBLIC ${LIBXML2_INCLUDE_DIR})
else()
    message("libxml2 not found")
endif()

add_executable(elvexbuildLexicon ${ELVEX_COMMON_SOURCES} src/buildlexicon.cc)
target_compile_options(elvexbuildLexicon PUBLIC -std=c++11 -O3 -Wall -Wextra -Wno-deprecated -Wno-sign-compare  -Wno-missing-field-initializers)

FLEX_TARGET(postedition_en src/postedition_en.l ${CMAKE_CURRENT_BINARY_DIR}/src/postedition_en.cc)
add_executable(elvexpostedition_en ${FLEX_postedition_en_OUTPUTS})
target_compile_options(elvexpostedition_en PUBLIC -std=c++11 -O3 -Wall -Wextra -Wno-deprecated -Wno-sign-compare  -Wno-missing-field-initializers)

FLEX_TARGET(postedition_fr src/postedition_fr.l ${CMAKE_CURRENT_BINARY_DIR}/src/postedition_fr.cc)
add_executable(elvexpostedition_fr ${FLEX_postedition_fr_OUTPUTS})
target_compile_options(elvexpostedition_fr PUBLIC -std=c++11 -O3 -Wall -Wextra -Wno-deprecated -Wno-sign-compare  -Wno-missing-field-initializers)

install(TARGETS elvex elvexdebug elvexbuildLexicon elvexpostedition_en elvexpostedition_fr
        RUNTIME DESTINATION bin
        )
