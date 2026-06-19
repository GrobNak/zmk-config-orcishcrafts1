#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

lv_obj_t *zmk_display_status_screen(void) {
    // 1. Root Screen Canvas Container
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_size(screen, 240, 320);
    lv_obj_set_pos(screen, 0, 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    
    // Remove default canvas borders/padding
    lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);

    // 2. THE TOP BLOCK: Paint a sharp block of vibrant red (Hex: 0xE74C3C)
    lv_obj_t *top_block = lv_obj_create(screen);
    lv_obj_set_size(top_block, 240, 160); // Half screen height
    lv_obj_set_pos(top_block, 0, 0);
    lv_obj_clear_flag(top_block, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(top_block, lv_color_hex(0xE74C3C), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(top_block, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(top_block, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(top_block, 0, LV_PART_MAIN);

    // 3. THE BOTTOM BLOCK: Paint a sharp block of solid green (Hex: 0x2ECC71)
    lv_obj_t *bottom_block = lv_obj_create(screen);
    lv_obj_set_size(bottom_block, 240, 160);
    lv_obj_set_pos(bottom_block, 0, 160); // Aligned right under the red block
    lv_obj_clear_flag(bottom_block, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(bottom_block, lv_color_hex(0x2ECC71), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bottom_block, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(bottom_block, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(bottom_block, 0, LV_PART_MAIN);

    // 4. Force direct graphics synchronization flush down the SPI lanes
    lv_scr_load(screen);
    lv_obj_invalidate(screen);
    lv_refr_now(NULL);
    
    return screen;
}
