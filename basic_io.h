#ifndef BASIC_IO_H
#define BASIC_IO_H

void led_init();
void led_on();
void led_off();

void button_init();
uint32_t button_read();

#endif