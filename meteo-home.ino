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
//  
//    sei();
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
  {
      PAGE page = PAGE::HOME;
      if(tp.y < 940 && tp.y > 875)
          page = PAGE::HOME;
      else if(tp.y < 875 && tp.y > 775)
          page = PAGE::SETTING;
      else if(tp.y < 775 && tp.y > 680)
          page = PAGE::CALENDAR;
      else if(tp.y < 680 && tp.y > 590)
          page = PAGE::ALARM;
      else if(tp.y < 590 && tp.y > 505)
          page = PAGE::DIAGRAM;
      else if(tp.y < 505 && tp.y > 415)
          page = PAGE::WIFI;
//      else if(tp.y < 415 && tp.y > 320)
//          page = 6;
//      else if(tp.y < 320 && tp.y > 220)
//          page = 7;
      
      if(page != currentPage)
      {
          currentPage = page;
          menuSelect();
          pageSelect();
      }
  }
  else if(currentPage == PAGE::SETTING)
  {
      if(tp.x > 590 && tp.x < 710 && tp.y < 310 && tp.y > 250)
      {
        clearPage();
        subPage1 = Inc(subPage1, 2, 1);
      }
      
      if(subPage1 == 1)
      {
        touch_page_1_1();
        writeDS3231();
        page_1_sub_1();
      }
      else if(subPage1 == 2)
      {
        touch_page_1_2();
        page_1_sub_2();
      }
  }
  else if(currentPage == PAGE::ALARM)
  {
    if(tp.x > 260 && tp.x < 340 && tp.y < 920 && tp.y > 760)
    {
      a1_status_reg ^= 0x80;
      eeprom_write_byte(A1_REG, a1_status_reg);
    }
    else if(tp.x > 340 && tp.x < 500 && (a1_status_reg & 0x80))
    {
      if(tp.y < 920 && tp.y > 825)
      {
        a1_status_reg ^= 0x01;
        eeprom_write_byte(A1_REG, a1_status_reg);
      }
      else if(tp.y < 825 && tp.y > 735)
      {
        a1_status_reg ^= 0x02;
        eeprom_write_byte(A1_REG, a1_status_reg);
      }
      else if(tp.y < 735 && tp.y > 635)
      {
        a1_status_reg ^= 0x04;
        eeprom_write_byte(A1_REG, a1_status_reg);
      }
      else if(tp.y < 635 && tp.y > 540)
      {
        a1_status_reg ^= 0x08;
        eeprom_write_byte(A1_REG, a1_status_reg);
      }
      else if(tp.y < 540 && tp.y > 440)
      {
        a1_status_reg ^= 0x10;
        eeprom_write_byte(A1_REG, a1_status_reg);
      }
      else if(tp.y < 440 && tp.y > 345)
      {
        a1_status_reg ^= 0x20;
        eeprom_write_byte(A1_REG, a1_status_reg);
      }
      else if(tp.y < 345 && tp.y > 245)
      {
        a1_status_reg ^= 0x40;
        eeprom_write_byte(A1_REG, a1_status_reg);
      }
    }
    else if(a1_status_reg & 0x80)
    {
      //Стрелки вверх для будильника
      if(tp.x < 605 && tp.x > 525)
      {
        if(tp.y < 525 && tp.y > 465)
        {
            a1_hour = Inc(a1_hour, 23, 0);
            eeprom_write_byte(A1_H, a1_hour);
        }
        else if(tp.y < 395 && tp.y > 340)
        {
            a1_minute = Inc(a1_minute, 59, 0);
            eeprom_write_byte(A1_M, a1_minute);
        }
      }
      //Стрелки вниз для будильника
      else if(tp.x < 780 && tp.x > 700)
      {
        if(tp.y < 525 && tp.y > 465)
        {
            a1_hour = Dec(a1_hour, 23, 0);
            eeprom_write_byte(A1_H, a1_hour);
        }
        else if(tp.y < 395 && tp.y > 340)
        {
            a1_minute = Dec(a1_minute, 59, 0);
            eeprom_write_byte(A1_M, a1_minute);
        }
      }
    }
    page_3_Draw_mainText();
  }
  else if(currentPage == PAGE::DIAGRAM)
  {
    if(tp.x < 220 && tp.x > 180)
    {
      if(tp.y < 705 && tp.y > 440)
      {
        subPage4 = Inc(subPage4, 2, 1);
        clearPage();
        page_4_Draw();
      }
    }
  }


  //debug
  tft.setTextSize(0);
  tft.setCursor(0, 0);
  tft.println("tp.x=" + String(tp.x));
  tft.println("tp.y=" + String(tp.y));
  tft.println("tp.z=" + String(tp.z));

MARKER: 
  if(dht22Check)
  {
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) 
      connection_DHT22 = false;
    else
    {
      connection_DHT22 = true;

      if(dht22Counter60sec)
      {
        if(temperature > 35)
          temperature = 35;
        else if(temperature < -15)
          temperature = -15;
        else if(temperature == NAN)
          temperature = 0xFF;

        if(humidity > 100)
          humidity = 100;
        else if(humidity < 0)
          humidity = 0;
        else if(humidity == NAN)
          humidity = 0xFF;
          
        hourTempLog[minute] = (int)temperature;
        hourHumLog[minute] = (int)humidity;
        
        dht22Counter60sec = false;

        if(currentPage == PAGE::DIAGRAM)
        {
          clearPage();
          page_4_Draw();
        }
      }
    }
    dht22Check = false;
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
