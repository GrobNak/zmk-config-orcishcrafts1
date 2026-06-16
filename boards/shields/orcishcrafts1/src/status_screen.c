#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

lv_obj_t *zmk_display_status_screen() {
    // 1. HARDWARE SPEC FIX: Force a 150ms thread delay to allow the slow ST7789 
    // physical lines to finish booting up after the hardware reset pulse.
    k_msleep(150);

    // 2. Create the base canvas screen pointer
    lv_obj_t *screen = lv_obj_create(NULL);
    
    // 3. Set absolute layout grid bounds to match the 170x320 physical panel
    lv_obj_set_size(screen, 170, 320);
    lv_obj_set_pos(screen, 0, 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    
    // 4. Paint the canvas layer with your warm amber color (Hex: 0xE67E22)
    lv_obj_set_style_bg_color(screen, lv_color_hex(0xE67E22), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    
    return screen;
}
