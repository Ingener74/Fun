cmake_minimum_required(VERSION 3.0)

if(NOT EXISTS ${SYSROOT})
    set(EXT_POCO ext_POCO)
    
    if(MINGW OR MSYS)
        ExternalProject_Add(
            ${EXT_POCO}
            URL                 http://pocoproject.org/releases/poco-1.7.4/poco-1.7.4-all.zip
            PATCH_COMMAND       ${PATCH_EXECUTABLE} -p1 < ${CMAKE_CURRENT_LIST_DIR}/mingw.patch
            CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                                -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                                -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
                                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                                -DENABLE_DATA_ODBC=OFF
                                -DENABLE_DATA_MYSQL=OFF
                                -DENABLE_DATA_SQLITE=OFF
                                -DENABLE_APACHECONNECTOR=OFF
                                -DENABLE_POCODOC=OFF
                                -DENABLE_PDF=OFF
                                -DENABLE_PAGECOMPILER=OFF
                                -DENABLE_PAGECOMPILER_FILE2PAGE=OFF
                                -DENABLE_ZIP=OFF
                                -DENABLE_XML=OFF
                                -DENABLE_JSON=OFF
                                -DENABLE_MONGODB=OFF
                                -DENABLE_TESTS=OFF
                                -DPOCO_STATIC=OFF
                                -DFORCE_OPENSSL=OFF
                                # -DOPENSSL_INCLUDE_DIR=${3RDPARTY_INSTALL}/include
                                # -DOPENSSL_CRYPTO_LIBRARY=${3RDPARTY_INSTALL}/lib/libcrypto.a
                                # -DOPENSSL_SSL_LIBRARY=${3RDPARTY_INSTALL}/lib/libssl.a
        )
    elseif(MSVC)
        ExternalProject_Add(
            ${EXT_POCO}
            URL                 http://pocoproject.org/releases/poco-1.7.4/poco-1.7.4-all.zip
            CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                                -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
                                -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
                                -DENABLE_DATA_ODBC=OFF
                                -DENABLE_DATA_MYSQL=OFF
                                -DENABLE_DATA_SQLITE=OFF
                                -DENABLE_APACHECONNECTOR=OFF
                                -DENABLE_POCODOC=OFF
                                -DENABLE_PDF=OFF
                                -DENABLE_PAGECOMPILER=OFF
                                -DENABLE_PAGECOMPILER_FILE2PAGE=OFF
                                -DENABLE_ZIP=OFF
                                -DENABLE_XML=OFF
                                -DENABLE_JSON=OFF
                                -DENABLE_MONGODB=OFF
                                -DENABLE_TESTS=OFF
                                -DPOCO_STATIC=OFF
                                -DFORCE_OPENSSL=OFF
        )
    elseif(APPLE)
        ExternalProject_Add(
            ${EXT_POCO}
            URL                 http://pocoproject.org/releases/poco-1.7.4/poco-1.7.4-all.zip
            CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                                -DENABLE_DATA_ODBC=OFF
                                -DENABLE_DATA_MYSQL=OFF
                                -DENABLE_DATA_SQLITE=OFF
                                -DENABLE_APACHECONNECTOR=OFF
                                -DENABLE_POCODOC=OFF
                                -DENABLE_PDF=OFF
                                -DENABLE_PAGECOMPILER=OFF
                                -DENABLE_PAGECOMPILER_FILE2PAGE=OFF
                                -DENABLE_ZIP=OFF
                                -DENABLE_XML=OFF
                                -DENABLE_JSON=OFF
                                -DENABLE_MONGODB=OFF
                                -DENABLE_TESTS=OFF
                                -DPOCO_STATIC=OFF
                                -DFORCE_OPENSSL=OFF
                                # -DOPENSSL_INCLUDE_DIR=${3RDPARTY_INSTALL}/include
                                # -DOPENSSL_CRYPTO_LIBRARY=${3RDPARTY_INSTALL}/lib/libcrypto.a
                                # -DOPENSSL_SSL_LIBRARY=${3RDPARTY_INSTALL}/lib/libssl.a
        )
    
    elseif(EMSCRIPTEN)
        ExternalProject_Add(
            ${EXT_POCO}
            URL                 http://pocoproject.org/releases/poco-1.7.4/poco-1.7.4-all.zip
            CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                                -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                                -DENABLE_DATA_ODBC=OFF
                                -DENABLE_DATA_MYSQL=OFF
                                -DENABLE_APACHECONNECTOR=OFF
                                -DENABLE_POCODOC=OFF
                                -DENABLE_PDF=OFF
                                -DENABLE_PAGECOMPILER=OFF
                                -DENABLE_PAGECOMPILER_FILE2PAGE=OFF
                                -DENABLE_ZIP=OFF
                                -DENABLE_XML=OFF
                                -DENABLE_MONGODB=OFF
                                -DENABLE_TESTS=OFF
                                -DPOCO_STATIC=ON
                                -DOPENSSL_INCLUDE_DIR=${3RDPARTY_INSTALL}/include
                                -DOPENSSL_CRYPTO_LIBRARY=${3RDPARTY_INSTALL}/lib/libcrypto.a
                                -DOPENSSL_SSL_LIBRARY=${3RDPARTY_INSTALL}/lib/libssl.a
                                -DANDROID_ABI=${ANDROID_ABI}
                                -DANDROID_NATIVE_API_LEVEL=${ANDROID_NATIVE_API_LEVEL}
        )
    
    elseif(ANDROID)
        ExternalProject_Add(
            ${EXT_POCO}
            URL                 http://pocoproject.org/releases/poco-1.6.1/poco-1.6.1-all.tar.gz
            CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                                -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                                -DENABLE_DATA_ODBC=OFF
                                -DENABLE_DATA_MYSQL=OFF
                                -DENABLE_APACHECONNECTOR=OFF
                                -DENABLE_POCODOC=OFF
                                -DENABLE_PDF=OFF
                                -DENABLE_PAGECOMPILER=OFF
                                -DENABLE_PAGECOMPILER_FILE2PAGE=OFF
                                -DENABLE_ZIP=OFF
                                -DENABLE_XML=OFF
                                -DENABLE_MONGODB=OFF
                                -DENABLE_TESTS=OFF
                                -DPOCO_STATIC=ON
                                # -DOPENSSL_INCLUDE_DIR=${3RDPARTY_INSTALL}/include
                                # -DOPENSSL_CRYPTO_LIBRARY=${3RDPARTY_INSTALL}/lib/libcrypto.a
                                # -DOPENSSL_SSL_LIBRARY=${3RDPARTY_INSTALL}/lib/libssl.a
                                -DANDROID_ABI=${ANDROID_ABI}
                                -DANDROID_NATIVE_API_LEVEL=${ANDROID_NATIVE_API_LEVEL}
        )
    
    else()
        ExternalProject_Add(
            ${EXT_POCO}
            URL                 http://pocoproject.org/releases/poco-1.7.4/poco-1.7.4-all.zip
            CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                                -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
                                -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
                                -DENABLE_DATA_ODBC=OFF
                                -DENABLE_DATA_MYSQL=OFF
                                -DENABLE_DATA_SQLITE=OFF
                                -DENABLE_APACHECONNECTOR=OFF
                                -DENABLE_POCODOC=OFF
                                -DENABLE_PDF=OFF
                                -DENABLE_PAGECOMPILER=OFF
                                -DENABLE_PAGECOMPILER_FILE2PAGE=OFF
                                -DENABLE_ZIP=OFF
                                -DENABLE_XML=OFF
                                -DENABLE_JSON=OFF
                                -DENABLE_MONGODB=OFF
                                -DENABLE_TESTS=OFF
                                -DPOCO_STATIC=OFF
                                -DFORCE_OPENSSL=OFF
        )
    endif()
endif()

if(MSVC)
    set(POCO_LIBRARIES PocoFoundationd PocoUtild CACHE STRING "" FORCE)
elseif(MINGW OR MSYS)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(POCO_LIBRARIES PocoFoundationd.dll PocoUtild.dll CACHE STRING "" FORCE)
    else()
        set(POCO_LIBRARIES PocoFoundation.dll PocoUtil.dll CACHE STRING "" FORCE)
    endif()
else()
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(POCO_LIBRARIES PocoFoundationd PocoUtild CACHE STRING "" FORCE)
    else()
        set(POCO_LIBRARIES PocoFoundation PocoUtil CACHE STRING "" FORCE)
    endif()
endif()

message(STATUS "Poco libraries ${POCO_LIBRARIES}")




