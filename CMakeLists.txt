cmake_minimum_required(VERSION 3.5)
project(naivebayes)

set(CMAKE_CXX_STANDARD 14)

add_executable(naivebayes src/main.cpp src/Number.cpp src/Number.h test/TestingData.cpp test/TestingData.h src/Training.cpp src/Training.h src/Model.cpp src/Model.h)
add_executable(unit-tests catch.hpp test/Test.cpp src/Number.h src/Number.cpp test/TestingData.h test/TestingData.cpp src/Training.h src/Training.cpp)

set_target_properties(unit-tests PROPERTIES LINKER_LANGUAGE CXX)


