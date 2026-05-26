add_executable(led_blink main.c)

target_link_libraries(led_blink PRIVATE emblib pico_stdlib)


pico_add_extra_outputs(led_blink)
