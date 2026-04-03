#pragma once
#include "theme.h"

struct Chart {
  lv_obj_t *           chart;
  lv_chart_series_t *  ser;
};

static Chart draw_chart(
  u_int width,
  u_int height,
  u_int max_x_value,
  u_int max_y_value,
  u_int x_grid_lines,
  u_int y_grid_lines,
  void (*fptr)(lv_event_t* e),
  lv_obj_t * parent = NULL
)
{
  lv_obj_t * container;
  if(parent == NULL)
    container = lv_obj_create(lv_scr_act());
  else
    container = lv_obj_create(parent);

  lv_obj_set_size(container, width, height);
  lv_obj_set_style_bg_color(container, PRIMARY_COLOR, LV_PART_MAIN);
  lv_obj_set_style_border_width(container, 0, LV_PART_MAIN);
  lv_obj_set_style_pad_all(container, 14, LV_PART_MAIN);

  Chart instance;
  instance.chart = lv_chart_create(container);
  lv_obj_align(instance.chart, LV_ALIGN_TOP_RIGHT, 0, 0);
  lv_obj_set_size(instance.chart, width - 55, height - 40);
  lv_obj_set_style_bg_color(instance.chart, BACKGROUND_COLOR, LV_PART_MAIN);
  lv_obj_set_style_size(instance.chart, 0, LV_PART_INDICATOR);
  lv_obj_set_style_line_color(instance.chart, PRIMARY_COLOR, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(instance.chart, 0, LV_PART_MAIN);

  lv_chart_set_div_line_count(instance.chart, y_grid_lines, x_grid_lines);
  lv_chart_set_type(instance.chart, LV_CHART_TYPE_LINE);
  lv_chart_set_point_count(instance.chart, max_x_value);
  lv_chart_set_update_mode(instance.chart, LV_CHART_UPDATE_MODE_SHIFT);
  lv_chart_set_range(instance.chart, LV_CHART_AXIS_PRIMARY_X, 0, max_x_value);
  lv_chart_set_range(instance.chart, LV_CHART_AXIS_PRIMARY_Y, 0, max_y_value);
  lv_chart_set_axis_tick(instance.chart, LV_CHART_AXIS_PRIMARY_Y, 0, 0, y_grid_lines, 1, true, 50);
  lv_chart_set_axis_tick(instance.chart, LV_CHART_AXIS_PRIMARY_X, 0, 0, x_grid_lines, 2, true, 50);
  lv_obj_add_event_cb(instance.chart, fptr, LV_EVENT_DRAW_PART_BEGIN, NULL);

  instance.ser = lv_chart_add_series(instance.chart, lv_palette_main(LV_PALETTE_ORANGE), LV_CHART_AXIS_PRIMARY_Y);

  for(u_int i = max_x_value; i > 0; i--)
    lv_chart_set_next_value(instance.chart, instance.ser, 0);

  return instance;
}

static void update_chart(Chart &instance, float value)
{
  lv_chart_set_next_value(instance.chart, instance.ser, value);
}
