cmake_minimum_required(VERSION 3.22)
project(qtmovies VERSION 0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/lib")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # resource file e.g .qrc

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")

if(CLANG_TIDY_EXE)
  # Generate a lightweight wrapper script to filter out GCC-specific flags
  # that Clang/clang-tidy does not recognize (e.g., -mno-direct-extern-access)
  set(CLANG_TIDY_WRAPPER "${CMAKE_BINARY_DIR}/clang-tidy-wrapper.py")
  file(WRITE "${CLANG_TIDY_WRAPPER}"
    "#!/usr/bin/env python3\n"
    "import sys\n"
    "import subprocess\n"
    "\n"
    "args = sys.argv[1:]\n"
    "filtered_args = []\n"
    "for arg in args:\n"
    "    if arg == '-mno-direct-extern-access' or arg.startswith('-mno-direct-extern-access='):\n"
    "        continue\n"
    "    filtered_args.append(arg)\n"
    "\n"
    "cmd = ['${CLANG_TIDY_EXE}'] + filtered_args\n"
    "sys.exit(subprocess.run(cmd).returncode)\n"
  )
  execute_process(COMMAND chmod +x "${CLANG_TIDY_WRAPPER}")

  set(CMAKE_CXX_CLANG_TIDY
    "python3;${CLANG_TIDY_WRAPPER};-extra-arg=-std=c++20;-extra-arg=-Wno-unknown-warning-option;-extra-arg=-Wno-ignored-optimization-argument")
endif()

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

add_executable(qtmovies ${SOURCES} ${HEADERS} res.qrc)

target_include_directories(qtmovies PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(qtmovies PRIVATE
                      Qt6::Core
                      Qt6::Gui
                      Qt6::Widgets
                      webview::core)
