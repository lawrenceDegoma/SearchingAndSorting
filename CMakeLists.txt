cmake_minimum_required(VERSION 3.26)
project(SortingAndSearching)

set(CMAKE_CXX_STANDARD 17)

add_executable(SortingAndSearching main.cpp)
target_link_libraries(SortingAndSearching sfml-graphics sfml-audio)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)