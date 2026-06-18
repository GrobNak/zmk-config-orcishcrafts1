#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

lv_obj_t *zmk_display_status_screen() {
    // 1. FORCE CORE THEME ABSTRACTION (Satisfies ZMK's internal layout generator)
    // This creates an active, fully opacified background canvas structure
    lv_obj_t *screen = lv_obj_create(NULL);
    
    // 2. Lock the absolute physical boundaries of your 172x320 viewport glass
    lv_obj_set_size(screen, 172, 320);
    lv_obj_set_pos(screen, 0, 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    
    // 3. Paint the canvas background layer completely with your warm amber orange (Hex: 0xE67E22)
    lv_obj_set_style_bg_color(screen, lv_color_hex(0xE67E22), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    
    // 4. ZEPHYR KERNEL UNLOCK HANDSHAKE
    // This tells ZMK's background display thread that a valid drawing is waiting, 
    // forcing the operating system to actively spin up the ST7789V driver.
    lv_scr_load(screen);
    lv_obj_invalidate(screen);
    lv_refr_now(NULL);
    
    return screen;
}
