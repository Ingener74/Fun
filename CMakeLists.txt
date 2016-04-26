cmake_minimum_required(VERSION 3.0)

if(MSVC)
else()
    add_definitions(-std=c++11)
endif()


option(ENABLE_DESERTED_XYLOPHONE "Enable Deserted-Xylophone" ON)
if(ENABLE_DESERTED_XYLOPHONE)
    add_subdirectory(Deserted-Xylophone)
endif()


option(ENABLE_TAINTED_BULLDOZER "Enable Tainted-Bulldozer" ON)
if(ENABLE_TAINTED_BULLDOZER)
    add_subdirectory(Tainted-Bulldozer)
endif()


option(ENABLE_RARE_CRYSTAL "Enable Rare-Crystal" OFF)
if(ENABLE_RARE_CRYSTAL)
    add_subdirectory(Rare-Crystal)
endif()


option(ENABLE_RAW_RAILROAD "Enable Raw-Railroad" ON)
if(ENABLE_RAW_RAILROAD)
    add_subdirectory(Raw-Railroad)
endif()


option(ENABLE_DREADED_BACKPACK "Enable Dreaded-Backpack" OFF)
if(ENABLE_DREADED_BACKPACK)
    add_subdirectory(Dreaded-Backpack)
endif()