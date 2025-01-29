# CMake generated Testfile for 
# Source directory: /Users/hiyu/Tools/pbrt
# Build directory: /Users/hiyu/Tools/pbrt/build_tsvLight02
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(pbrt_unit_test "pbrt_test")
set_tests_properties(pbrt_unit_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/hiyu/Tools/pbrt/CMakeLists.txt;1095;add_test;/Users/hiyu/Tools/pbrt/CMakeLists.txt;0;")
subdirs("src/ext")
