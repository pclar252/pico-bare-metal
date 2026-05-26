if(CMAKE_CROSSCOMPILING)
  set(EMBLIB_CS_SRC src/cs_pico.c)
  set(EMBLIB_PLATFORM EMBLIB_PLATFORM_PICO)
else()
  set(EMBLIB_CS_SRC src/cs_host.c)
  set(EMBLIB_PLATFORM EMBLIB_PLATFORM_HOST)
endif()

add_library(emblib STATIC
  src/mem.c
  src/ring.c
  src/gpio.c
  src/io_bank.c
  src/nvic.c
  src/pad.c
  src/sio.c
  src/timer.c
  ${EMBLIB_CS_SRC}
)

target_compile_definitions(emblib PUBLIC ${EMBLIB_PLATFORM})

target_include_directories(emblib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Freestanding: the library must not assume a hosted C environment.
# -ffreestanding  signals to GCC that libc may not be present
# -fno-builtin    prevents the compiler from silently replacing our
#                 implementations with its own intrinsics (critical for
#                 functions like memcpy/memset which GCC loves to swap out)
set_target_properties(emblib PROPERTIES C_EXTENSIONS OFF)

target_compile_options(emblib PRIVATE
  -ffreestanding
  -fno-builtin
)
