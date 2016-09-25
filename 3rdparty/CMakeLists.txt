cmake_minimum_required(VERSION 3.0)

include(ExternalProject)

option(ENABLE_DEPEND_POCO "Enable POCO dependency" ON)
if(ENABLE_DEPEND_POCO)
    add_subdirectory(POCO)
endif()

option(ENABLE_DEPEND_GTEST "Enable gtest dependency" ON)
if(ENABLE_DEPEND_GTEST)
    add_subdirectory(gtest)
endif()

option(ENABLE_DEPEND_FLEX "Enable flex dependency" ON)
if(ENABLE_DEPEND_FLEX)
    add_subdirectory(flex)
    add_dependencies(ext_flex ext_bison ext_m4)
endif()

option(ENABLE_DEPEND_BISON "Enable bison dependency" ON)
if(ENABLE_DEPEND_BISON)
    add_subdirectory(bison)
    add_dependencies(ext_bison ext_m4)
endif()

option(ENABLE_DEPEND_M4 "Enable m4 dependency" ON)
if(ENABLE_DEPEND_M4)
    add_subdirectory(m4)
endif()

