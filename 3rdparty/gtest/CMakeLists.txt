cmake_minimum_required(VERSION 2.8.11)

macro(make_windows_path pathname variable)
  string(REPLACE "/" "\\" ${variable} "${pathname}")
endmacro(make_windows_path)

if(NOT EXISTS ${SYSROOT})
    set(EXT_GMOCK ext_gmock)
    set(EXT_GTEST ext_gtest)

    if(MINGW OR MSYS)

        make_windows_path(${3RDPARTY_INSTALL} 3RDPARTY_INSTALL_WIN32)
        make_windows_path(${CMAKE_BINARY_DIR} CMAKE_BINARY_DIR_WIN32)

        configure_file(install_gtest.bat.in ${CMAKE_BINARY_DIR}/install_gtest.bat)
        configure_file(install_gmock.bat.in ${CMAKE_BINARY_DIR}/install_gmock.bat)

        ExternalProject_Add(
                ${EXT_GTEST}
                URL                 https://github.com/google/googletest/archive/release-1.7.0.zip
                CMAKE_ARGS          -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                INSTALL_COMMAND     ${CMAKE_BINARY_DIR}/install_gtest.bat
        )
        ExternalProject_Add(
                ${EXT_GMOCK}
                URL                 https://github.com/google/googlemock/archive/release-1.7.0.zip
                PATCH_COMMAND       ${PATCH_EXECUTABLE} -p1 < ${CMAKE_CURRENT_LIST_DIR}/gmock-mingw.patch
                CMAKE_ARGS          -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                    -DGTEST_DIR=${CMAKE_BINARY_DIR}/3rdparty/gtest/${EXT_GTEST}-prefix/src/${EXT_GTEST}
                INSTALL_COMMAND     ${CMAKE_BINARY_DIR}/install_gmock.bat
        )
    elseif(MSVC)
        ExternalProject_Add(
            ${EXT_GTEST}
            URL                 https://github.com/google/googletest/archive/master.zip
            CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
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

