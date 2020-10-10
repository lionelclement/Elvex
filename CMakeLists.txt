cmake_minimum_required(VERSION 3.17)
project(Elvex)

set(CMAKE_CXX_STANDARD 11)
add_compile_options("-std=c++11;-Wall;-Wextra;-Wno-error=deprecated-declarations;-Wno-error=deprecated-register")

include_directories(src)

find_package(BISON)
BISON_TARGET(rulesyacc src/rulesyacc.y ${CMAKE_CURRENT_BINARY_DIR}/rulesyacc.cpp
        DEFINES_FILE rulesyacc.h
        COMPILE_FLAGS "-p rules" )

find_package(FLEX)
FLEX_TARGET(ruleslex src/ruleslex.l ${CMAKE_CURRENT_BINARY_DIR}/ruleslex.cpp
        COMPILE_FLAGS "-Prules")

ADD_FLEX_BISON_DEPENDENCY(ruleslex rulesyacc)

add_executable(elvex
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

add_executable(buildLexicon
        ${BISON_rulesyacc_OUTPUTS}
        ${FLEX_ruleslex_OUTPUTS}
        src/bitset.cpp
        src/bitset.h
        src/buildlexicon.cpp
        src/buildlexicon.h
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

FLEX_TARGET(postedition src/postedition_en.l ${CMAKE_CURRENT_BINARY_DIR}/postedition.cpp)

add_executable(postedition
        ${FLEX_postedition_OUTPUTS}
)

