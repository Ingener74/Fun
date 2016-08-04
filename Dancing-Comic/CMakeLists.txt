cmake_minimum_required(VERSION 3.0)

project(Dancing-Comic)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
include_directories(
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5Core_INCLUDE_DIRS}
)

qt5_add_resources(DANCING_COMIC_RESOURCES res/resources.qrc)

qt5_wrap_ui(DANCING_COMIC_UI res/mainwidget.ui)

set(DancingComic_SOURCES
    ${DANCING_COMIC_RESOURCES} 
    ${DANCING_COMIC_UI}
    src/main.cpp
    src/MainWidget.h
    src/MainWidget.cpp
    src/OperandsController.h
    src/OperandsController.cpp
)

if(WIN32)
    if(MSVC)
    	list(APPEND DancingComic_SOURCES res/resources.rc)
    endif()
    add_executable(DancingComic WIN32 ${DancingComic_SOURCES}) 
else()
	add_executable(DancingComic ${DancingComic_SOURCES})
endif()

target_link_libraries(DancingComic Qt5::Widgets Qt5::Core Fun)

install(TARGETS DancingComic DESTINATION bin)

if(WIN32)
	set(CPACK_GENERATOR "NSIS")
else()
	set(CPACK_GENERATOR "ZIP")
endif()

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Shnaider Pavel") #required
 
include(CPack)