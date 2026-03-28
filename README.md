# Initial setup from 
https://github.com/jtenniswood/esphome-lvgl

# Guition ESP32-P4 JC1060P470 (7")

7-inch touch LCD panel with ESP32-P4, running ESPHome and LVGL for home automation and sensor displays.

![Guition ESP32-P4 JC1060P470](../images/guition-esp32-p4-jc1060p470.jpg)

## Configuration

- **Template**: [homeCockpit.yaml](homeCockpit.yaml) — use the **contents of this file as your ESPHome config** in the dashboard or CLI (create or edit your device config so it matches this file).

## Stand

- **Desk mount** (3D printable): [MakerWorld](https://makerworld.com/en/models/2387421-guition-esp32p4-jc1060p470-7inch-screen-desk-mount#profileId-2614995)

## Folder Structure

```
guition-esp32-p4-jc1060p470/
├── addon/              # Time, network, backlight
├── assets/             # Fonts and icons
├── device/             # device.yaml, sensors.yaml, lvgl.yaml
├── theme/              # Button and UI styling
└── homeCockpit.yaml    # ESPHome config template
```

Customize for your setup by editing the YAML files under `device/`, `addon/`, and `theme/`. See the [main README](../README.md) for full quick start and ESPHome setup.
