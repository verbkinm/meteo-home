//Страница настроек даты, времени и пороговых значение температуры и влажности

void page_1_Draw()
{
  if(subPage1 == 1)
    page_1_sub_1();
  else if(subPage1 == 2)
    page_1_sub_2();
}

void page_1_arrow()
{
    tft.setTextColor(TFT_COLOR::BLUE, TFT_COLOR::BLACK);
    tft.setTextSize(4);
    tft.setCursor(280, 140);
    tft.print(char(16));
    tft.setTextColor(TFT_COLOR::WHITE, TFT_COLOR::BLUE);
    tft.setTextSize(1);
    tft.setCursor(285, 150);
    tft.print(Inc(subPage1, 2, 1));
}

void page_1_Draw_data()
{
    tft.setTextSize(2);
    tft.setCursor(20, 50);
    if(connection_DS3231)
    {
      tft.print("Date: " + weekDays[weekDay] + ". " + dateString(day, month, year));
      tft.setCursor(20, 140);
      tft.print("Time: " + leadingZero(hour) + ":" + leadingZero(minute) + ":" + leadingZero(second));
    }
    else
    {
      tft.print("Date: ---. --.--.----");
      tft.setCursor(20, 140);
      tft.print("Time: --:--:--");
    }
}

void page_1_sub_1()
{
    page_1_Draw_data();

    tft.setTextSize(3);
    tft.setTextColor(TFT_COLOR::BLUE, TFT_COLOR::BLACK);
    
    tft.setCursor(102, 25);
    tft.print(char(30));
    tft.setCursor(156, 25);
    tft.print(char(30));
    tft.print(" ");
    tft.print(char(30));
    tft.setCursor(236, 25);
    tft.print(char(30));

    tft.setCursor(102, 70);
    tft.print(char(31));
    tft.setCursor(156, 70);
    tft.print(char(31));
    tft.print(" ");
    tft.print(char(31));
    tft.setCursor(236, 70);
    tft.print(char(31));

    tft.setCursor(96, 114);
    tft.print(char(30));
    tft.print(" ");
    tft.print(char(30));

    tft.setCursor(96, 160);
    tft.print(char(31));
    tft.print(" ");
    tft.print(char(31));

    page_1_arrow();
    
    tft.setTextColor(TFT_COLOR::WHITE, TFT_COLOR::BLACK);
}

void page_1_sub_2()
{
    tft.setTextSize(2);
    
    tft.setCursor(175, 25);
    tft.print("min  max");
    
    tft.setCursor(20, 70);
    tft.print("Temperature:");
    tft.setCursor(180, 70);
    tft.print(leadingZero(temperature_low) + " "); 
    tft.setCursor(242, 70);
    tft.print(leadingZero(temperature_high) + " ");

    tft.setCursor(20, 140);
    tft.print("Humidity:");
    tft.setCursor(180, 140);
    tft.print(leadingZero(humidity_low) + " "); 
    tft.setCursor(242, 140);
    tft.print(leadingZero(humidity_high) + " ");

    tft.setTextSize(3);
    tft.setTextColor(TFT_COLOR::BLUE, TFT_COLOR::BLACK);
    
    tft.setCursor(184, 45);
    tft.print(char(30));
    tft.setCursor(245, 45);
    tft.print(char(30));

    tft.setCursor(184, 90);
    tft.print(char(31));
    tft.setCursor(245, 90);
    tft.print(char(31));

    tft.setCursor(184, 115);
    tft.print(char(30));
    tft.setCursor(245, 115);
    tft.print(char(30));

    tft.setCursor(184, 158);
    tft.print(char(31));
    tft.setCursor(245, 158);
    tft.print(char(31));

    page_1_arrow();

    tft.setTextColor(TFT_COLOR::WHITE, TFT_COLOR::BLACK);
}
