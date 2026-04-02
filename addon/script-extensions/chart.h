static lv_obj_t * chart;
static lv_chart_series_t * ser;

#include "theme.h"


static void DrawCallbackEvent(lv_event_t* e)
{
    //Get the event descriptor
    lv_obj_draw_part_dsc_t* dsc = lv_event_get_draw_part_dsc(e);

    //Check what part we are updating. Only proceed if we are updating one of the tick label(s)
    if (!lv_obj_draw_part_check_type(dsc, &lv_chart_class, LV_CHART_DRAW_PART_TICK_LABEL))
        return;

    //Check this is a callback for a major tick (minor ticks have 0 here)
    if (dsc->text == NULL)
        return;

    //If we are editing the Y axis
    if (dsc->id == LV_CHART_AXIS_PRIMARY_X)
    {
        uint value = 24 - ((dsc->value) * 2);
        if(value == 0) {
          lv_snprintf(dsc->text, dsc->text_length, "now");
        }
        else {
          lv_snprintf(dsc->text, dsc->text_length, "-%d", value);
        }
    }
    else if (dsc->id == LV_CHART_AXIS_PRIMARY_Y)
    {
        lv_snprintf(dsc->text, dsc->text_length, "%d%", dsc->value);
    }
}

static void draw_chart(lv_obj_t * parent = NULL)
{
  const u_int X_HEIGHT = 410;
  const u_int Y_HEIGHT = 270;

  const u_int MAX_X_POINTS = 288;       // Number of data points (288 x 5-min = 24 hours)
  const u_int MAX_POWER_WATTS = 800;    // Solar panel max power in watts

  const u_int X_GRID_LINES = 13;        // Hourly grid lines
  const u_int Y_GRID_LINES = 9;         // Power grid lines (100W intervals)

  // Create container slightly larger than the chart
  lv_obj_t * container;
  if(parent == NULL) {
    container = lv_obj_create(lv_scr_act());
  }
  else {
    container = lv_obj_create(parent);
  }

  lv_obj_set_size(container, X_HEIGHT, Y_HEIGHT);
  lv_obj_set_style_bg_color(container, PRIMARY_COLOR, LV_PART_MAIN);
  lv_obj_set_style_border_width(container, 0, LV_PART_MAIN);
  lv_obj_set_style_pad_all(container, 14, LV_PART_MAIN);

  // Create chart inside container
  chart = lv_chart_create(container);
  lv_obj_align(chart, LV_ALIGN_TOP_RIGHT, 0, 0);

  lv_obj_set_size(chart, X_HEIGHT - 55, Y_HEIGHT - 40);
  lv_obj_set_style_bg_color(chart, BACKGROUND_COLOR, LV_PART_MAIN);                 // Chart background color
  lv_obj_set_style_size(chart, 0, LV_PART_INDICATOR);                                     // Points on line size
  lv_obj_set_style_line_color(chart, PRIMARY_COLOR, LV_STATE_DEFAULT);        // Grid lines color
  //lv_obj_set_style_border_color(chart, PRIMARY_COLOR, LV_STATE_DEFAULT);      // Border color
  lv_obj_set_style_border_width(chart, 0, LV_PART_MAIN);
  
  lv_chart_set_div_line_count(chart, Y_GRID_LINES, X_GRID_LINES);
  lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
  lv_chart_set_point_count(chart, MAX_X_POINTS);
  lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_SHIFT);
  lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_X, 0, MAX_X_POINTS);
  lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, MAX_POWER_WATTS);

  // Add Y-axis labels (Power in Watts: 0, 200, 400, 600, 800)
  lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 0, Y_GRID_LINES, 1, true, 50);

  // Add X-axis labels (showing every 6 hours: 0, 6, 12, 18, 24)
  lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_X, 0, 0, X_GRID_LINES , 2, true, 50);

  // Callback to get the labesl text for the X and Y axis ticks
  lv_obj_add_event_cb(chart, DrawCallbackEvent, LV_EVENT_DRAW_PART_BEGIN, NULL);

  ser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_ORANGE), LV_CHART_AXIS_PRIMARY_Y);

  // Initialize chart with zeros
  //for(u_int i = MAX_X_POINTS; i > 0; i--) {
  //   lv_chart_set_next_value(chart, ser, 0);
  //}
}          

static void update_chart(float value)
{
  lv_chart_set_next_value(chart, ser, value);
}