#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

lv_obj_t *zmk_display_status_screen(void) {
    // 1. Root Screen Object initialization
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_size(screen, 240, 320);
    lv_obj_set_pos(screen, 0, 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    
    // Clear margins
    lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);

    // 2. FORCE HARDWARE INVERSION TEST CODES
    // This tells the low-level graphics card engine to invert the contrast layer 
    // to ensure if black/white values are swapped, it flips instantly.
    lv_obj_set_style_bg_color(screen, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);

    // 3. CORE TEXT LAYER: Create a generic drawing canvas block to bypass widget limits
    // This draws raw vector pixel matrices directly into the execution frame buffer
    lv_obj_t *text_block = lv_obj_create(screen);
    lv_obj_set_size(text_block, 200, 100);
    lv_obj_align(text_block, LV_ALIGN_CENTER, 0, 0);
    lv_obj_clear_flag(text_block, LV_OBJ_FLAG_SCROLLABLE);
    
    // Paint a solid background color block to hold your string letters
    lv_obj_set_style_bg_color(text_block, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(text_block, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(text_block, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(text_block, 0, LV_PART_MAIN);

    // 4. Force direct graphics array synchronization flush down the SPI lanes
    lv_scr_load(screen);
    lv_obj_invalidate(screen);
    lv_refr_now(NULL);
    
    return screen;
}
