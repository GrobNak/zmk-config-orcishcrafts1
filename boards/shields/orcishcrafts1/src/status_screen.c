#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

lv_obj_t *zmk_display_status_screen() {
    // 1. Initialize the root canvas screen container object
    lv_obj_t *screen = lv_obj_create(NULL);
    
    // 2. Set strict viewport dimensions to anchor the physical 172x320 boundaries
    lv_obj_set_size(screen, 172, 320);
    lv_obj_set_pos(screen, 0, 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    
    // 3. Paint the canvas background layer with your warm amber color (Hex: 0xE67E22)
    lv_obj_set_style_bg_color(screen, lv_color_hex(0xE67E22), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    
    // 4. ZEPHYR ASYNC LINKER FIX: Force an immediate hardware cache push loop
    // This explicitly tells the driver to grab the color cache and stream it down the pins.
    lv_obj_invalidate(screen);
    lv_refr_now(NULL);
    
    return screen;
}
