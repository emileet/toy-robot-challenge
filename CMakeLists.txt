cmake_minimum_required(VERSION 3.12)

# set the project name
project(ToyRobot)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(ToyRobot ./src/main.cpp)

# unit tests with GoogleTest
find_package(GTest CONFIG REQUIRED)
add_executable(TestToyRobot ./tests/tests.cpp)
target_link_libraries(TestToyRobot gtest)
add_test(NAME Tests COMMAND TestToyRobot)
