#ifndef _EXTEND_H
#define _EXTEND_H

#include <stdint.h>

typedef void (*mpro_callback)(void *);

typedef struct {
    uint8_t *framebuffer;
    int width, height;
} mpro_info;

typedef enum {
    CB_TIMER_READY,
    CB_I2C_RX_READY,
    CB_UART_RX_READY,
    CB_TOUCH_RX_READY,
    CB_LOOP_READY,
    CB_USB_RX_READY,
} callback_type;

// EXTEND API
extern void mproex_get_info(mpro_info *info);
extern void mproex_set_cb(callback_type type, void* cb);
extern int mproex_i2c_write(uint8_t addr, void *d, int size);
extern int mproex_i2c_read(uint8_t addr, void *d, int size);
extern int mproex_uart_write(void *d, int size);
extern int mproex_uart_read(void *d, int size);
extern int mproex_usb_write(void *d, int size);
extern int mproex_usb_read(void *d, int size);

#ifdef MPRO
extern void mpro_extend_load(char *name);
extern mpro_callback mproex_i2crx_ready;
extern mpro_callback mproex_uartrx_ready;
extern mpro_callback mproex_loop_ready;
extern mpro_callback mproex_touch_ready;
extern mpro_callback mproex_usbrx_ready;
#endif

#endif // _EXTEND_H
