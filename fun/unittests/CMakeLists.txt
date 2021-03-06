cmake_minimum_required(VERSION 3.0)

option(ENABLE_FUN_UNITTESTS "Enable fun unittesting" ON)

if(MSVC)
    set(fun_unittests_SOURCES
        test.cpp
        test.h
        # test-empty.cpp
        # test-integer.cpp
        # test-bool.cpp
        # test-float.cpp
        # test-string.cpp
        test-id.cpp
        # test-binary-ops.cpp
        # test-assign.cpp
        # test-print.cpp
        # test-if.cpp
        # test-while.cpp
        # test-for.cpp
        # test-function.cpp
        # test-dictionary.cpp
        # test-class.cpp
    )
else()
    set(fun_unittests_SOURCES
        test.cpp
        test.h
        test-empty.cpp
        test-integer.cpp
        test-bool.cpp
        test-float.cpp
        test-string.cpp
        test-id.cpp
        test-binary-ops.cpp
        test-assign.cpp
        test-print.cpp
        test-if.cpp
        test-while.cpp
        test-for.cpp
        test-function.cpp
        test-dictionary.cpp
        test-class.cpp
        
        MockDebugger.cpp
        MockDebugger.h
    )
endif()

if(MINGW OR MSYS)
    add_executable(fun_unittests ${fun_unittests_SOURCES})
    target_link_libraries(fun_unittests fun_backend pthread ${GTEST_LIBRARIES} ${POCO_LIBRARIES})

    add_test(Tests fun_unittests)
elseif(MSVC)
    add_executable(fun_unittests ${fun_unittests_SOURCES})
    target_link_libraries(fun_unittests fun_backend ${GTEST_LIBRARIES} ${POCO_LIBRARIES})

    add_test(Tests fun_unittests)
elseif(EMSCRIPTEN)
elseif(ANDROID)
elseif(APPLE)
else()
    add_executable(fun_unittests ${fun_unittests_SOURCES})
    target_link_libraries(fun_unittests fun_backend pthread ${GTEST_LIBRARIES} ${POCO_LIBRARIES})

    add_test(Tests fun_unittests)
endif()
