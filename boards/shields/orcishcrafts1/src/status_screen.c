#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <zephyr/init.h>

// Match the display target node handle directly
#define DISPLAY_NODE DT_NODELABEL(display)

static int force_amber_bench_stream(void) {
    // 1. Grab the raw initialized hardware driver pointer from the kernel core
    const struct device *display_dev = DEVICE_DT_GET(DISPLAY_NODE);
    
    if (!display_dev || !device_is_ready(display_dev)) {
        return -1; // Fail out if the SPI core didn't wake up
    }

    // 2. Prepare a 170-pixel wide color buffer line mapped to Warm Amber (0xE3EC in RGB565)
    static uint16_t row_buffer[170];
    for (int i = 0; i < 170; i++) {
        row_buffer[i] = 0xE3EC;
    }

    // 3. Define a single-row pixel buffer descriptor
    struct display_buffer_descriptor desc = {
        .buf_size = sizeof(row_buffer),
        .width = 170,
        .height = 1,
        .pitch = 170,
    };

    // 4. Pump raw amber pixels into every single row of the 320 vertical grid lines
    for (int y = 0; y < 320; y++) {
        display_write(display_dev, 0, y, &desc, row_buffer);
    }

    return 0;
}

// Register this routine to fire immediately during the application boot stage
SYS_INIT(force_amber_bench_stream, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

// Satisfy ZMK Studio linker requirements with an empty wrapper stub
void *zmk_display_status_screen(void) {
    return NULL;
}
