#ifndef THEME_H
#define THEME_H

#include "lvgl.h"

// Colors from global.yaml
#define BACKGROUND_COLOR    lv_color_make(0x00, 0x00, 0x00)    // 0x000000
#define PRIMARY_COLOR       lv_color_make(0x31, 0x31, 0x31)    // 0x313131
#define HIGHLIGHT_COLOR     lv_color_make(0xFF, 0x8C, 0x00)    // 0xFF8C00 (Orange)
#define TEXT_COLOR          lv_color_make(0xFF, 0xFF, 0xFF)    // 0xFFFFFF

// Grid colors (complementary)
#define GRID_COLOR          lv_color_make(0x32, 0x32, 0x32)    // 0x323232 (slightly lighter than primary)

#endif // THEME_H
