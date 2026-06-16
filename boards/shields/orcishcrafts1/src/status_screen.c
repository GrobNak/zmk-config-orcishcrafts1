#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

lv_obj_t *zmk_display_status_screen() {
    // 1. Create the base canvas screen pointer
    lv_obj_t *screen = lv_obj_create(NULL);
    
    // 2. Map coordinates explicitly to the physical 170x320 panel
    lv_obj_set_size(screen, 170, 320);
    lv_obj_set_pos(screen, 0, 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    
    // 3. Paint the canvas layer warm amber (Hex: 0xE67E22)
    lv_obj_set_style_bg_color(screen, lv_color_hex(0xE67E22), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    
    // 4. HARDWARE SPEC FIX: Force an immediate graphic flush update 
    // This wakes up the ST7789 driver and prevents it from sleeping.
    lv_obj_invalidate(screen);
    lv_refr_now(NULL);
    
    return screen;
}
