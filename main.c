#include <string.h>

#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"

#include "extend.h"
#include "touch.h"

#define LVGL_BUF_SIZE        (800 * 800 * 2 / 10)

static mpro_info info;
static struct touch t;

void screen_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *pc)
{
    int32_t w = lv_area_get_width(area);

#ifdef ENABLE_LVGL_ROTATE
    lv_display_rotation_t r = lv_display_get_rotation(disp);
    lv_area_t ra;
    if (r != LV_DISPLAY_ROTATION_0) {
        int32_t h = lv_area_get_height(area);
        lv_color_format_t cf = lv_display_get_color_format(disp);
        uint32_t ws = lv_draw_buf_width_to_stride(w, cf);
        uint32_t hs = lv_draw_buf_width_to_stride(h, cf);

        static uint8_t buf[LVGL_BUF_SIZE];
        switch(r) {
        case LV_DISPLAY_ROTATION_0:
            break;
        case LV_DISPLAY_ROTATION_90:
            lv_draw_sw_rotate(pc, buf, w, h, ws, hs, r, cf);
            break;
        case LV_DISPLAY_ROTATION_180:
            lv_draw_sw_rotate(pc, buf, w, h, ws, ws, r, cf);
            break;
        case LV_DISPLAY_ROTATION_270:
            lv_draw_sw_rotate(pc, buf, w, h, ws, hs, r, cf);
            break;
        }
        pc = buf;

        ra = *area;
        lv_display_rotate_area(disp, &ra);
        area = &ra;

        if(r != LV_DISPLAY_ROTATION_180)
            w = lv_area_get_width(area);
    }
#endif

    int32_t wb = w * 2;
    for (int y = area->y1; y <= area->y2; y++) {
        memcpy(info.framebuffer + (y * info.width + area->x1) * 2,
               pc + (y - area->y1) * wb, wb);
    }

    lv_display_flush_ready(disp);
}

void touch_ready(struct touch *pt)
{
    memcpy(&t, pt, sizeof(struct touch));
}

void main_indev_read(lv_indev_t *indev, lv_indev_data_t *data)
{
    if (t.count) {
        data->point.x = (t.p[0].xh.x.h << 8) + t.p[0].xl;
        data->point.y = (t.p[0].yh.x.h << 8) + t.p[0].yl;
        data->state = LV_INDEV_STATE_PRESSED;
        t.count = 0;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void timer_ready(void *unused)
{
    lv_tick_inc(1);
}

void usb_ready(int size)
{
    char buf[0x200];
    int used;
    for (int i = 0; i < size; i += used) {
        used = size > sizeof(buf) ? sizeof(buf) : size;
        mproex_usb_read(buf, used);
    }
}

void main(void)
{
    lv_init();

    mproex_get_info(&info);

    lv_disp_t *disp = lv_display_create(info.width, info.height);
    lv_display_set_flush_cb(disp, screen_flush);
    lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565);

    static uint8_t buf[LVGL_BUF_SIZE];
    int mode = LV_DISPLAY_RENDER_MODE_PARTIAL;
    lv_display_set_buffers(disp, buf, NULL, LVGL_BUF_SIZE, mode);

    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, main_indev_read);

    mproex_set_cb(CB_TIMER_READY, (mpro_callback)timer_ready);
    mproex_set_cb(CB_LOOP_READY, (mpro_callback)lv_timer_handler);
    mproex_set_cb(CB_TOUCH_RX_READY, (mpro_callback)touch_ready);
    mproex_set_cb(CB_USB_RX_READY, (mpro_callback)usb_ready);

#ifdef ENABLE_LVGL_ROTATE
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);
#endif

    lv_demo_widgets();
}

