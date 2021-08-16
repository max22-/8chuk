#ifndef KEYMAP_H
#define KEYMAP_H

#include <stdint.h>

void keymap_init();
extern uint8_t hid_keycode[256];
extern uint8_t hid_modifier[256];

#endif