#pragma once

MCUFRIEND_kbv tft;
DHT dht(DHTPIN, DHTTYPE);
DS3231 ds3231;

TouchScreen ts = TouchScreen(6, A1, A2, 7, 330);
TSPoint tp;
