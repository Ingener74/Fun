cmake_minimum_required(VERSION 3.0)


include_directories(
    Fun
    ${CMAKE_BINARY_DIR}/Fun
)

if(MSVC)
	add_definitions(/DYY_NO_UNISTD_H)
else()
    add_definitions(-std=c++11)
endif()


option(ENABLE_DESERTED_XYLOPHONE "Enable Deserted-Xylophone" ON)
if(ENABLE_DESERTED_XYLOPHONE)
    add_subdirectory(Deserted-Xylophone)
endif()


option(ENABLE_TAINTED_BULLDOZER "Enable Tainted-Bulldozer" ON)
if(ENABLE_TAINTED_BULLDOZER)
    add_subdirectory(Tainted-Bulldozer)
endif()


option(ENABLE_FUN "Enable Fun" ON)
if(ENABLE_FUN)
    add_subdirectory(Fun)
endif()


option(ENABLE_DANCING_COMIC "Enable Dancing-Comic" OFF)
if(ENABLE_DANCING_COMIC)
    add_subdirectory(Dancing-Comic)
endif()


option(ENABLE_LIQUID_METAPHOR "Enable Liquid-Metaphor" ON)
if(ENABLE_LIQUID_METAPHOR)
    add_subdirectory(Liquid-Metaphor)
endif()



