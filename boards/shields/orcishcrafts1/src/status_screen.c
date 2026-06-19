#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

lv_obj_t *zmk_display_status_screen(void) {
    // 1. Root Screen Canvas Object initialization
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_size(screen, 240, 320);
    lv_obj_set_pos(screen, 0, 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    
    // 2. BACKGROUND LAYER: Paint canvas solid green (Hex: 0x2ECC71)
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x2ECC71), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    
    // 3. TEXT LAYER: Create a centered label to print your red text
    lv_obj_t *text_label = lv_label_create(screen);
    lv_label_set_text(text_label, "ORCISH CRAFTS");
    
    // Set text color to bold vibrant red (Hex: 0xE74C3C)
    lv_obj_set_style_text_color(text_label, lv_color_hex(0xE74C3C), LV_PART_MAIN);
    
    // Center the text block cleanly inside your 240x320 viewport boundaries
    lv_obj_align(text_label, LV_ALIGN_CENTER, 0, 0);
    
    // 4. Force direct graphics array synchronization flush down the SPI lanes
    lv_scr_load(screen);
    lv_obj_invalidate(screen);
    lv_refr_now(NULL);
    
    return screen;
}
