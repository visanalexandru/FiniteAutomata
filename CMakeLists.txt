cmake_minimum_required(VERSION 3.21)
project(finite_automata)

set(CMAKE_CXX_STANDARD 14)

add_executable(finite_automata DFA.h NFA.h tests.cpp L_NFA.h)
target_compile_options(finite_automata PRIVATE -Wall)
