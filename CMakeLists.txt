cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(8chuk)

pico_sdk_init()

add_executable(8chuk
    8chuk.c
    nunchuk.c
)

pico_enable_stdio_usb(8chuk 1)
pico_enable_stdio_uart(8chuk 0)

pico_add_extra_outputs(8chuk)

target_link_libraries(8chuk pico_stdlib hardware_i2c)