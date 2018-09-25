cmake_minimum_required(VERSION 3.8.2)

project(TrebleShot VERSION 1.0)

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC
set(CMAKE_AUTOMOC ON)

# Include Qt basic functions
include(QtCommon)

# Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
fix_project_version()

#For Build on Mac: uncomment following srting and provice proper way to QT
set(CMAKE_PREFIX_PATH ~/DevToolsMac/QT/5.9.6/clang_64)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Make this a GUI application on Windows
if (WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif ()

# Find the Qt5 libraries
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Widgets REQUIRED)

IF (Qt5Core_FOUND)
    MESSAGE(STATUS "Found Qt ${Qt5Core_VERSION_STRING}")

    # FIX: Qt was built with -reduce-relocations
    if (Qt5_POSITION_INDEPENDENT_CODE)
        SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
    endif ()

    # guess plugins and libraries directory
    set(QT_PLUGINS_DIR "${Qt5Core_DIR}/../../../plugins")
    get_target_property(QT_LIBRARY_DIR Qt5::Core LOCATION)
    get_filename_component(QT_LIBRARY_DIR ${QT_LIBRARY_DIR} PATH)
ELSE ()
    MESSAGE(FATAL_ERROR "No Qt5 found!")
ENDIF ()

add_project_meta(META_FILES_TO_INCLUDE)

qt5_add_resources(QRCS assets/resources.qrc)
qt5_wrap_ui(UI_HEADERS src/ui/mainwindow.ui)

set(UTIL_LIBRARY src/database/accessdatabase.h
        src/database/accessdatabase.cpp
        src/broadcast/communicationserver.h
        src/broadcast/communicationserver.cpp
        src/config/config.h
        src/coolsocket/coolsocket.h
        src/coolsocket/coolsocket.cpp
        src/config/keyword.h
        src/model/stringlistmodel.h
        src/model/stringlistmodel.cpp
        src/database/object/transferobject.h
        src/database/object/transferobject.cpp
        src/database/object/transfergroup.h
        src/database/object/transfergroup.cpp src/database/object/networkdevice.cpp src/database/object/networkdevice.h)

add_library(sources SHARED ${UTIL_LIBRARY} ${UI_HEADERS} ${QRCS})
add_executable(TrebleShot src/main.cpp src/ui/mainwindow.cpp)

# Add the Qt5 Widgets for linking
if (NOT TARGET Qt5::WinMain)
    add_library(Qt5::WinMain STATIC IMPORTED)
endif ()

target_link_libraries(sources PUBLIC Qt5::Core Qt5::Gui Qt5::Network Qt5::Sql Qt5::Widgets)
target_link_libraries(TrebleShot sources)