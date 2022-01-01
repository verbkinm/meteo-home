#pragma once

#define MINPRESSURE 20
#define MAXPRESSURE 1000
#define SD_CS 5

#define BUFFPIXEL 20

enum TFT_COLOR {
                BLACK = 0x0000, 
                BLUE = 0x001F, 
                RED = 0xF800, 
                GREEN = 0x07E0, 
                CYAN = 0x07FF, 
                MAGENTA = 0xF81F, 
                YELLOW = 0xFFE0, 
                WHITE = 0xFFFF, 
                GREY = 0x632C,
                ORANGE = 0xFDCA,
                WHITEBLUE = 0x76FF
                };

enum class PAGE {
           HOME,
           SETTING,
           CALENDAR,
           ALARM,
           DIAGRAM,
           WIFI
          };

#define A1_REG 0x01
#define A1_H 0x02
#define A1_M 0x03

#define T_LOW 0x04
#define T_HIGH 0x05
#define H_LOW 0x06
#define H_HIGH 0x07

#define DHTPIN 35 
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTVCC 37
#define DHTGND 31

#define ALARMVCC 43
#define ALARMGND 47
