if(EXISTS "/home/davidsim/Documents/Programming/IntegratedCompiler/build/lexer/test_dfa[1]_tests.cmake")
  include("/home/davidsim/Documents/Programming/IntegratedCompiler/build/lexer/test_dfa[1]_tests.cmake")
else()
  add_test(test_dfa_NOT_BUILT test_dfa_NOT_BUILT)
endif()
