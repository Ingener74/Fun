cmake_minimum_required(VERSION 2.8.11)

set(EXT_GMOCK ext_gtest)

if(MINGW OR MSYS)
    # ExternalProject_Add(
    #     ${EXT_GMOCK}
    #     URL                 https://github.com/google/googletest/archive/master.zip
    #     CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
    #                         -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    #                         -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    #                         -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
    # )
elseif(EMSCRIPTEN)
elseif(ANDROID)
elseif(APPLE)
    ExternalProject_Add(
        ${EXT_GMOCK}
        URL                 https://github.com/google/googletest/archive/master.zip
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} 
    )
else()
    ExternalProject_Add(
        ${EXT_GMOCK}
        URL                 https://github.com/google/googletest/archive/master.zip
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    )
endif()

