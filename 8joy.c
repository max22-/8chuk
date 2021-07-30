#include <stdio.h>
#include <string.h>
#include <math.h>
#include <tusb.h>
#include "8joy.h"

#define THRESHOLD 0.5
#define QS 70 /* quadrant size, in degrees */

#define degrees(rad) ((rad)*180/M_PI)

hid_key key_none = {HID_KEY_NONE, 0};

bool key_equal(hid_key key1, hid_key key2)
{
  return 
        key1.keycode == key2.keycode 
    &&  key1.modifier == key2.modifier;
}

static void (*callback)(hid_key) = NULL;

void eight_joy_set_callback(void (*_callback)(hid_key))
{
    callback = _callback;
}

typedef struct {
  char* code;
  hid_key hid_keycode;
} KeyCode;

/* Quadrants
        1
    2       0
        3
*/

const KeyCode codes[] = {

  {"2", {HID_KEY_BACKSPACE, 0}},
  {"3", {HID_KEY_ENTER, 0}},

  {"01", {HID_KEY_A, 0}},
  {"012", {HID_KEY_R, 0}},
  {"0123", {HID_KEY_X, 0}},
  {"01230", {HID_KEY_SLASH, KEYBOARD_MODIFIER_LEFTSHIFT}}, // ?

  {"10", {HID_KEY_Y, 0}},
  {"103", {HID_KEY_B, 0}},
  {"1032", {HID_KEY_P, 0}},
  {"10321", {HID_KEY_Q, 0}},

  {"12", {HID_KEY_S, 0}},
  {"123", {HID_KEY_D, 0}},
  {"1230", {HID_KEY_G, 0}},
  {"1231", {HID_KEY_BACKSLASH, 0}},

  {"21", {HID_KEY_T, 0}},
  {"210", {HID_KEY_C, 0}},
  {"2103", {HID_KEY_Z, 0}},
  {"21032", {HID_KEY_PERIOD, 0}},

  {"23", {HID_KEY_I, 0}},
  {"230", {HID_KEY_H, 0}},
  {"2301", {HID_KEY_J, 0}},
  {"23012", {HID_KEY_COMMA, 0}},

  {"32", {HID_KEY_E, 0}},
  {"321", {HID_KEY_L, 0}},
  {"3210", {HID_KEY_K, 0}},
  {"32103", {HID_KEY_2, KEYBOARD_MODIFIER_LEFTSHIFT}}, // @

  {"30", {HID_KEY_O, 0}},
  {"301", {HID_KEY_U, 0}},
  {"3012", {HID_KEY_V, 0}},
  {"30123", {HID_KEY_W, 0}},

  {"03", {HID_KEY_N, 0}},
  {"032", {HID_KEY_M, 0}},
  {"0321", {HID_KEY_F, 0}},
  {"03210", {HID_KEY_1, KEYBOARD_MODIFIER_LEFTSHIFT}}, // !

};

hid_key code_to_character(const char* code)
{
  for(int i = 0; i < sizeof(codes)/sizeof(KeyCode); i++)
    if(!strcmp(codes[i].code, code))
      return codes[i].hid_keycode;
  return key_none;
}

char get_quadrant(double r, double theta)
{
  if(r < THRESHOLD)
    return 'c';   // center
  if(theta > 360 - QS/2 || theta < QS / 2)
    return '0';
  if(theta > 90 - QS/2 && theta < 90 + QS / 2)
    return '1';
  if(theta > 180 - QS/2 && theta < 180 + QS / 2)
    return '2';
  if(theta > 270 - QS/2 && theta < 270 + QS / 2)
    return '3';
  return 'b';   // in-between 2 quadrants
}

hid_key get_character(char q)
{
  static char code[256];
  static int cpt = 0;

  switch(q) {
    case '0':
    case '1':
    case '2':
    case '3':
        if(cpt < 255)
            code[cpt++] = q;
        else
            cpt = 0;
      break;
    case 'c': {
        code[cpt] = 0;
        hid_key character = code_to_character(code);
        cpt = 0;
        return character;
    }
    default:
      break;
  }
  return key_none;
}

void eight_joy_update(double joy_x, double joy_y) 
{
  static char quadrant = 'c';

  double r = sqrt(pow(joy_x, 2) + pow(joy_y, 2));
  double theta = degrees(atan2(joy_y, joy_x));
  if(theta < 0)
    theta += 360;

  char new_quadrant = get_quadrant(r, theta);
  if(new_quadrant != quadrant && new_quadrant != 'b') {
    quadrant = new_quadrant;
    hid_key k = get_character(quadrant);
    if(!key_equal(k, key_none))
        callback(k);
  }
}



