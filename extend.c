#include "../../main/extend.h"

extern uint32_t __extend_start[];
uint32_t *extend_api = __extend_start + 64;

void mproex_get_info(mpro_info *p1)
{
    typedef void (*mproex_get_info_t)(mpro_info *);
    mproex_get_info_t fn = (mproex_get_info_t)extend_api[0];
    fn(p1);
}

void mproex_set_cb(callback_type p1, void *p2)
{
    typedef void (*mproex_set_cb_t)(callback_type p1, void *p2);
    mproex_set_cb_t fn = (mproex_set_cb_t)extend_api[1];
    fn(p1, p2);
}

int mproex_i2c_write(uint8_t p1, void *p2, int p3)
{
    typedef int (*mproex_i2c_write_t)(uint8_t p1, void *p2, int p3);
    mproex_i2c_write_t fn = (mproex_i2c_write_t)extend_api[2];
    return fn(p1, p2, p3);
}

int mproex_i2c_read(uint8_t p1, void *p2, int p3)
{
    typedef int (*mproex_i2c_read_t)(uint8_t p1, void *p2, int p3);
    mproex_i2c_read_t fn = (mproex_i2c_read_t)extend_api[3];
    return fn(p1, p2, p3);
}

int mproex_uart_write(void *p1, int p2)
{
    typedef int (*mproex_uart_write_t)(void *p1, int p2);
    mproex_uart_write_t fn = (mproex_uart_write_t)extend_api[4];
    return fn(p1, p2);
}

int mproex_uart_read(void *p1, int p2)
{
    typedef int (*mproex_uart_read_t)(void *p1, int p2);
    mproex_uart_read_t fn = (mproex_uart_read_t)extend_api[5];
    return fn(p1, p2);
}

int mproex_usb_write(void *p1, int p2)
{
    typedef int (*mproex_usb_write_t)(void *p1, int p2);
    mproex_usb_write_t fn = (mproex_usb_write_t)extend_api[6];
    return fn(p1, p2);
}

int mproex_usb_read(void *p1, int p2)
{
    typedef int (*mproex_usb_read_t)(void *p1, int p2);
    mproex_usb_read_t fn = (mproex_usb_read_t)extend_api[7];
    return fn(p1, p2);
}
