#ifndef EIGHT_JOY_H
#define EIGHT_JOY_H

#include <stdint.h>
#include <stdbool.h>

void eight_joy_init();
void eight_joy_set_callback(void (*callback)(char));
void eight_joy_update(double, double);


#endif