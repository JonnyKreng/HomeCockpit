#pragma once
#include "theme.h"
#include "chart.h"

static Chart chart_home_instance;
static Chart chart_solar_instance;

static Chart draw_solar_chart(lv_obj_t * parent = NULL)
{
  return draw_chart(398, 324, 288, 800, 13, 9, parent);
}
