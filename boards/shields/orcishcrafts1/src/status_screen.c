#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

// Direct low-level reference to the Nordic nRF52840 Pin Configuration Registers
#define NRF_P0_BASE 0x50000000
#define P0_PIN_CNF_24 *(volatile uint32_t*)(NRF_P0_BASE + 0x700 + (24 * 4))
#define P0_OUTSET       *(volatile uint32_t*)(NRF_P0_BASE + 0x508)

lv_obj_t *zmk_display_status_screen() {
    // 1. Force nRF52840 Chip Pin 24 (D5) into Output Mode with high drive strength
    P0_PIN_CNF_24 = (1 << 0) | (3 << 8); // Dir: Output, Drive: High Drive

    // 2. Immediately set Pin 24 HIGH to flood the display BLK trace with 3.3V power
    P0_OUTSET = (1 << 24);

    // 3. Render the warm amber color canvas screen
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0xE67E22), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    
    return screen;
}
