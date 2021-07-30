#include "ring_buffer.h"

static char ring_buffer[8];
static int head = 0, tail = 0;

#define INC(i) ((i+1) % sizeof(ring_buffer))

void ring_buffer_clear()
{
    head = 0, tail = 0;
}

void ring_buffer_put(char c)
{
    ring_buffer[tail] = c;
    int nt = INC(tail);
    if(nt == head)
        head = INC(head);
    tail = nt;
}

char ring_buffer_get()
{
    if(head == tail)
        return 0;
    int ret = ring_buffer[tail];
    tail = INC(tail);
    return ret;
}