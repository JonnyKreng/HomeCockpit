#pragma once
#include "theme.h"

struct Chart {
  lv_obj_t *           chart;
  lv_chart_series_t *  ser;
  lv_obj_t *           x_scale;
  lv_obj_t *           y_scale;
  char **              x_labels;
};

static void update_chart_time(Chart &instance)
{
  auto current_time = id(sntp_time).now();
  if (!current_time.is_valid()) {
    return;
  }

  int x_grid_lines = lv_scale_get_total_tick_count(instance.x_scale);
  int current_hour = current_time.hour;
  int current_minute = current_time.minute;

  for (int i = 0; i < x_grid_lines; i++) {
    int tick_hour = (current_hour + (i * 2)) % 24;
    if(x_grid_lines == i + 1) {
      lv_snprintf(instance.x_labels[i], 16, "%02d\n%02d", tick_hour, current_minute);
    }
    else {
      lv_snprintf(instance.x_labels[i], 16, "%02d", tick_hour, current_minute);
    }
  }
  lv_obj_invalidate(instance.x_scale);
}

static Chart draw_chart(
  u_int width,
  u_int height,
  u_int max_x_value,
  u_int max_y_value,
  u_int x_grid_lines,
  u_int y_grid_lines,
  lv_obj_t * parent = NULL
)
{
  lv_obj_t * container;
  if(parent == NULL)
    container = lv_obj_create(lv_screen_active());
  else
    container = lv_obj_create(parent);

  lv_obj_set_size(container, width, height);
  lv_obj_set_style_bg_color(container, PRIMARY_COLOR, LV_PART_MAIN);
  lv_obj_set_style_border_width(container, 0, LV_PART_MAIN);
  lv_obj_set_style_pad_all(container, 14, LV_PART_MAIN);

  int pad = 14;
  int inner_width = width - (pad * 2);
  int inner_height = height - (pad * 2);

  int y_scale_width = 55;
  int x_scale_height = 30;

  int chart_width = inner_width - y_scale_width;
  int chart_height = inner_height - x_scale_height;

  int chart_pad_hor = 10;
  int chart_pad_ver = 10;

  Chart instance;
  instance.chart = lv_chart_create(container);
  lv_obj_align(instance.chart, LV_ALIGN_TOP_RIGHT, 0, 0);
  lv_obj_set_size(instance.chart, chart_width, chart_height);
  lv_obj_set_style_bg_color(instance.chart, BACKGROUND_COLOR, LV_PART_MAIN);
  lv_obj_set_style_size(instance.chart, 0, 0, LV_PART_INDICATOR);
  lv_obj_set_style_line_color(instance.chart, PRIMARY_COLOR, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(instance.chart, 0, LV_PART_MAIN);
  
  // Align chart plot area padding
  lv_obj_set_style_pad_left(instance.chart, chart_pad_hor, LV_PART_MAIN);
  lv_obj_set_style_pad_right(instance.chart, chart_pad_hor, LV_PART_MAIN);
  lv_obj_set_style_pad_top(instance.chart, chart_pad_ver, LV_PART_MAIN);
  lv_obj_set_style_pad_bottom(instance.chart, chart_pad_ver, LV_PART_MAIN);

  lv_chart_set_div_line_count(instance.chart, y_grid_lines, x_grid_lines);
  lv_chart_set_type(instance.chart, LV_CHART_TYPE_LINE);
  lv_chart_set_point_count(instance.chart, max_x_value);
  lv_chart_set_update_mode(instance.chart, LV_CHART_UPDATE_MODE_SHIFT);
  lv_chart_set_range(instance.chart, LV_CHART_AXIS_PRIMARY_X, 0, max_x_value);
  lv_chart_set_range(instance.chart, LV_CHART_AXIS_PRIMARY_Y, 0, max_y_value);

  // Y-axis Scale on the left
  instance.y_scale = lv_scale_create(container);
  lv_scale_set_mode(instance.y_scale, LV_SCALE_MODE_VERTICAL_LEFT);
  lv_obj_set_size(instance.y_scale, y_scale_width, chart_height);
  lv_obj_align(instance.y_scale, LV_ALIGN_TOP_LEFT, 0, 0);
  lv_scale_set_total_tick_count(instance.y_scale, y_grid_lines);
  lv_scale_set_major_tick_every(instance.y_scale, 1);
  lv_scale_set_label_show(instance.y_scale, true);
  lv_scale_set_range(instance.y_scale, 0, max_y_value);
  
  // Align Y-scale ticks vertically to match chart padding
  lv_obj_set_style_pad_top(instance.y_scale, chart_pad_ver, LV_PART_MAIN);
  lv_obj_set_style_pad_bottom(instance.y_scale, chart_pad_ver, LV_PART_MAIN);
  lv_obj_set_style_pad_left(instance.y_scale, 0, LV_PART_MAIN);
  lv_obj_set_style_pad_right(instance.y_scale, 0, LV_PART_MAIN);
  
  // Style Y-axis Scale
  lv_obj_set_style_line_color(instance.y_scale, PRIMARY_COLOR, LV_PART_MAIN);
  lv_obj_set_style_line_color(instance.y_scale, PRIMARY_COLOR, LV_PART_ITEMS);
  lv_obj_set_style_line_color(instance.y_scale, PRIMARY_COLOR, LV_PART_INDICATOR);
  lv_obj_set_style_text_color(instance.y_scale, TEXT_COLOR, LV_PART_INDICATOR);

  // Generate Y-axis labels dynamically (bottom-to-top)
  char ** y_labels = new char*[y_grid_lines + 1];
  for (u_int i = 0; i < y_grid_lines; i++) {
    int val = (max_y_value * i) / (y_grid_lines - 1);
    y_labels[i] = new char[16];
    lv_snprintf(y_labels[i], 16, "%d W", val);
  }
  y_labels[y_grid_lines] = NULL;
  lv_scale_set_text_src(instance.y_scale, (const char **)y_labels);

  // X-axis Scale at the bottom
  instance.x_scale = lv_scale_create(container);
  lv_scale_set_mode(instance.x_scale, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
  lv_obj_set_size(instance.x_scale, chart_width, x_scale_height);
  lv_obj_align(instance.x_scale, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
  lv_scale_set_total_tick_count(instance.x_scale, x_grid_lines);
  lv_scale_set_major_tick_every(instance.x_scale, 1);
  lv_scale_set_label_show(instance.x_scale, true);
  
  // Align X-scale ticks horizontally to match chart padding
  lv_obj_set_style_pad_left(instance.x_scale, chart_pad_hor, LV_PART_MAIN);
  lv_obj_set_style_pad_right(instance.x_scale, chart_pad_hor, LV_PART_MAIN);
  lv_obj_set_style_pad_top(instance.x_scale, 0, LV_PART_MAIN);
  lv_obj_set_style_pad_bottom(instance.x_scale, 0, LV_PART_MAIN);

  // Style X-axis Scale
  lv_obj_set_style_line_color(instance.x_scale, PRIMARY_COLOR, LV_PART_MAIN);
  lv_obj_set_style_line_color(instance.x_scale, PRIMARY_COLOR, LV_PART_ITEMS);
  lv_obj_set_style_line_color(instance.x_scale, PRIMARY_COLOR, LV_PART_INDICATOR);
  lv_obj_set_style_text_color(instance.x_scale, TEXT_COLOR, LV_PART_INDICATOR);

  // Generate X-axis labels dynamically
  instance.x_labels = new char*[x_grid_lines + 1];
  for (u_int i = 0; i < x_grid_lines; i++) {
    instance.x_labels[i] = new char[16];
    uint value = 24 - (i * 2);
    if (value == 0) {
      lv_snprintf(instance.x_labels[i], 16, "now");
    } else {
      lv_snprintf(instance.x_labels[i], 16, "-%d", value);
    }
  }
  instance.x_labels[x_grid_lines] = NULL;
  lv_scale_set_text_src(instance.x_scale, (const char **)instance.x_labels);

  instance.ser = lv_chart_add_series(instance.chart, lv_palette_main(LV_PALETTE_ORANGE), LV_CHART_AXIS_PRIMARY_Y);

  for(u_int i = max_x_value; i > 0; i--)
    lv_chart_set_next_value(instance.chart, instance.ser, 0);

  update_chart_time(instance);
  return instance;
}

static void update_chart(Chart &instance, float value)
{
  lv_chart_set_next_value(instance.chart, instance.ser, value);
  update_chart_time(instance);
}