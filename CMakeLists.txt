cmake_minimum_required(VERSION 3.22)
project(qtmovies VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/lib")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # resource file e.g .qrc

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

set(WEBVIEW_BUILD_STATIC_LIBRARY ON CACHE BOOL "" FORCE)
set(WEBVIEW_BUILD_SHARED_LIBRARY OFF CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
    webview
    GIT_REPOSITORY https://github.com/webview/webview
    GIT_TAG 0.12.0)
FetchContent_MakeAvailable(webview)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.hpp")

add_executable(qtmovies ${SOURCES} ${HEADERS})

target_include_directories(qtmovies PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(qtmovies PRIVATE
                      Qt6::Core
                      Qt6::Gui
                      Qt6::Widgets
                      webview::core)
