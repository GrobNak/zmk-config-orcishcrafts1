#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

lv_obj_t *zmk_display_status_screen() {
    // 1. Create the base canvas screen pointer
    lv_obj_t *screen = lv_obj_create(NULL);
    
    // 2. ST7789 SPEC MANDATE: Explicitly break auto-layout and set absolute grid bounds
    lv_obj_set_size(screen, 170, 320);
    lv_obj_set_pos(screen, 0, 0);
    
    // 3. Force alignment constraints so memory vectors don't drop structural pointers
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    
    // 4. Fill the exact layout grid with your warm amber color (Hex: 0xE67E22)
    lv_obj_set_style_bg_color(screen, lv_color_hex(0xE67E22), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    
    return screen;
}
