#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zmk/display.h>

/* Standard baseline graphics header path for your firmware generation */
#include <lvgl.h>

/* Define the status screen initialization hook required by ZMK's display thread */
lv_obj_t *zmk_display_status_screen() {
    /* Pass a single NULL argument to create a clean root screen base canvas object container */
    lv_obj_t *screen = lv_obj_create(NULL);

    /* 
       THE LEGACY LVGL COMPILER COMPLIANCE FIX:
       Older iterations of the widget framework require explicit fallback template parameter cells
       to map layout structures into the final compiled firmware binary successfully.
    */
    lv_obj_t *custom_label = lv_label_create(screen, NULL);
    
    /* Safely assign your custom text string across the label object layer bounds */
    lv_label_set_text(custom_label, "Check-it Hal :o");

    /* Forces the text label to sit perfectly dead center on your 170x320 matrix */
    lv_obj_align(custom_label, LV_ALIGN_CENTER, 0, 0);

    /* Return the completed graphic tree to the OS rendering loop */
    return screen;
}
