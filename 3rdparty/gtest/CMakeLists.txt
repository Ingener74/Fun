cmake_minimum_required(VERSION 2.8.11)

if(NOT EXISTS ${SYSROOT})
    set(EXT_GMOCK ext_gmock)
    set(EXT_GTEST ext_gtest)

    if(MINGW OR MSYS)
        ExternalProject_Add(
                ${EXT_GTEST}
                URL                 https://github.com/google/googletest/archive/release-1.7.0.zip
                CMAKE_ARGS          -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                INSTALL_COMMAND     mkdir -p ${3RDPARTY_INSTALL}/include
                    && mkdir -p ${3RDPARTY_INSTALL}/lib
                    && cp -R ${CMAKE_BINARY_DIR}/3rdparty/gtest/${EXT_GTEST}-prefix/src/${EXT_GTEST}/include ${3RDPARTY_INSTALL}
                    && cp -R ${CMAKE_BINARY_DIR}/3rdparty/gtest/${EXT_GTEST}-prefix/src/${EXT_GTEST}-build/libgtest.a ${3RDPARTY_INSTALL}/lib
                    && cp -R ${CMAKE_BINARY_DIR}/3rdparty/gtest/${EXT_GTEST}-prefix/src/${EXT_GTEST}-build/libgtest_main.a ${3RDPARTY_INSTALL}/lib
        )
        ExternalProject_Add(
                ${EXT_GMOCK}
                URL                 https://github.com/google/googlemock/archive/release-1.7.0.zip
                PATCH_COMMAND       patch -p1 < ${CMAKE_CURRENT_LIST_DIR}/gmock-mingw.patch
                CMAKE_ARGS          -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                    -DGTEST_DIR=${CMAKE_BINARY_DIR}/3rdparty/gtest/${EXT_GTEST}-prefix/src/${EXT_GTEST}
                INSTALL_COMMAND     mkdir -p ${3RDPARTY_INSTALL}/include
                    && mkdir -p ${3RDPARTY_INSTALL}/lib
                    && cp -R ${CMAKE_BINARY_DIR}/3rdparty/gtest/${EXT_GMOCK}-prefix/src/${EXT_GMOCK}/include ${3RDPARTY_INSTALL}
                    && cp -R ${CMAKE_BINARY_DIR}/3rdparty/gtest/${EXT_GMOCK}-prefix/src/${EXT_GMOCK}-build/libgmock.a ${3RDPARTY_INSTALL}/lib
                    && cp -R ${CMAKE_BINARY_DIR}/3rdparty/gtest/${EXT_GMOCK}-prefix/src/${EXT_GMOCK}-build/libgmock_main.a ${3RDPARTY_INSTALL}/lib
        )
    elseif(EMSCRIPTEN)
    elseif(ANDROID)
    elseif(APPLE)
        ExternalProject_Add(
            ${EXT_GTEST}
            URL                 https://github.com/google/googletest/archive/master.zip
            CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} 
        )
    else()
        ExternalProject_Add(
            ${EXT_GTEST}
            URL                 https://github.com/google/googletest/archive/master.zip
            CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        )
    endif()
endif()

set(GTEST_LIBRARIES gmock gtest gmock_main gtest_main CACHE STRING "" FORCE)

message(STATUS "gtest libraries ${GTEST_LIBRARIES}")

