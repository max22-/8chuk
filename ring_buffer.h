#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "8joy.h"

void ring_buffer_put(hid_key c);
hid_key ring_buffer_get();

#endif