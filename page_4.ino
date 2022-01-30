void page_4_Draw()
{
  tft.setTextSize(0);
  //Сетка
  tft.drawRect(28, 26, 264, 160, TFT_COLOR::GREY);
  for (uint8_t i = 0; i < 12; i++)
    tft.drawLine(28 + 22 * i, 26, 28 + 22 * i, 184, TFT_COLOR::GREY);
  for (uint8_t i = 0; i < 10; i++)
    tft.drawLine(28, 26 + 16 * i, 290, 26 + 16 * i, TFT_COLOR::GREY);

  int8_t t = 35;
  String spaces;
  for (uint8_t i = 0, h = 100; i < 11; i++, t -= 5, h -= 10)
  {
    if (t <= 35 && t >= 10 || t == -5)
      spaces = " ";
    else if (t <= 5 && t >= 0)
      spaces = "  ";
    else
      spaces = "";

    tft.setCursor(0, 23 + 16 * i);
    tft.setTextColor(TFT_COLOR::ORANGE);
    tft.print(spaces + String(t) + char(247));

    if (h < 100 && h > 0)
      spaces = " ";
    else if (h == 0)
      spaces = "  ";
    else
      spaces = "";

    tft.setCursor(295, 23 + 16 * i);
    tft.setTextColor(TFT_COLOR::WHITEBLUE);
    tft.print(spaces + String(h) + "%");
  }

  tft.setTextColor(TFT_COLOR::WHITE, TFT_COLOR::BLACK);
  if (subPage4 == 1)
  {
    //Цифры
    for (uint8_t i = 0, m = 0; i < 12; i++, m += 5)
    {
      tft.setCursor(24 + 22 * i, 188);
      tft.print(leadingZero(m));
    }
    tft.setCursor(24 + 22 * 12, 188);
    tft.print("59");

    page_4_Draw_OneHour();
  }
  else if (subPage4 == 2)
  {
    //Цифры
    for (uint8_t i = 0, h = 0; i < 12; i++, h += 2)
    {
      tft.setCursor(24 + 22 * i, 188);
      tft.print(leadingZero(h));
    }
    tft.setCursor(24 + 22 * 12, 188);
    tft.print("23");

    page_4_Draw_Date();
  }

  tft.setTextColor(TFT_COLOR::WHITE, TFT_COLOR::BLACK);
}

void page_4_Draw_OneHour()
{
  tft.setTextSize(2);
  tft.setCursor(320 / 2 - ((4 * 2 * 8 + 8 * 2) / 2) - 10, 7);
  tft.setTextColor(TFT_COLOR::BLUE);
  tft.print("One Hour");

  for (uint8_t i = 0; i < 59; i++)
  {
    if (hourTempLog[i] != 0xFF)
    {
      for (uint8_t j = i + 1; j < 60; j++)
      {
        if (hourTempLog[j] != 0xFF)
        {
          tft.drawLine(28 + i * 4.4, (26 + 16 * 7) - hourTempLog[i] * 3.2, 28 + j * 4.4, (26 + 16 * 7) - hourTempLog[j] * 3.2, TFT_COLOR::ORANGE);
          i = j;
        }
        else
          break;
      }
    }
  }

  for (uint8_t i = 0; i < 59; i++)
  {
    if (hourHumLog[i] != 0xFF)
    {
      for (uint8_t j = i + 1; j < 60; j++)
      {
        if (hourHumLog[j] != 0xFF)
        {
          tft.drawLine(28 + i * 4.4, 186 - hourHumLog[i] * 1.6, 28 + j * 4.4, 186 - hourHumLog[j] * 1.6, TFT_COLOR::WHITEBLUE);
          i = j;
        }
        else
          break;
      }
    }
  }

  tft.drawLine(28 + minute * 4.4, 26, 28 + minute * 4.4, 185, TFT_COLOR::RED);
  
  if (hourTempLog[minute] != 0xFF)
    tft.fillRect(28 + minute * 4.4 - 2, (26 + 16 * 7) - hourTempLog[minute] * 3.2 - 2, 5, 5, TFT_COLOR::ORANGE);
  if (hourHumLog[minute] != 0xFF)
    tft.fillRect(28 + minute * 4.4 - 2, 186 - hourHumLog[minute] * 1.6 - 2, 5, 5, TFT_COLOR::WHITEBLUE);
}

void page_4_Draw_Date()
{ 
  if(list_day == 0)
  {
    list_day = day;
    list_month = month;
    list_year = year;
  }
  
  tft.setTextSize(2);
  tft.setCursor(320 / 2 - ((4 * 2 * 14 + 14 * 2) / 2) - 10, 7);
  tft.setTextColor(TFT_COLOR::BLUE);
  tft.print(String(char(17)) + " " + dateString(list_day, list_month, list_year) + " " + char(16));

  File file = SD.open("meteo/" + dateStringWithoutDot(list_day, list_month, list_year));
  if(file)
  {
    while (file.available()) 
    {
      uint16_t x1 = static_cast<uint8_t>(file.read()) * 5.5 + 28;
      int8_t y1 = file.read();  
      uint8_t y2 = file.read();

      tft.fillRect(x1 - 1, y1 - 1, 3, 3, TFT_COLOR::ORANGE);
      tft.fillRect(x1 - 1, y2 - 1, 3, 3, TFT_COLOR::WHITEBLUE);

      while (file.available()) 
      {
        uint16_t x2 = static_cast<uint8_t>(file.read()) * 5.5 + 28;
        int8_t y1_2 = file.read();  
        uint8_t y2_2 = file.read();
        tft.drawLine(x1, y1, x2, y1_2, TFT_COLOR::ORANGE);
        tft.drawLine(x1, y2, x2, y2_2, TFT_COLOR::WHITEBLUE);
        file.seek(file.position() - 3);
        break;
      }
    }
    file.close();
  }
  else
  {
    tft.setCursor(73, 90);
    tft.setTextColor(TFT_COLOR::RED);
    tft.print("File not exist!");
  }
}
