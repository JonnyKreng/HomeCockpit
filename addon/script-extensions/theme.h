#ifndef THEME_H
#define THEME_H

#include "lvgl.h"

// Colors are defined via build_flags from theme/global.yaml
#define BACKGROUND_COLOR    lv_color_hex(THEME_BACKGROUND)
#define PRIMARY_COLOR       lv_color_hex(THEME_PRIMARY)
#define HIGHLIGHT_COLOR     lv_color_hex(THEME_HIGHLIGHT)
#define TEXT_COLOR          lv_color_hex(THEME_TEXT)

// Grid color: slightly lighter than primary
#define GRID_COLOR          lv_color_hex(THEME_PRIMARY)

#endif // THEME_H
