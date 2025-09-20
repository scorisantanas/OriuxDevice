#ifndef TRANSLATIONS_H
#define TRANSLATIONS_H

// Language support
enum Language { LANG_EN = 0, LANG_LT = 1 };

struct LocalizedStrings {
  const char* temp_placeholder;
  const char* feels_like_temp;
  const char* five_day_forecast;
  const char* room_temp;
  const char* room_humidity;
  const char* hourly_forecast;
  const char* today;
  const char* now;
  const char* am;
  const char* pm;
  const char* noon;
  const char* invalid_hour;
  const char* brightness;
  const char* location;
  const char* use_24hr;
  const char* save;
  const char* cancel;
  const char* close;
  const char* location_btn;
  const char* reset_wifi;
  const char* reset;
  const char* change_location;
  const char* weather_settings;
  const char* city;
  const char* search_results;
  const char* city_placeholder;
  const char* wifi_config;
  const char* reset_confirmation;
  const char* language_label;
  const char* weekdays[7];
  const char* use_night_mode;
};

#define DEFAULT_CAPTIVE_SSID "Oriux"

static const LocalizedStrings strings_en = {
  "--°C", "Feels Like", "FIVE DAY FORECAST",
  "Current room temp", "Current room humidity", "HOURLY FORECAST",
  "Today", "Now", "AM", "PM", "Noon", "Invalid hour",
  "Brightness:", "Location:", "24hr:",
  "Save", "Cancel", "Close", "Location", "Reset Wi-Fi",
  "Reset", "Change Location", "Oriux Settings",
  "City:", "Search Results", "e.g. London",
  "Wi-Fi Configuration:\n\n"
  "Please connect your\n"
  "phone or laptop to the\n"
  "temporary Wi-Fi access\n point "
  DEFAULT_CAPTIVE_SSID
  "\n"
  "to configure.\n\n"
  "If you don't see a \n"
  "configuration screen \n"
  "after connecting,\n"
  "visit http://192.168.4.1\n"
  "in your web browser.",
  "Are you sure you want to reset "
  "Wi-Fi credentials?\n\n"
  "You'll need to reconnect to the Wifi SSID " DEFAULT_CAPTIVE_SSID
  " with your phone or browser to "
  "reconfigure Wi-Fi credentials.",
  "Language:",
  {"Sun", "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat"},
  "Dim screen at night"
};

static const LocalizedStrings strings_lt = {
  "--°C", "Jaučiasi kaip", "5 DIENŲ PROGNOZĖ",
  "Kambario temperatūra", "Kambario drėgmė", "VALANDINĖ PROGNOZĖ",
  "Šiandien", "Dabar", "AM", "PM", "Vidurdienis", "Neteisinga valanda",
  "Ryškumas:", "Vieta:", "24 val. formatas:",
  "Išsaugoti", "Atšaukti", "Uždaryti", "Vieta", "Atstatyti Wi-Fi",
  "Atstatyti", "Keisti vietą", "Oriux Nustatymai",
  "Miestas:", "Paieškos rezultatai", "pvz., Vilnius",
  "Wi-Fi Konfigūracija:\n\nPrijunkite savo telefoną\narba kompiuterį prie laikinojo\nWi-Fi prieigos taško\n"
  DEFAULT_CAPTIVE_SSID
  "\nkad sukonfigūruotumėte.\n\nJei po prisijungimo nematote\nkonfigūracijos ekrano,\napsilankykite http://192.168.4.1\nsavo naršyklėje.",
  "Ar tikrai norite atstatyti\nWi-Fi prisijungimo duomenis?\n\nJums reikės iš naujo prisijungti prie\nSSID " DEFAULT_CAPTIVE_SSID
  "\nsu savo telefonu ar naršykle,\nkad iš naujo sukonfigūruotumėte\nWi-Fi prisijungimo duomenis.",
  "Kalba:",
  {"Sek", "Pir", "Ant", "Tre", "Ket", "Pen", "Šeš"},
  "Tamsus režimas naktį"
};

static const LocalizedStrings* get_strings(Language current_language) {
  switch (current_language) {
    case LANG_LT: return &strings_lt;
    default: return &strings_en;
  }
}

#endif // TRANSLATIONS_H