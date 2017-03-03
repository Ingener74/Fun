cmake_minimum_required(VERSION 3.0)

if(NOT EXISTS ${SYSROOT})
    set(EXT_FLEX ext_flex)
    
    configure_file(build_ext_flex.sh.in ${CMAKE_BINARY_DIR}/build_ext_flex.sh)

    if(MINGW OR MSYS)
        message(WARNING "Use cygwin's flex")
    elseif(APPLE)
        ExternalProject_Add(
            ${EXT_FLEX}
            URL                 https://github.com/westes/flex/archive/v2.6.3.zip
            CONFIGURE_COMMAND   ""
            BUILD_COMMAND       ${CMAKE_BINARY_DIR}/build_ext_flex.sh
            INSTALL_COMMAND     ""
        )
    elseif(EMSCRIPTEN)
    elseif(ANDROID)
    else()
        ExternalProject_Add(
            ${EXT_FLEX}
            URL                 https://github.com/westes/flex/archive/v2.6.3.zip
            CONFIGURE_COMMAND   ""
            BUILD_COMMAND       ${CMAKE_BINARY_DIR}/build_ext_flex.sh
            INSTALL_COMMAND     ""
        )
    endif()
endif()

set(FLEX_EXECUTABLE "${3RDPARTY_INSTALL}/bin/flex" CACHE STRING "" FORCE)
message(STATUS "Flex executable ${FLEX_EXECUTABLE}")

