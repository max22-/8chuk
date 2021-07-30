cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(8chuk)

pico_sdk_init()

add_executable(${PROJECT_NAME}
    main.c
    nunchuk.c
    usb_stuff.c
    usb_descriptors.c
    basic_io.c
    ring_buffer.c
    8joy.c
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
target_include_directories(${PROJECT_NAME} PRIVATE ${PICO_TINYUSB_PATH}/src)

pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_i2c tinyusb_device)