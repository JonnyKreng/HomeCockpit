static lv_obj_t * chart;
static lv_chart_series_t * ser;

static void draw_chart()
{
  chart = lv_chart_create(lv_scr_act());

  lv_obj_set_size(chart, 100, 150);
  lv_obj_set_pos(chart, 10, 10);
  lv_obj_set_style_bg_color(chart, lv_color_make(0, 0, 0), LV_PART_MAIN);                 //Chart background color
  lv_obj_set_style_size(chart, 0, LV_PART_INDICATOR);                                     //Points on line size
  lv_obj_set_style_line_color(chart, lv_color_make(50, 50, 50), LV_STATE_DEFAULT);        //Horizontal div lines color
  lv_obj_set_style_border_color(chart, lv_color_make(50, 50, 50), LV_STATE_DEFAULT);      //Border color

  lv_chart_set_div_line_count(chart, 8, 0);
  lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
  lv_chart_set_point_count(chart, 60);
  lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_SHIFT);
  lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_X, 0, 60);
  lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, -2, 6);

  ser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
}          

static void update_chart()
{
  uint32_t i;
  for(i = 0; i < 60; i++) {
    lv_chart_set_next_value(chart, ser, (int32_t)id(chart_values)[i]);
  }
}