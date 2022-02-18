cmake_minimum_required(VERSION 3.10.0 )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} ./)

add_subdirectory("${PROJECT_SOURCE_DIR}/external/googletest" "external/googletest")

mark_as_advanced(
        BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
        gmock_build_tests gtest_build_samples gtest_build_tests
        gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

add_executable(KilobotArenaTest ImageBuffer_test.cc)

gtest_discover_tests(KilobotArenaTest
        # set a working directory so your project root so that you can find test data via paths relative to the project root
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
        )

target_link_libraries(KilobotArenaTest gtest gmock gtest_main)
set_target_properties(KilobotArenaTest PROPERTIES FOLDER tests)


target_link_libraries(KilobotArenaTest Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries (KilobotArenaTest ${OpenCV_LIBS})