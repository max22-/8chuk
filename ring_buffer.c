#include "ring_buffer.h"

static hid_key ring_buffer[8];
static int head = 0, tail = 0;

#define INC(i) ((i+1) % (sizeof(ring_buffer)/sizeof(hid_key)))


void ring_buffer_put(hid_key key)
{
    ring_buffer[tail] = key;
    int nt = INC(tail);
    if(nt == head)
        head = INC(head);
    tail = nt;
}

hid_key ring_buffer_get()
{
    if(head == tail)
        return key_none;
    hid_key ret = ring_buffer[head];
    head = INC(head);
    return ret;
}