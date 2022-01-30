#include "libs.h"
#include "define.h"

#include "global_object.h"
#include "global_var.h"

// TFT Breakout  -- Arduino UNO / Mega2560 / OPEN-SMART UNO Black
// GND              -- GND
// 3V3               -- 3.3V
// CS                 -- A3
// RS                 -- A2
// WR                -- A1
// RD                 -- A0
// RST                -- RESET
// LED                -- GND
// DB0                -- 8
// DB1                -- 9
// DB2                -- 10
// DB3                -- 11
// DB4                -- 4
// DB5                -- 13
// DB6                -- 6
// DB7                -- 7

void setup(void) 
{
    pinMode(DHTVCC, OUTPUT);
    digitalWrite(DHTVCC, HIGH);
    pinMode(DHTGND, OUTPUT);
    digitalWrite(DHTGND, LOW);

    pinMode(ALARMGND, OUTPUT);
    digitalWrite(ALARMGND, LOW);
    
    Serial.begin(9600);
    Wire.begin();
    dht.begin();
    SD.begin(SD_CS);
    tft.begin(0x9329);
    tft.reset();
    
    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(0);

    a1_status_reg = eeprom_read_byte(A1_REG);
    a1_hour = eeprom_read_byte(A1_H);
    a1_minute = eeprom_read_byte(A1_M);

    temperature_low = eeprom_read_byte(T_LOW);
    temperature_high = eeprom_read_byte(T_HIGH);
    humidity_low = eeprom_read_byte(H_LOW);
    humidity_high = eeprom_read_byte(H_HIGH);
    
    bmpDraw("menu.bmp", 0, 200);
    pageSelect();
    menuSelect();

    readDS3231();

    memset(hourTempLog, 0xFF, 60);
    memset(hourHumLog, 0xFF, 60);
    
    TCCR5A = (0 << COM5A1) | (0 << COM5A0) |/* (0 << COM5B0) | (0 << COM5B1) | (0 << COM5C0) | (0 << COM5C0) | */
             (0 << WGM51) | (0 << WGM50);
    TCCR5B = (0 << ICNC5) | (0 << ICES5) | (0 << WGM53) | (1 << WGM52) | (1 << CS52) | (0 << CS51) | (1 << CS50);
  
    TCNT5 = 0;
    OCR5A = 0x3D09;
    TIMSK5 = (1 << OCIE5A);
}

void loop(void) 
{           
  tp = ts.getPoint();
  pinMode(A2, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) 
    goto MARKER;

  //Выбор страницы - меню
  if(tp.x > 810)
    touch_select_page();
  else if(currentPage == PAGE::SETTING)
    touch_setting_page();
  else if(currentPage == PAGE::ALARM)
   touch_alarm_page();
  else if(currentPage == PAGE::DIAGRAM)
    touch_diagram_page();
  else if(currentPage == PAGE::FEEDING)
    touch_feeding_page();

  //debug
  tft.setTextSize(0);
  tft.setCursor(0, 0);
  tft.setTextColor(TFT_COLOR::WHITE, TFT_COLOR::BLACK);
  tft.println("tp.x=" + String(tp.x));
  tft.println("tp.y=" + String(tp.y));
  tft.println("tp.z=" + String(tp.z));

MARKER: 
  if(dht22Check)
  {
    dht22Check = false;
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) 
      connection_DHT22 = false;
    else
    {
      connection_DHT22 = true;

      if(dht22Counter60sec)
      {
        dht22Counter60sec = false;
        
        temperature = dht22_values(temperature, 35, -15);
        humidity = dht22_values(humidity, 100, 0);
          
        hourTempLog[minute] = temperature + 0.5;
        hourHumLog[minute] = humidity + 0.5;
        
        if((minute == 0) || (minute == 30))
        {
          File file = SD.open("meteo/" + dateStringWithoutDot(day, month, year), FILE_WRITE);
          if(file)
          {
            //3600 / 30 = 120
            //264 / 12 = 22 (пикселя на ячейку)
            //120 / 30 = 4 (значения на ячейку, 0, 30, 60, 90)
            //22 / 4 = 5,5 (шаг для 30 минут)
            file.write((hour * 60 + minute) / 30 );
            file.write((26 + 16 * 7) - static_cast<uint8_t>((temperature + 0.5) * 3.2));
            file.write(186 - static_cast<uint8_t>((humidity + 0.5) * 1.6));
            file.close();
          }
        }

        if(currentPage == PAGE::DIAGRAM)
        {
          clearPage();
          page_4_Draw();
        }
      }
    }
  }
  
  if(ds3231Check)
  {
    readDS3231();
  
    if(currentPage == PAGE::HOME)
      page_0_Draw_data();
    else if(currentPage == PAGE::SETTING && subPage1 == 1)
      page_1_Draw_data(); 

    draw_statusPanel();
    ds3231Check = false;
  }
}
