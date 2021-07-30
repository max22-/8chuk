#ifndef EIGHT_JOY_H
#define EIGHT_JOY_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t keycode;
    uint8_t modifier;
} hid_key;

extern hid_key key_none;

bool key_equal(hid_key, hid_key);

void eight_joy_set_callback(void (*callback)(hid_key));
void eight_joy_update(double, double);


#endif