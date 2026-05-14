add_executable(test_runner
  main.c
  test_mem.c
)

target_link_libraries(test_runner PRIVATE emblib unity)

target_include_directories(test_runner PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# cmake --build build/host --target run_tests
add_custom_target(run_tests
  COMMAND test_runner
  DEPENDS test_runner
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running emblib test suite"
)
