cmake_minimum_required(VERSION 3.0)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(
        MyParser
        MyParser.y
        ${CMAKE_CURRENT_BINARY_DIR}/MyParser.cpp
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

FLEX_TARGET(
        MyLexer
        MyLexer.l
        ${CMAKE_CURRENT_BINARY_DIR}/MyLexer.cpp)

ADD_FLEX_BISON_DEPENDENCY(MyLexer MyParser)

add_executable(
        Raw-RailroadParser
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyLexer_OUTPUTS}
)

#
#
#
#set(PARSING_SOURCES
#        src/Lexer.cpp
#        src/Parser.cpp)
#
#if(MSVC)
#else()
#    add_definitions(-std=c++11)
#endif()
#
#add_library(parsing
#        ${PARSING_SOURCES}
#        ${BISON_BisonParser_OUTPUTS}
#        ${FLEX_FlexLexer_OUTPUTS})
#
#set(Rare-Crystal_SOURCES
#        src/main.cpp)
#
#add_executable(Rare-Crystal ${Rare-Crystal_SOURCES})
#target_link_libraries(Rare-Crystal parsing)