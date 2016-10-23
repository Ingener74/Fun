cmake_minimum_required(VERSION 3.0)

# include modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

unset(BUILD_PLATFORM)
if(MINGW OR MSYS)
    message(STATUS "MinGW or MSYS build")
    set(BUILD_PLATFORM msys_mingw)
    add_definitions(-std=gnu++0x)
    include(FindPatch)
elseif(MSVC)
    message(STATUS "Microsoft Visual Studio 2013 build")
    set(BUILD_PLATFORM msvc)
    add_definitions(/DYY_NO_UNISTD_H)
elseif(EMSCRIPTEN)
    message(STATUS "Emscripten build")
    set(BUILD_PLATFORM emscripten)
elseif(ANDROID)
    message(STATUS "Android build")
    set(BUILD_PLATFORM android)
elseif(APPLE)
    message(STATUS "MacOS build")
    set(BUILD_PLATFORM macos)
    add_definitions(-std=c++11)
else()
    message(STATUS "Linux build")
    set(BUILD_PLATFORM linux)
    add_definitions(-std=c++11)
endif()

set(SYSROOT ${CMAKE_SOURCE_DIR}/3rdparty/sysroot-${BUILD_PLATFORM})

set(3RDPARTY_INSTALL ${SYSROOT})

option(ENABLE_ASAN "Enable AddressSanitizer" OFF)
if(ENABLE_ASAN)
    # sudo sysctl vm.overcommit_memory=1
    # export ASAN_OPTIONS=abort_on_error=1
    # cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-fsanitize=address -fno-omit-frame-pointer" -DCMAKE_C_FLAGS="-fsanitize=address -fno-omit-frame-pointer"
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_DEBUG -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif()

add_subdirectory(3rdparty)

enable_testing()

include_directories(
    fun
    ${CMAKE_BINARY_DIR}/fun
    ${SYSROOT}/include
)
link_directories(
    ${SYSROOT}/lib
)


if(EXISTS ${SYSROOT})
    option(ENABLE_FUN "Enable Fun" ON)
    if(ENABLE_FUN)
        add_subdirectory(fun)
    endif()
    
    
    option(ENABLE_DANCING_COMIC "Enable Dancing-Comic" OFF)
    if(ENABLE_DANCING_COMIC)
        add_subdirectory(Dancing-Comic)
    endif()
endif()

