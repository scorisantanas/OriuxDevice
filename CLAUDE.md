# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Oriux is a DIY weather station for the ESP32-2432S028R ("Cheap Yellow Display") that displays current weather conditions, 5-day forecast, and room temperature/humidity from a DHT22 sensor. It uses LVGL for the UI and TFT_eSPI for display rendering.

## Build and Development Commands

### Building and Uploading

**Important:** Do not move the `weather/` folder into your Arduino sketchbook. Build directly from the repository location.

1. Open `weather/weather.ino` in Arduino IDE
2. Set board configuration:
   - Board: "ESP32 Dev Module"
   - Partition Scheme: "Huge App (3MB No OTA/1MB SPIFFS)"
3. Click Verify (checkmark) to compile
4. Click Upload (right arrow) to flash to device
5. Open Serial Monitor at 115200 baud for debug output

### Required Library Installation

Install exact versions through Arduino Library Manager:
- `ArduinoJson` 7.4.1
- `HttpClient` 2.2.0
- `TFT_eSPI` 2.5.43
- `WiFiManager` 2.0.17
- `XPT2046_Touchscreen` 1.4
- `lvgl` 9.2.2
- `DHT sensor library` 1.4.6
- `Adafruit Unified Sensor` 1.1.14

**Critical:** After library installation, copy config files:
- Copy `TFT_eSPI/User_Setup.h` → `~/Arduino/libraries/TFT_eSPI/User_Setup.h`
- Copy `lvgl/src/lv_conf.h` → `~/Arduino/libraries/lvgl/src/lv_conf.h`
- Restart Arduino IDE after copying

### Font Generation (Optional)

To regenerate custom fonts (requires Node.js and Python):

```bash
python FONT/font_generator.py
```

1. Edit `font_path` in `FONT/font_generator.py` to point to your font file
2. Modify `weather/required_chars.txt` for character set
3. Run the script from repository root
4. Update `LV_FONT_DECLARE` statements and `get_font_*` functions in `weather/weather.ino` if font names/sizes change

## Architecture

### Main Application Structure

**Entry Points:**
- `setup()` (line 331): Initializes hardware, WiFi, LVGL, and creates UI
- `loop()` (line 388): Runs LVGL timer tasks and handles periodic weather updates
- `create_ui()` (line 418): Constructs all LVGL UI elements
- `fetch_and_update_weather()` (line 955): Fetches data from oriux.lt API and updates display

### Hardware Configuration

**DHT22 Sensor:**
- Signal pin: GPIO 22
- Power: 3.3V
- Ground: GND

**Display Pins:**
- Defined in `TFT_eSPI/User_Setup.h`
- Using ILI9341_2_DRIVER for the ILI9341 display
- Touch controller pins hardcoded in weather.ino (lines 20-24)

**Backlight:**
- GPIO 21 (LCD_BACKLIGHT_PIN)
- PWM controlled for brightness
- Night mode: 10PM-6AM (dimmed to 0)

### Data Flow

1. **Weather Data Source:** Custom API at oriux.lt (not Open-Meteo despite some comments)
   - Current weather: `https://oriux.lt/api/weather_data_agg/{locationId}`
   - Location search: `https://oriux.lt/api/search_by_name/{query}`

2. **Data Update Cycle:**
   - Updates every 20 minutes (UPDATE_INTERVAL = 1200000ms)
   - Fetches current conditions and 5-day forecast in one call
   - Room sensor read on every display update

3. **Storage:**
   - Uses ESP32 Preferences (NVS) for persistent settings
   - Stores: locationId, location name, brightness, use_24_hour, use_night_mode, language

### UI Components (LVGL)

The UI is built with LVGL 9.2.2 and consists of:
- Main screen with current weather, 5-day forecast, and room conditions
- Settings window for configuration (brightness, time format, night mode, language)
- Location search modal with keyboard input
- Touch-based interaction

**Key LVGL Objects:**
- `lbl_today_temp`: Current temperature display
- `img_today_icon`: Current weather icon
- `lbl_room_temp`, `lbl_room_humidity`: DHT22 sensor readings
- `box_daily`: Container for 5-day forecast cards
- `settings_win`: Settings modal window
- `location_win`: Location search modal

### Asset Management

**Weather Icons and Images:**
- Pre-converted to C arrays (`icon_*.c` and `image_*.c` files in `weather/`)
- Embedded directly in firmware using `LV_IMG_DECLARE` macros
- Icon mapping done in `choose_icon()` and `choose_image()` functions based on condition codes

**Fonts:**
- Custom font: Typo Grotesk Rounded
- Pre-rendered as C arrays (`lv_font_typo_grotesk_rounded_*.c`)
- Sizes: 12, 14, 16, 20, 42 point
- Includes Latin Extended-A characters for Lithuanian language support

### Internationalization

**Language Support:**
- English (LANG_EN) and Lithuanian (LANG_LT)
- Implemented via `translations.h` with `LocalizedStrings` struct
- Helper function `get_strings(Language)` returns appropriate string set
- Language setting persists in Preferences

### Night Mode

**Automatic Screen Dimming:**
- Active between 22:00-06:00 (NIGHT_MODE_START_HOUR/END_HOUR)
- Turns backlight to 0 when active
- Temporary wake on touch interaction (30-second timer)
- User can disable night mode in settings

## Development Notes

### Memory Considerations

- ESP32 "Huge App" partition scheme required (3MB app / 1MB SPIFFS)
- LVGL draw buffer: SCREEN_WIDTH * SCREEN_HEIGHT / 10
- Large JSON documents: 32KB for weather, 8KB for geocoding
- Font and image assets consume significant flash space

### First Boot Behavior

Device creates WiFi AP named "Oriux" on first boot. Users connect to this network and configure WiFi credentials via captive portal (WiFiManager library handles this automatically).

### Known Patterns

- Single-threaded architecture (no RTOS, LV_USE_RTOS = 0)
- Event-driven UI updates via LVGL callbacks
- Global state variables for UI components and settings
- HTTP requests are blocking (no async operations)
- Time sync via NTP servers after timezone configuration

### Testing

No automated test suite. Manual testing by flashing device and verifying:
- WiFi captive portal functionality
- Weather data display updates
- Touch interaction responsiveness
- Settings persistence across reboots
- DHT22 sensor readings
- Night mode behavior
