#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zmk/display.h>

/* Standard baseline graphics header path for your firmware generation */
#include <lvgl.h>

/* Define the status screen initialization hook required by ZMK's display thread */
lv_obj_t *zmk_display_status_screen() {
    /* Create a clean root screen base canvas container */
    lv_obj_t *screen = lv_obj_create(NULL);

    /* 
       THE VISIBILITY FIX:
       Force the root canvas container background to be a clean, solid White color 
       instead of defaulting to invisible pure black.
    */
    lv_obj_set_style_bg_color(screen, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);

    /* Instantiates your custom text label inside the styled screen canvas */
    lv_obj_t *custom_label = lv_label_create(screen);
    lv_label_set_text(custom_label, "Check-it Hal :o");

    /* 
       THE FONT COLOR FIX:
       Force the text color to a crisp, high-contrast black so it stands out 
       vividly against the white canvas backdrop.
    */
    lv_obj_set_style_text_color(custom_label, lv_color_black(), LV_PART_MAIN);

    /* Forces the text label to sit perfectly dead center on your 170x320 matrix */
    lv_obj_align(custom_label, LV_ALIGN_CENTER, 0, 0);

    /* Return the completed graphic tree to the OS rendering loop */
    return screen;
}
