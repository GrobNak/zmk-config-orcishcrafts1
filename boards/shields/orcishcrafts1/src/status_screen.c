#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>

// Automatically pull the display hardware handle directly from your overlay file
#define DISPLAY_NODE DT_NODELABEL(display)

static int initialize_test_bench_screen(void) {
    // 1. Locate the physical ST7789 display controller engine instance
    const struct device *display_dev = DEVICE_DT_GET(DISPLAY_NODE);
    
    if (!device_is_ready(display_dev)) {
        return -1; // Halt if the hardware bus isn't initialized yet
    }

    // 2. Allocate a localized pixel buffer block matching 170x320 resolution
    // Using 0xE3EC maps to a clean, warm amber/orange color value in RGB565 format
    static uint16_t pixel_buffer[170];
    for (int i = 0; i < 170; i++) {
        pixel_buffer[i] = 0xE3EC; 
    }

    // 3. Configure the structural rendering window coordinates
    struct display_capabilities caps;
    display_get_capabilities(display_dev, &caps);

    struct display_buffer_descriptor desc = {
        .buf_size = sizeof(pixel_buffer),
        .width = 170,
        .height = 1, // Write the color array stream row-by-row
        .pitch = 170,
    };

    // 4. Actively stream the warm color payload into every physical row register
    for (int y = 0; y < 320; y++) {
        display_write(display_dev, 0, y, &desc, pixel_buffer);
    }

    return 0;
}

// Automatically execute the pixel streaming routine the moment the kernel boots
SYS_INIT(initialize_test_bench_screen, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
