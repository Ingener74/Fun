cmake_minimum_required(VERSION 3.0)

if(NOT EXISTS ${SYSROOT})
    set(EXT_BISON ext_bison)
    
    configure_file(build_ext_bison.sh.in ${CMAKE_BINARY_DIR}/build_ext_bison.sh)
    
    if(MINGW OR MSYS)
        message(WARNING "Use cygwin's bison")
    elseif(APPLE)
        ExternalProject_Add(
            ${EXT_BISON}
            URL                 http://ftp.gnu.org/gnu/bison/bison-3.0.4.tar.gz
            CONFIGURE_COMMAND   ""
            BUILD_COMMAND       ${CMAKE_BINARY_DIR}/build_ext_bison.sh
            INSTALL_COMMAND     ""
        )
    elseif(EMSCRIPTEN)
    elseif(ANDROID)
    else()
        ExternalProject_Add(
            ${EXT_BISON}
            URL                 http://ftp.gnu.org/gnu/bison/bison-3.0.4.tar.gz
            CONFIGURE_COMMAND   ""
            BUILD_COMMAND       ${CMAKE_BINARY_DIR}/build_ext_bison.sh
            INSTALL_COMMAND     ""
        )
    endif()
endif()

set(BISON_EXECUTABLE "${3RDPARTY_INSTALL}/bin/bison" CACHE STRING "" FORCE)
message(STATUS "Bison executable ${BISON_EXECUTABLE}")




