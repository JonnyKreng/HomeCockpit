#ifndef WEATHER_COLORS_H
#define WEATHER_COLORS_H

#include "lvgl.h"
#include <string>

static lv_color_t weather_icon_color(const std::string& condition) {
    if (condition == "rainy" || condition == "pouring" ||
        condition == "snowy-rainy" || condition == "hail") {
        return lv_color_hex(0x4FC3F7);  // blue
    }
    if (condition == "lightning" || condition == "lightning-rainy") {
        return lv_color_hex(0xFFD600);  // yellow
    }
    if (condition == "clear-night" || condition == "cloudy" || condition == "partlycloudy") {
        return lv_color_hex(0xB3E5FC);  // light blue
    }
    if(condition == "sunny") {
        return lv_color_hex(0xFFEB3B);  // bright yellow
    }
    return lv_color_hex(0xFFFFFF);  // white (fog, snowy, windy)
}

#endif // WEATHER_COLORS_H
