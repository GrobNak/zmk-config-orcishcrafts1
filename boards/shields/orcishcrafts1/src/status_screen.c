#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zmk/display.h>

/* Standard baseline graphics header path for your firmware generation */
#include <lvgl.h>

/* Define the status screen initialization hook required by ZMK's display thread */
lv_obj_t *zmk_display_status_screen() {
    /* Pass a single NULL argument to create a clean root screen base canvas container */
    lv_obj_t *screen = lv_obj_create(NULL);

    /* 
       THE ONE-ARGUMENT FIX:
       In LVGL v8, label instantiation only takes the parent object variable container.
    */
    lv_obj_t *custom_label = lv_label_create(screen);
    
    /* Safely assign your custom text string across the label layer */
    lv_label_set_text(custom_label, "Check-it Hal :o");

    /* Forces the text label to sit perfectly dead center on your 170x320 matrix */
    lv_obj_align(custom_label, LV_ALIGN_CENTER, 0, 0);

    /* Return the completed graphic tree to the OS rendering loop */
    return screen;
}
