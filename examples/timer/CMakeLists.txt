cmake_minimum_required(VERSION 3.25)

# If PICO_SDK_PATH is not set, fetch the SDK from git at configure time.
# pico_sdk_import.cmake must be included before project() to set the toolchain.
if(NOT DEFINED ENV{PICO_SDK_PATH} AND NOT DEFINED PICO_SDK_PATH)
  set(PICO_SDK_FETCH_FROM_GIT ON CACHE BOOL "" FORCE)
endif()
include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/pico_sdk_import.cmake")

project(timer-example
  VERSION 0.1.0
  LANGUAGES C CXX ASM
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

pico_sdk_init()

add_executable(timer_example main.c)

target_link_libraries(timer_example PRIVATE
  pico_stdlib
  hardware_timer
  hardware_irq
  hardware_gpio
)

pico_add_extra_outputs(timer_example)
