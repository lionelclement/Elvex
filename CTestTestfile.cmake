# CMake generated Testfile for 
# Source directory: /Users/clement/Elvex
# Build directory: /Users/clement/Elvex
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(elvex_regression "/bin/bash" "/Users/clement/Elvex/test/run-regression.sh" "/Users/clement/Elvex/bin/elvex")
set_tests_properties(elvex_regression PROPERTIES  WORKING_DIRECTORY "/Users/clement/Elvex" _BACKTRACE_TRIPLES "/Users/clement/Elvex/CMakeLists.txt;196;add_test;/Users/clement/Elvex/CMakeLists.txt;0;")
