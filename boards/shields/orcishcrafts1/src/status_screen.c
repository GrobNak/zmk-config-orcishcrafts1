#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

static lv_obj_t *main_screen;

// Automated rendering thread loop to keep the ST7789 bus actively driven
static void refresh_timer_cb(lv_timer_t * timer) {
    if (main_screen != NULL) {
        lv_obj_invalidate(main_screen);
        lv_refr_now(NULL);
    }
}

lv_obj_t *zmk_display_status_screen() {
    // 1. Initialize the root screen object canvas
    main_screen = lv_obj_create(NULL);
    
    // 2. Set strict dimensions matching your physical 170x320 grid viewport
    lv_obj_set_size(main_screen, 170, 320);
    lv_obj_set_pos(main_screen, 0, 0);
    lv_obj_clear_flag(main_screen, LV_OBJ_FLAG_SCROLLABLE);
    
    // 3. Paint the canvas background layer warm amber orange (Hex: 0xE67E22)
    lv_obj_set_style_bg_color(main_screen, lv_color_hex(0xE67E22), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(main_screen, LV_OPA_COVER, LV_PART_MAIN);
    
    // 4. ZEPHYR ASYNC LOCK FIX: Register an active 50ms refresh timer 
    // This loops the frame buffer memory and prevents the SPI lines from dropping into idle sleep
    lv_timer_create(refresh_timer_cb, 50, NULL);
    
    return main_screen;
}
