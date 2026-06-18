#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

lv_obj_t *zmk_display_status_screen() {
    lv_obj_t *screen = lv_obj_create(NULL);
    
    // Canvas sizing synchronized with your physical 172-pixel width requirement
    lv_obj_set_size(screen, 172, 320);         // <--- UPGRADE TO 172
    lv_obj_set_pos(screen, 0, 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    
    // Set background color to warm amber orange (Hex: 0xE67E22)
    lv_obj_set_style_bg_color(screen, lv_color_hex(0xE67E22), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    
    // Force immediate visual cache synchronization
    lv_obj_invalidate(screen);
    lv_refr_now(NULL);
    
    return screen;
}
