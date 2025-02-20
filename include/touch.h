#ifndef _TOUCH_H
#define _TOUCH_H

#include <stdint.h>

union axis{
    struct hx{
        unsigned char h:4;
        unsigned char u:2;
        unsigned char f:2;
    } x;

    struct hy{
        unsigned char h:4;
        unsigned char id:4;
    } y;

    char c;
};

struct point {
    union axis xh;
    unsigned char xl;
    union axis yh;
    unsigned char yl;

    unsigned char weight;
    unsigned char misc;
};

struct touch {
    unsigned char id[2];
    unsigned char count;
    struct point p[2];
};

#endif // _TOUCH_H
