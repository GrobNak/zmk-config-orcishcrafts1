# Tell the Zephyr build system to compile your status screen file when display support is enabled
target_sources_ifdef(CONFIG_ZMK_DISPLAY app PRIVATE status_screen.c)
