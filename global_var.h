#pragma once

uint8_t spi_save;
PAGE currentPage = PAGE::HOME;
uint8_t subPage1 = 1, subPage4 = 1, subPage6 = 1;
bool connection_WIFI = false;
bool connection_DS3231 = false;
bool connection_DHT22 = false;

uint8_t year;
uint8_t month;
uint8_t day;
uint8_t weekDay;
uint8_t hour;
uint8_t minute;
uint8_t second;

uint8_t list_day;
uint8_t list_month;
uint8_t list_year;

bool century = false;
bool h12Flag;
bool pmFlag;

String weekDays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
String monthList[] = {"January", "February", "March",  "April", "May", "June", "July", "August", "September", "October", "November", "December"};
uint8_t dayInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

uint8_t a1_status_reg;// 7 - on/off, 6 - 0 on/off day of week
uint8_t a1_hour;
uint8_t a1_minute;

uint8_t hourTempLog[60], hourHumLog[60];
float temperature;
float humidity;

int8_t temperature_low, temperature_high;
int8_t humidity_low, humidity_high;

bool ds3231Check = false;
bool dht22Check = false;
bool dht22Counter60sec = false;
bool sdCheck = false;

uint8_t page_6_value = 90;
//uint8_t page_6_total = 0;
