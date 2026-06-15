#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zmk/display.h>
#include <lvgl.h>

// Fetch the backlight pin configuration structure from your overlay file
static const struct gpio_dt_spec backlight = GPIO_DT_SPEC_GET(DT_PATH(backlight), backlight_gpios);

lv_obj_t *zmk_display_status_screen() {
    // Initialize the GPIO pin and force it high (turn on the screen panel light)
    if (gpio_is_ready_dt(&backlight)) {
        gpio_pin_configure_dt(&backlight, GPIO_OUTPUT_ACTIVE);
    }

    // Create a base screen container object
    lv_obj_t *screen = lv_obj_create(NULL);
    
    // Set background color to warm amber orange (Hex: 0xE67E22)
    lv_obj_set_style_bg_color(screen, lv_color_hex(0xE67E22), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    
    return screen;
}
