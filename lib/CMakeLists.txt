add_library(emblib STATIC
  src/mem.c
  src/ring.c
)

target_include_directories(emblib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Freestanding: the library must not assume a hosted C environment.
# -ffreestanding  signals to GCC that libc may not be present
# -fno-builtin    prevents the compiler from silently replacing our
#                 implementations with its own intrinsics (critical for
#                 functions like memcpy/memset which GCC loves to swap out)
target_compile_options(emblib PRIVATE
  -ffreestanding
  -fno-builtin
)
