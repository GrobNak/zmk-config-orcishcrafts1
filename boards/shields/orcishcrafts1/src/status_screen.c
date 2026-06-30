#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zmk/display.h>

#include <lvgl.h>

/* 
   THE ACTUAL ZMK CORE RENDERING HOOK
   ZMK's display thread looks specifically for 'zmk_display_status_screen' 
   to draw the base layer layout. We hook into it natively.
*/
lv_obj_t *zmk_display_status_screen() {
    /* Create a clean root screen base object container canvas */
    lv_obj_t *screen = lv_obj_create(NULL);

    /* Paints your custom text directly onto the active screen container object */
    lv_obj_t *custom_label = lv_label_create(screen);
    lv_label_set_text(custom_label, "Check-it Hal :o");

    /* Forces the text label to sit perfectly dead center on your 170x320 matrix */
    lv_obj_align(custom_label, LV_ALIGN_CENTER, 0, 0);

    /* Return the completed graphic tree to the OS rendering loop */
    return screen;
}
