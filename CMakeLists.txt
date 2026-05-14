cmake_minimum_required(VERSION 3.25)

project(pico-bare-metal
  VERSION 0.1.0
  LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Warnings applied to every target in this build
add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
  -Werror
  -Wshadow
  -Wconversion
  -Wcast-align
  -Wundef
)

add_subdirectory(lib)

# Tests are host-only; cross-compiling skips this subtree automatically
if(NOT CMAKE_CROSSCOMPILING)
  include(FetchContent)

  FetchContent_Declare(
    Unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG        v2.6.1
  )

  FetchContent_MakeAvailable(Unity)

  add_subdirectory(test)
endif()
