cmake_minimum_required(VERSION 3.0)

if(NOT EXISTS ${SYSROOT})
    set(EXT_M4 ext_m4)
    
    if(MINGW OR MSYS)
        message(WARNING "Use cygwin's m4")
    elseif(APPLE)
        ExternalProject_Add(
            ${EXT_M4}
            URL                 http://ftp.gnu.org/gnu/m4/m4-1.4.17.tar.gz
            CONFIGURE_COMMAND   ${CMAKE_BINARY_DIR}/3rdparty/m4/${EXT_M4}-prefix/src/${EXT_M4}/configure --prefix=${3RDPARTY_INSTALL}
            BUILD_COMMAND       make
            INSTALL_COMMAND     make install
        )
    elseif(EMSCRIPTEN)
    elseif(ANDROID)
    else()
        ExternalProject_Add(
            ${EXT_M4}
            URL                 http://ftp.gnu.org/gnu/m4/m4-1.4.17.tar.gz
            CONFIGURE_COMMAND   ${CMAKE_BINARY_DIR}/3rdparty/m4/${EXT_M4}-prefix/src/${EXT_M4}/configure --prefix=${3RDPARTY_INSTALL}
            BUILD_COMMAND       make
            INSTALL_COMMAND     make install
        )
    endif()
endif()

set(M4_LOCATION "${3RDPARTY_INSTALL}/bin/m4" CACHE STRING "" FORCE)
