#include "keymap.h"
#include <tusb.h>

uint8_t hid_keycode[256];
uint8_t hid_modifier[256];

#define K(a, b) hid_keycode[a] = b
#define M(a, b) hid_modifier[a] = b

void keymap_init()
{
    K('\b', HID_KEY_BACKSPACE);
    K('\n', HID_KEY_ENTER);
    K('a', HID_KEY_Q);
    K('r', HID_KEY_R);
    K('x', HID_KEY_X);
    K('?', HID_KEY_M);
    K('y', HID_KEY_Y);
    K('b', HID_KEY_B);
    K('p', HID_KEY_P);
    K('q', HID_KEY_A);
    K('s', HID_KEY_S);
    K('d', HID_KEY_D);
    K('g', HID_KEY_G);
    K('\\', HID_KEY_8);
    K('t', HID_KEY_T);
    K('c', HID_KEY_C);
    K('z', HID_KEY_W);
    K('.', HID_KEY_COMMA);
    K('i', HID_KEY_I);
    K('h', HID_KEY_H);
    K('j', HID_KEY_J);
    K(',', HID_KEY_M);
    K('e', HID_KEY_E);
    K('l', HID_KEY_L);
    K('k', HID_KEY_K);
    K('@', HID_KEY_0);
    K('o', HID_KEY_O);
    K('u', HID_KEY_U);
    K('v', HID_KEY_V);
    K('w', HID_KEY_Z);
    K('n', HID_KEY_N);
    K('m', HID_KEY_SEMICOLON);
    K('f', HID_KEY_F);
    K('à', HID_KEY_0);

    M('\b', 0);
    M('\n', 0);
    M('a', 0);
    M('r', 0);
    M('x', 0);
    M('?', KEYBOARD_MODIFIER_LEFTSHIFT);
    M('y', 0);
    M('b', 0);
    M('p', 0);
    M('q', 0);
    M('s', 0);
    M('d', 0);
    M('g', 0);
    M('\\', KEYBOARD_MODIFIER_RIGHTALT);
    M('t', 0);
    M('c', 0);
    M('z', 0);
    M('.', KEYBOARD_MODIFIER_LEFTSHIFT);
    M('i', 0);
    M('h', 0);
    M('j', 0);
    M(',', 0);
    M('e', 0);
    M('l', 0);
    M('k', 0);
    M('@', KEYBOARD_MODIFIER_RIGHTALT);
    M('o', 0);
    M('u', 0);
    M('v', 0);
    M('w', 0);
    M('n', 0);
    M('m', 0);
    M('f', 0);
    M('à', 0);

}