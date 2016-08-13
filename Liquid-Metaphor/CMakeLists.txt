cmake_minimum_required(VERSION 3.0)

project(Liquid-Metaphor)

add_executable(Liquid-Metaphor main.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(Liquid-Metaphor Fun PocoFoundationd)
else()
    target_link_libraries(Liquid-Metaphor Fun PocoFoundation)
endif()
