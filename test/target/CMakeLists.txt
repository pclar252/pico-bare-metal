cmake_minimum_required(VERSION 3.25)

# If PICO_SDK_PATH is not set, fetch the SDK from git at configure time.
# pico_sdk_import.cmake must be included before project() to set the toolchain.
if(NOT DEFINED ENV{PICO_SDK_PATH} AND NOT DEFINED PICO_SDK_PATH)
  set(PICO_SDK_FETCH_FROM_GIT ON CACHE BOOL "" FORCE)
endif()
include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/pico_sdk_import.cmake")

project(emblib-target-tests
  VERSION 0.1.0
  LANGUAGES C CXX ASM
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

pico_sdk_init()

add_subdirectory(../../lib lib)

add_subdirectory(led_blink)

