cmake_minimum_required(VERSION 3.8)
project(cpp-not-so-simple-calculator-std-children-of-the-calc)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Calculator.cpp ExprElem.cpp Operators.cpp Tester.hpp CalculatorException.cpp CalculatorException.h)
add_executable(cpp-not-so-simple-calculator-std-children-of-the-calc ${SOURCE_FILES})