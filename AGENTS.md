# HomeCockpit

ESPHome + LVGL config for a **Guition ESP32-P4 JC1060P470** (7" touch LCD panel).

## Entrypoints

- `homeCockpit.yaml` — template config (substitute `name`/`friendly_name`, includes via GitHub URL)
- `homeCockpit.local.yaml` — local dev variant (includes `package.yaml` directly)
- `package.yaml` — composition root, `!include`s all packages

## Structure

| Directory | Contents |
|-----------|----------|
| `device/` | ESP32-P4 hardware config (`device.yaml`), sensors, LVGL pages/tabs |
| `device/dashboards/` | Tab content: `home.yaml`, `solar.yaml`, `car.yaml`, `settings.yaml`, `heating.yaml` (disabled) |
| `addon/` | Feature packages: time, weather, people, car charging, heating, solar-chart |
| `theme/` | `global.yaml` (colors/sizes), `button.yaml`, `container.yaml` |
| `assets/` | Fonts (Roboto via Google Fonts) and Material Design icons (v7.4.47) |
| `addon/script-extensions/` | C/C++ helpers: `chart.h`, `theme.h`, `weather_colors.h` |

## Commands

```sh
esphome run homeCockpit.yaml         # compile + upload to device
esphome compile homeCockpit.yaml     # compile only
esphome logs homeCockpit.yaml        # view device logs
esphome run homeCockpit.local.yaml   # local overrides variant
```

## Key details

- **Build framework**: ESP-IDF, ESP32-P4, 16MB flash, 360MHz, PSRAM in octal DTR mode
- **Display**: MIPI DSI, model JC1060P470, `update_interval: never` + `auto_clear_enabled: false`
- **Touch**: GT911 on I2C bus A, drives inactivity timer
- **Second chip**: ESP32-C6 for connectivity via `esp32_hosted` (shared SPI)
- **LVGL component**: pulled from `github://pr#16362` — temporary workaround in `package.yaml`
- **Theme**: colors defined via ESPHome `substitutions` in `theme/global.yaml`, injected as C `build_flags` macros (`THEME_BACKGROUND`, etc.)
- **Secrets**: `secrets.yaml` is gitignored; contains Wi-Fi, API, OTA passwords. Do not commit changes to it.
- **Charts**: custom C `draw_chart()`/`update_chart()` in `addon/script-extensions/chart.h` using LVGL scales
- **Backlight**: inactivity timer (60s) pauses LVGL, shows snow; presence sensor in `addon/backlight.yaml` resumes it via HA `binary_sensor.office_presence_group`
- **Heating tab** (`device/dashboards/heating.yaml`) and `addon/heating.yaml` exist but are commented out in `device/lvgl.yaml` and `package.yaml`
- **No tests, no CI, no linter/formatter** — all ESPHome YAML compiled by `esphome`
