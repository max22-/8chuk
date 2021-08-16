#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "nunchuk.h"
#include "usb_stuff.h"
#include "basic_io.h"
#include "ring_buffer.h"
#include "8joy.h"

#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
#error No i2c on this board
#endif

void callback(char c)
{
    printf("%c", c);
    ring_buffer_put(c);
}

int main() {
    usb_init();
    stdio_init_all();
    led_init();
    button_init();
    eight_joy_init();

    // Initializing i2c
    i2c_init(i2c_default, 400 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

    nunchuk_init();
    eight_joy_set_callback(callback);

    double x = 0, y = 0;

    while (true) {
        nunchuk_update();
        x = nunchuk_x();
        y = nunchuk_y();
        x = (x - 128) / 128;
        y = (y - 128) / 128;
        eight_joy_update(x, y);
        usb_task();
    }
}
