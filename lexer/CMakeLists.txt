cmake_minimum_required(VERSION 3.10)
project(Lexer VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/dfa.cpp
    src/nfa.cpp
    src/re.cpp
)

add_library(lexer_lib ${SOURCES})
target_include_directories(lexer_lib PUBLIC include)

add_executable(test_dfa test/test_dfa.cpp)
target_link_libraries(test_dfa PUBLIC lexer_lib gtest gtest_main)
target_include_directories(test_dfa PUBLIC include)

add_executable(test_nfa test/test_nfa.cpp)
target_link_libraries(test_nfa PUBLIC lexer_lib gtest gtest_main)
target_include_directories(test_nfa PUBLIC include)

add_executable(test_re test/test_re.cpp)
target_link_libraries(test_re PUBLIC lexer_lib gtest gtest_main)
target_include_directories(test_re PUBLIC include)

add_executable(nfa_dfa_speed_test test/nfa_dfa_speed_test.cpp)
target_link_libraries(nfa_dfa_speed_test PUBLIC lexer_lib)
target_include_directories(nfa_dfa_speed_test PUBLIC include)