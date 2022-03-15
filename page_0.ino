//Главная страница. Время, дата, температура, влажность.

void page_0_Draw()
{    
    bmpDraw("temp.bmp", 35, 22);
    bmpDraw("Humidity.bmp", 160, 20);

    page_0_Draw_data();
}

void page_0_Draw_data()
{
    TFT_COLOR COLOR = TFT_COLOR::RED;
    
    String sign = "";

    if (temperature > 0)
      sign = '+';

    if(temperature < temperature_low)
      COLOR = TFT_COLOR::YELLOW;
    else if(temperature >= temperature_low && temperature <= temperature_high)
      COLOR = TFT_COLOR::GREEN;

    tft.setTextColor(COLOR, TFT_COLOR::BLACK);
    tft.setCursor(65, 30);
    tft.setTextSize(2);
    tft.print(sign + String(temperature, 1) + "C" + char(247));
    
    tft.setCursor(200, 30);

    COLOR = TFT_COLOR::RED;
    if(humidity < humidity_low)
      COLOR = TFT_COLOR::YELLOW;
    else if(humidity >= humidity_low && humidity <= humidity_high)
      COLOR = TFT_COLOR::GREEN;
      
    tft.setTextColor(COLOR, TFT_COLOR::BLACK);
    tft.print(String(humidity, 1) + "%  ");    

    int pixSize = 7;
    tft.setTextColor(TFT_COLOR::WHITE, TFT_COLOR::BLACK);
    tft.setCursor(80, 150);
    if(connection_DS3231)
    {
      tft.print(weekDays[weekDay] + ". " + dateString(day, month, year));//leadingZero(day) + "." + leadingZero(month) + ".20" + leadingZero(year));
      
      tft.setCursor(320 / 2 - ((4 * pixSize * 5 + 5 * pixSize) / 2) - 10, 240 / 2 - (8 * pixSize) / 2 - 20);
      tft.setTextSize(pixSize);
      tft.print(leadingZero(hour) + ":" + leadingZero(minute));
    }
    else
    {
      tft.print("---. --.--.----");
      
      tft.setCursor(320 / 2 - ((4 * pixSize * 5 + 5 * pixSize) / 2) - 10, 240 / 2 - (8 * pixSize) / 2 - 20);
      tft.setTextSize(pixSize);
      tft.print("--:--");
    }
}
