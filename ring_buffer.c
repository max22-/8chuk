#include "ring_buffer.h"

static char ring_buffer[8];
static int head = 0, tail = 0;

#define INC(i) ((i+1) % (sizeof(ring_buffer)/sizeof(char)))


void ring_buffer_put(char key)
{
    ring_buffer[tail] = key;
    int nt = INC(tail);
    if(nt == head)
        head = INC(head);
    tail = nt;
}

char ring_buffer_get()
{
    if(head == tail)
        return 0;
    char ret = ring_buffer[head];
    head = INC(head);
    return ret;
}