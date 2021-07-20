#ifndef NUNCHUK_H
#define NUNCHUK_H

void nunchuk_init();
void nunchuk_update();
uint8_t nunchuk_x();
uint8_t nunchuk_y();
bool nunchuk_button_c();
bool nunchuk_button_z();
uint16_t nunchuk_ax();
uint16_t nunchuk_ay();
uint16_t nunchuk_az();
void nunchuk_display();


#endif