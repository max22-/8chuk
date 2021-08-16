#include <stdio.h>
#include <string.h>
#include <math.h>
#include "8joy.h"
#include "keymap.h"

#define THRESHOLD 0.5
#define QS 70 /* quadrant size, in degrees */

#define degrees(rad) ((rad)*180/M_PI)

static void (*callback)(char) = NULL;

void eight_joy_init()
{
  keymap_init();
}

void eight_joy_set_callback(void (*_callback)(char))
{
    callback = _callback;
}

typedef struct {
  char* code;
  char character;
} KeyCode;

/* Quadrants
        1
    2       0
        3
*/

const KeyCode codes[] = {

  {"2", '\b'},
  {"3", '\n'},

  {"01", 'a'},
  {"012", 'r'},
  {"0123", 'x'},
  {"01230", '?'},

  {"10", 'y'},
  {"103", 'b'},
  {"1032", 'p'},
  {"10321", 'q'},

  {"12", 's'},
  {"123", 'd'},
  {"1230", 'g'},
  {"1231", '\''},

  {"21", 't'},
  {"210", 'c'},
  {"2103", 'z'},
  {"21032", '.'},

  {"23", 'i'},
  {"230", 'h'},
  {"2301", 'j'},
  {"23012", ','},

  {"32", 'e'},
  {"321", 'l'},
  {"3210", 'k'},
  {"32103", '@'},

  {"30", 'o'},
  {"301", 'u'},
  {"3012", 'v'},
  {"30123", 'w'},

  {"03", 'n'},
  {"032", 'm'},
  {"0321", 'f'},
  {"03210", '!'}, 

};

char code_to_character(const char* code)
{
  for(int i = 0; i < sizeof(codes)/sizeof(KeyCode); i++)
    if(!strcmp(codes[i].code, code))
      return codes[i].character;
  return 0;
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

char get_character(char q)
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
        char character = code_to_character(code);
        cpt = 0;
        return character;
    }
    default:
      break;
  }
  return 0;
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
    char c = get_character(quadrant);
    if(c != 0)
        callback(c);
  }
}



