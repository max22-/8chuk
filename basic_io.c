#include "pico/stdlib.h"
#include "basic_io.h"

#define LED_PIN PICO_DEFAULT_LED_PIN
#define BUTTON_PIN 6

void led_init()
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void led_on()
{
    gpio_put(LED_PIN, 1);
}

void led_off()
{
    gpio_put(LED_PIN, 0);
}

void button_init()
{
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
}

uint32_t button_read()
{
    if(!gpio_get(BUTTON_PIN))
        return 1;
    else
        return 0;
}
