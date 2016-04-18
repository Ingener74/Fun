cmake_minimum_required(VERSION 3.0)

add_subdirectory(Deserted-Xylophone)

add_subdirectory(Tainted-Bulldozer)

option(ENABLE_RARE_CRYSTAL "Enable Rare-Crystal" OFF)

if(ENABLE_RARE_CRYSTAL)
    add_subdirectory(Rare-Crystal)
endif()

option(ENABLE_DREADED_BACKPACK "Enable Tainted-Bulldozer" OFF)

if(ENABLE_DREADED_BACKPACK)
    add_subdirectory(Dreaded-Backpack)
endif()