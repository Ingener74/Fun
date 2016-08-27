cmake_minimum_required(VERSION 3.0)


if(MSVC)
	add_definitions(/DYY_NO_UNISTD_H)
else()
    add_definitions(-std=c++11)
endif()

unset(BUILD_PLATFORM)
if(MINGW OR MSYS)
    message(STATUS "MinGW or MSYS build")
    set(BUILD_PLATFORM msys_mingw)
elseif(EMSCRIPTEN)
    message(STATUS "Emscripten build")
    set(BUILD_PLATFORM emscripten)
elseif(ANDROID)
    message(STATUS "Android build")
    set(BUILD_PLATFORM android)
elseif(APPLE)
    message(STATUS "MacOS build")
    set(BUILD_PLATFORM macos)
else()
    message(STATUS "Linux build")
    set(BUILD_PLATFORM linux)
endif()

set(SYSROOT ${CMAKE_SOURCE_DIR}/3rdparty/sysroot-${BUILD_PLATFORM})

set(3RDPARTY_INSTALL ${SYSROOT})

add_subdirectory(3rdparty)

enable_testing()

include_directories(
    fun
    ${CMAKE_BINARY_DIR}/fun
    cxxopts/src
    ${SYSROOT}/include
)
link_directories(
        ${SYSROOT}/lib
)

option(ENABLE_DESERTED_XYLOPHONE "Enable Deserted-Xylophone" OFF)
if(ENABLE_DESERTED_XYLOPHONE)
    add_subdirectory(Deserted-Xylophone)
endif()


option(ENABLE_TAINTED_BULLDOZER "Enable Tainted-Bulldozer" OFF)
if(ENABLE_TAINTED_BULLDOZER)
    add_subdirectory(Tainted-Bulldozer)
endif()


option(ENABLE_FUN "Enable Fun" ON)
if(ENABLE_FUN)
    add_subdirectory(fun)
endif()


option(ENABLE_DANCING_COMIC "Enable Dancing-Comic" OFF)
if(ENABLE_DANCING_COMIC)
    add_subdirectory(Dancing-Comic)
endif()
