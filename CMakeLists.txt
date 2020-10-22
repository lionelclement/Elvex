cmake_minimum_required(VERSION 3.5)
project(elvex VERSION 2.15.0)

set(CMAKE_CXX_STANDARD 11)
include_directories(src)

find_package(BISON)
if (BISON_FOUND)
    BISON_TARGET(rulesyacc src/rulesyacc.y ${CMAKE_CURRENT_BINARY_DIR}/src/rulesyacc.cpp
            DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/src/rulesyacc.h
            COMPILE_FLAGS "-p rules")
else()
    message("bison not found")
endif()

find_package(FLEX)
if (FLEX_FOUND)
    FLEX_TARGET(ruleslex src/ruleslex.l ${CMAKE_CURRENT_BINARY_DIR}/src/ruleslex.cpp
            COMPILE_FLAGS "-Prules")
else()
    message("flex not found")
endif()

ADD_FLEX_BISON_DEPENDENCY(ruleslex rulesyacc)
#add_compile_options("-std=c++11;-Wall;-Wextra;-Wno-deprecated")
#add_definitions("-DPACKAGE_VERSION=\"2.15.0\"" )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(ELVEX_SOURCES
        ${BISON_rulesyacc_OUTPUTS}
        ${FLEX_ruleslex_OUTPUTS}
        src/bitset.cpp
        src/bitset.h
        src/compact-lexicon-buffer.cpp
        src/compact-lexicon-buffer.h
        src/compact-lexicon-fsa.cpp
        src/compact-lexicon-fsa.h
        src/compact-lexicon-info.cpp
        src/compact-lexicon-info.h
        src/compact-lexicon-tree.cpp
        src/compact-lexicon-tree.h
        src/compact-lexicon.cpp
        src/compact-lexicon.h
        src/elvex.cpp
        src/entries.cpp
        src/entries.h
        src/entry.cpp
        src/entry.h
        src/environment.cpp
        src/environment.h
        src/feature.cpp
        src/feature.h
        src/features.cpp
        src/features.h
        src/flags.cpp
        src/flags.h
        src/forest.cpp
        src/forest.h
        src/forestidentifier.cpp
        src/forestidentifier.h
        src/forestmap.cpp
        src/forestmap.h
        src/grammar.cpp
        src/grammar.h
        src/id.cpp
        src/id.h
        src/item.cpp
        src/item.h
        src/itemset.cpp
        src/itemset.h
        src/lexicon.cpp
        src/lexicon.h
        src/list.cpp
        src/list.h
        src/listfeatures.cpp
        src/listfeatures.h
        src/memoization-map.cpp
        src/memoization-map.h
        src/memoization-value.cpp
        src/memoization-value.h
        src/messages.h
        src/node.cpp
        src/node.h
        src/parser.cpp
        src/parser.h
        src/rule.cpp
        src/rule.h
        src/serializable.cpp
        src/serializable.h
        src/shared_ptr.h
        src/statement.cpp
        src/statement.h
        src/statements.cpp
        src/statements.h
        src/synthesizer.cpp
        src/synthesizer.h
        src/term.cpp
        src/term.h
        src/terms.cpp
        src/terms.h
        src/value.cpp
        src/value.h
        src/variableflag.cpp
        src/variableflag.h
        src/vartable.cpp
        src/vartable.h)

configure_file(
        src/config.h.in
        src/config.h
        @ONLY)

add_executable(elvex ${ELVEX_SOURCES})
target_compile_options(elvex PUBLIC -std=c++11 -O3 -Wall -Wextra -Wno-deprecated -Wno-sign-compare -Wno-missing-field-initializers)
find_package(LibXml2 REQUIRED)
if (LibXml2_FOUND)
    target_compile_definitions(elvex PUBLIC OUTPUT_XML)
    target_link_libraries(elvex PUBLIC ${LIBXML2_LIBRARIES})
    target_include_directories(elvex PUBLIC ${LIBXML2_INCLUDE_DIR})
else()
    message("libxml2 not found")
endif()

add_executable(elvexdebug ${ELVEX_SOURCES})
target_compile_options(elvexdebug PUBLIC -std=c++11 -O3 -Wall -Wextra -Wno-deprecated -Wno-sign-compare  -Wno-missing-field-initializers)
if (LibXml2_FOUND)
    target_compile_definitions(elvexdebug PUBLIC OUTPUT_XML TRACE_OPTION)
    target_link_libraries(elvexdebug PUBLIC ${LIBXML2_LIBRARIES})
    target_include_directories(elvexdebug PUBLIC ${LIBXML2_INCLUDE_DIR})
else()
    message("libxml2 not found")
endif()

add_executable(elvexbuildLexicon ${ELVEX_SOURCES})
target_compile_options(elvexbuildLexicon PUBLIC -std=c++11 -O3 -Wall -Wextra -Wno-deprecated -Wno-sign-compare  -Wno-missing-field-initializers)

FLEX_TARGET(postedition src/postedition_en.l ${CMAKE_CURRENT_BINARY_DIR}/src/postedition.cpp)
add_executable(elvexpostedition ${FLEX_postedition_OUTPUTS})
target_compile_options(elvexpostedition PUBLIC -std=c++11 -O3 -Wall -Wextra -Wno-deprecated -Wno-sign-compare  -Wno-missing-field-initializers)

