cmake_minimum_required(VERSION 3.5)

project(ArkArena VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -std=c++11 -fsanitize=address")


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

option(UNIT_TESTS "Build the unit tests")
if(UNIT_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()


find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} ./)

# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "Qt5 library status:")
message(STATUS "    version: ${Qt5_VERSION}")
message(STATUS "    config: ${Qt5_DIR}")
message(STATUS "    include path: ${Qt5_INCLUDE_DIRS}")
message(STATUS "Qt6 library status:")
message(STATUS "    version: ${Qt6_VERSION}")
message(STATUS "    config: ${Qt6_DIR}")
message(STATUS "    include path: ${Qt6_INCLUDE_DIRS}")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Quick  Gui QuickWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Quick Gui QuickWidgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        gui/mainwindow.cpp
        gui/mainwindow.h
        gui/mainwindow.ui
        gui/resources.qrc
        gui/dockimagesource.h
        gui/dockimagesource.cpp
        gui/dockimagesource.ui
        imageSource/ImageSource.h
        imageSource/single_camera_source/SingleCameraImageSource.cpp
        imageSource/single_camera_source/SingleCameraImageSource.h
        imageSource/photo_source/PhotoImageSource.cpp
        imageSource/photo_source/PhotoImageSource.h
        imageSource/photo_source/PhotoLoader.cpp
        imageSource/photo_source/PhotoLoader.h
        tools/LiveImageProvider.cpp
        tools/LiveImageProvider.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ArkArena
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ArkArena APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ArkArena SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ArkArena
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ArkArena PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Quick  Qt${QT_VERSION_MAJOR}::Gui  Qt${QT_VERSION_MAJOR}::QuickWidgets)
target_link_libraries (ArkArena PRIVATE ${OpenCV_LIBS})

set_target_properties(ArkArena PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ArkArena)
endif()
