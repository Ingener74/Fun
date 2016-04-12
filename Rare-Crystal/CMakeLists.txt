cmake_minimum_required(VERSION 3.0)

add_subdirectory(../Deserted-Xylophone)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(
        BisonParser
        src/Parser.y
        ${CMAKE_CURRENT_BINARY_DIR}/BisonParser.cpp
        # DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/src/BisonParser.h
)

FLEX_TARGET(
        FlexLexer
        src/Lexer.l
        ${CMAKE_CURRENT_BINARY_DIR}/FlexLexer.cpp)

ADD_FLEX_BISON_DEPENDENCY(FlexLexer BisonParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(PARSING_SOURCES
        src/Lexer.cpp
        src/Parser.cpp)

add_library(parsing
        ${PARSING_SOURCES}
        ${BISON_BisonParser_OUTPUTS}
        ${FLEX_FlexLexer_OUTPUTS})

set(TidyBoomerang_SOURCES
        src/main.cpp)

add_executable(TidyBoomerang ${TidyBoomerang_SOURCES})
target_link_libraries(TidyBoomerang parsing)