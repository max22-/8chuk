#include <stdio.h>
#include "hardware/i2c.h"
#include "nunchuk.h"

/* Inpired by https://github.com/kfricke/micropython-nunchuck
   and https://bootlin.com/labs/doc/nunchuk.pdf
*/

static const uint8_t addr = 0x52;
static uint8_t rbuf[] = {0, 0, 0, 0, 0, 0};

void nunchuk_init()
{
    uint8_t buf0[] = {0xf0, 0x55}, buf1[] = {0xfb, 0x00};
    i2c_write_blocking(i2c_default, addr, buf0, 2, false);
    i2c_write_blocking(i2c_default, addr, buf1, 2, false);
}

void nunchuk_update()
{
    uint8_t buf[] = {0};
    i2c_write_blocking(i2c_default, addr, buf, 1, false);
    i2c_read_blocking(i2c_default, addr, rbuf, 6, false);
}

uint8_t nunchuk_x()
{
    return rbuf[0];
}

uint8_t nunchuk_y()
{
    return rbuf[1];
}

bool nunchuk_button_c()
{
    return !(rbuf[5] & 2);
}

bool nunchuk_button_z()
{
    return !(rbuf[5] & 1);
}

uint16_t nunchuk_ax()
{
    return (rbuf[2] << 2) + ((rbuf[5] & 0b00001100) >> 2);
}

uint16_t nunchuk_ay()
{
    return (rbuf[3] << 2) + ((rbuf[5] & 0b00110000) >> 4);
}

uint16_t nunchuk_az()
{
    return (rbuf[4] << 2) + ((rbuf[5] & 0b11000000) >> 6);
}

void nunchuk_display()
{
    printf("x = %d ", nunchuk_x());
    printf("y = %d ", nunchuk_y());
    printf("c = %d ", nunchuk_button_c());
    printf("z = %d ", nunchuk_button_z());
    printf("ax = %d ", nunchuk_ax());
    printf("ay = %d ", nunchuk_ay());
    printf("az = %d\n", nunchuk_az());
}