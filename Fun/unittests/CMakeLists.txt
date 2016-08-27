cmake_minimum_required(VERSION 3.0)

if(MINGW OR MSYS)
elseif(EMSCRIPTEN)
elseif(ANDROID)
elseif(APPLE)
else()
    add_executable(fun_unittests test1.cpp)
    target_link_libraries(fun_unittests fun_backend gmock gtest pthread gmock_main gtest_main pthread ${POCO_LIBRARIES})
    
    add_test(Tests fun_unittests)
endif()
