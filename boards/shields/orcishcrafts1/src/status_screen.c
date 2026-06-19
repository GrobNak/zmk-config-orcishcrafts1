#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

lv_obj_t *zmk_display_status_screen(void) {
    // 1. Initialize a core, clean canvas container screen object
    lv_obj_t *screen = lv_obj_create(NULL);
    
    // 2. FIXED SIZE ALIGNMENT: Match the safe 240x320 devicetree structure exactly
    lv_obj_set_size(screen, 240, 320);
    lv_obj_set_pos(screen, 0, 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    
    // Remove default canvas borders/padding
    lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);
    
    // 3. Paint the canvas background layer completely with your warm amber orange (Hex: 0xE67E22)
    lv_obj_set_style_bg_color(screen, lv_color_hex(0xE67E22), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    
    // 4. Flush the graphics buffer immediately down the active SPI1 lines
    lv_scr_load(screen);
    lv_obj_invalidate(screen);
    lv_refr_now(NULL);
    
    return screen;
}
