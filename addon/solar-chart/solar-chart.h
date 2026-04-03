#pragma once
#include "theme.h"
#include "chart.h"

static Chart chart_home_instance;
static Chart chart_solar_instance;

static void DrawCallbackEvent(lv_event_t* e)
{
    lv_obj_draw_part_dsc_t* dsc = lv_event_get_draw_part_dsc(e);

    if (!lv_obj_draw_part_check_type(dsc, &lv_chart_class, LV_CHART_DRAW_PART_TICK_LABEL))
        return;
    if (dsc->text == NULL)
        return;

    if (dsc->id == LV_CHART_AXIS_PRIMARY_X)
    {
        uint value = 24 - ((dsc->value) * 2);
        if(value == 0)
          lv_snprintf(dsc->text, dsc->text_length, "now");
        else
          lv_snprintf(dsc->text, dsc->text_length, "-%d", value);
    }
    else if (dsc->id == LV_CHART_AXIS_PRIMARY_Y)
    {
        lv_snprintf(dsc->text, dsc->text_length, "%d%", dsc->value);
    }
}

static Chart draw_solar_chart(lv_obj_t * parent = NULL)
{
  return draw_chart(398, 324, 288, 800, 13, 9, DrawCallbackEvent, parent);
}
