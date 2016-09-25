cmake_minimum_required(VERSION 3.0)

if(NOT EXISTS ${SYSROOT})
    set(EXT_BISON ext_bison)
    
    if(MINGW OR MSYS)
        ExternalProject_Add(
            ${EXT_BISON}
            URL                 http://pocoproject.org/releases/poco-1.7.4/poco-1.7.4-all.zip
            PATCH_COMMAND       patch -p1 < ${CMAKE_CURRENT_LIST_DIR}/mingw.patch
            CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                                -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                                -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
                                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        )
    elseif(APPLE)
        ExternalProject_Add(
            ${EXT_BISON}
            URL                 http://ftp.gnu.org/gnu/bison/bison-3.0.4.tar.gz
            CONFIGURE_COMMAND   M4=${M4_LOCATION} ${CMAKE_BINARY_DIR}/3rdparty/bison/${EXT_BISON}-prefix/src/${EXT_BISON}/configure --prefix=${3RDPARTY_INSTALL}
            BUILD_COMMAND       make
            INSTALL_COMMAND     make install
        )
    elseif(EMSCRIPTEN)
    elseif(ANDROID)
    else()
        ExternalProject_Add(
            ${EXT_BISON}
            URL                 http://ftp.gnu.org/gnu/bison/bison-3.0.4.tar.gz
            CONFIGURE_COMMAND   M4=${M4_LOCATION} ${CMAKE_BINARY_DIR}/3rdparty/bison/${EXT_BISON}-prefix/src/${EXT_BISON}/configure --prefix=${3RDPARTY_INSTALL}
            BUILD_COMMAND       make
            INSTALL_COMMAND     make install
        )
    endif()
endif()

set(BISON_EXECUTABLE "${3RDPARTY_INSTALL}/bin/bison" CACHE STRING "" FORCE)
message(STATUS "Bison executable ${BISON_EXECUTABLE}")




