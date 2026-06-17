#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/mipi_dbi.h>
#include <zmk/display.h>
#include <lvgl.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(custom_screen, LOG_LEVEL_INF);

// Look up the parent MIPI DBI interface device node
#define MIPI_NODE DT_NODELABEL(mipi_dbi0)

static void send_raw_cmd(const struct device *mipi_dev, uint8_t cmd, const uint8_t *data, size_t len) {
    struct mipi_dbi_config config = {
        .mode = MIPI_DBI_MODE_SPI_4WIRE,
        .config.spi_config = {
            .frequency = 24000000,
            .operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(8) | SPI_MODE_CPOL | SPI_MODE_CPHA,
        },
    };
    mipi_dbi_command_write(mipi_dev, &config, cmd, data, len);
}

lv_obj_t *zmk_display_status_screen() {
    const struct device *mipi_dev = DEVICE_DT_GET(DT_PARENT(DT_NODELABEL(display)));

    if (device_is_ready(mipi_dev)) {
        LOG_INF("Manually awakening ST7789 chip registers...");
        
        // 1. Software Reset
        send_raw_cmd(mipi_dev, 0x01, NULL, 0); 
        k_msleep(150);

        // 2. Sleep Out
        send_raw_cmd(mipi_dev, 0x11, NULL, 0); 
        k_msleep(150);

        // 3. Interface Pixel Format (16-bit color / RGB565)
        uint8_t colmod_val = 0x55;
        send_raw_cmd(mipi_dev, 0x3A, &colmod_val, 1);

        // 4. Memory Data Access Control (Native Portrait orientation)
        uint8_t mdac_val = 0x00;
        send_raw_cmd(mipi_dev, 0x36, &mdac_val, 1);

        // 5. Display Inversion ON (Required for normal colors on these modules)
        send_raw_cmd(mipi_dev, 0x21, NULL, 0);

        // 6. Main Display ON
        send_raw_cmd(mipi_dev, 0x29, NULL, 0);
        k_msleep(50);
    }

    // Initialize the graphics canvas layer
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_size(screen, 170, 320);
    lv_obj_set_pos(screen, 0, 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    
    // Paint canvas layer with your warm amber color (Hex: 0xE67E22)
    lv_obj_set_style_bg_color(screen, lv_color_hex(0xE67E22), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    
    return screen;
}
