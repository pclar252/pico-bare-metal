cmake_minimum_required(VERSION 3.25)

project(pico-bare-metal
  VERSION 0.1.0
  LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

if(PROJECT_IS_TOP_LEVEL)
  include(FetchContent)
  FetchContent_Declare(
    Unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG        v2.6.1
  )
  FetchContent_MakeAvailable(Unity)

  if(NOT CMAKE_CROSSCOMPILING)
    add_subdirectory(test/host)
  else()
    add_subdirectory(test/target)
  endif()
endif()
