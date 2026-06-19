#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

lv_obj_t *zmk_display_status_screen(void) {
    // 1. Root Screen Canvas Object initialization
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_size(screen, 240, 320);
    lv_obj_set_pos(screen, 0, 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    
    // Clear borders/margins
    lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);
    
    // 2. MONOCHROME BASE FILL: Paint the entire screen canvas solid white (True bit high)
    lv_obj_set_style_bg_color(screen, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    
    // 3. Force immediate graphics flush down your copper wires
    lv_scr_load(screen);
    lv_obj_invalidate(screen);
    lv_refr_now(NULL);
    
    return screen;
}
