cmake_minimum_required(VERSION 3.0)

if(NOT EXISTS ${SYSROOT})
    set(EXT_FLEX ext_flex)
    
    if(MINGW OR MSYS)
        ExternalProject_Add(
            ${EXT_FLEX}
            URL                 http://pocoproject.org/releases/poco-1.7.4/poco-1.7.4-all.zip
            PATCH_COMMAND       patch -p1 < ${CMAKE_CURRENT_LIST_DIR}/mingw.patch
            CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                                -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                                -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
                                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        )
    elseif(APPLE)
        ExternalProject_Add(
            ${EXT_FLEX}
            URL                 http://downloads.sourceforge.net/project/flex/flex-2.6.0.tar.gz
            CONFIGURE_COMMAND   YACC=${3RDPARTY_INSTALL}/bin/yacc M4=${M4_LOCATION} ${CMAKE_BINARY_DIR}/3rdparty/flex/${EXT_FLEX}-prefix/src/${EXT_FLEX}/configure --prefix=${3RDPARTY_INSTALL}
            BUILD_COMMAND       make
            INSTALL_COMMAND     make install
        )
    elseif(EMSCRIPTEN)
    elseif(ANDROID)
    else()
        ExternalProject_Add(
            ${EXT_FLEX}
            URL                 http://downloads.sourceforge.net/project/flex/flex-2.6.0.tar.gz
            CONFIGURE_COMMAND   YACC=${3RDPARTY_INSTALL}/bin/yacc M4=${M4_LOCATION} ${CMAKE_BINARY_DIR}/3rdparty/flex/${EXT_FLEX}-prefix/src/${EXT_FLEX}/configure --prefix=${3RDPARTY_INSTALL}
            BUILD_COMMAND       make
            INSTALL_COMMAND     make install
        )
    endif()
endif()

set(FLEX_EXECUTABLE "${3RDPARTY_INSTALL}/bin/flex" CACHE STRING "" FORCE)
message(STATUS "Flex executable ${FLEX_EXECUTABLE}")

