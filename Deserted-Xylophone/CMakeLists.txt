cmake_minimum_required(VERSION 3.0)

find_package(LLVM REQUIRED)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_definitions(-std=c++11)

add_executable(Deserted-Xylophone main.cpp)

llvm_map_components_to_libnames(LLVM_LIBS support core irreader)

target_link_libraries(Deserted-Xylophone ${LLVM_LIBS})