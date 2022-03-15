//Страницы для задания и просмотра графика кормления младенца

void page_6_Draw()
{
  if(subPage6 == 2)
  {
    page_6_graph();
    return;
  }
  
  tft.setTextSize(2);
  tft.setTextColor(TFT_COLOR::YELLOW, TFT_COLOR::BLUE);

  for(uint8_t i = 0, val = 30, x = 50, y = 50, x_text = 40, y_text = 43; 
      i < 6; 
      i++, val += 30, x += 75, x_text += 75)
  {
    if(i == 3)
    {
      x = 50;
      y = 125;
      x_text = 33;
      y_text = 118;
    }

    tft.setCursor(x_text, y_text);
    if( (i + 1) == (page_6_value / 30))
    {
      tft.fillCircle(x, y, 25, TFT_COLOR::RED);
      tft.setTextColor(TFT_COLOR::YELLOW, TFT_COLOR::RED);
      tft.print(val);  
      tft.setTextColor(TFT_COLOR::YELLOW, TFT_COLOR::BLUE);
    }
    else
    {
      tft.fillCircle(x, y, 25, TFT_COLOR::BLUE);
      tft.print(val);  
    }
  }

  tft.setTextColor(TFT_COLOR::YELLOW, TFT_COLOR::RED);
  tft.fillCircle(275, 50, 25, TFT_COLOR::RED);
  tft.setCursor(270, 43);
  tft.print("R");
      
  tft.fillCircle(275, 125, 25, TFT_COLOR::RED);
  tft.setCursor(270, 118);
  tft.print("G");

  uint8_t page_6_total = 0;
  File file = SD.open("feeding/total/" + dateStringWithoutDot(day, month, year));
  if(file)
  {
    page_6_total = file.read();
    Serial.println("page_6_total = " + String(page_6_total));
    file.close();
  }

  int sum = 0;
  file = SD.open("feeding/" + dateStringWithoutDot(day, month, year));
  if(file)
  {
    while (file.available()) 
    {
      uint8_t x1 = file.read();
      sum += file.read() * 30;  
    }
    file.close();
  }

  tft.setTextColor(TFT_COLOR::YELLOW, TFT_COLOR::BLACK);
  tft.setCursor(15, 167);
  tft.print("Total feedings: " + String(page_6_total) + " (" + String(sum) + ")    ");
}

void page_6_graph()
{
  if(list_day == 0)
  {
    list_day = day;
    list_month = month;
    list_year = year;
  }
  
  clearPage();
  tft.setTextSize(0);
  //Сетка
  tft.drawRect(28, 26, 264, 160, TFT_COLOR::GREY);
  for (uint8_t i = 0; i < 12; i++)
    tft.drawLine(28 + 22 * i, 26, 28 + 22 * i, 184, TFT_COLOR::GREY);
  for (uint8_t i = 0; i < 8; i++)
    tft.drawLine(28, 26 + 20 * i, 290, 26 + 20 * i, TFT_COLOR::GREY);

  uint8_t volume = 0;
  String spaces;
  for (uint8_t i = 0; i < 9; i++, volume += 30)
  {
    if (volume < 100)
      spaces = "  ";
    else
      spaces = " ";

    tft.setCursor(0, 183 - 20 * i);
    tft.setTextColor(TFT_COLOR::ORANGE);
    tft.print(spaces + String(volume));
  }

  tft.setTextColor(TFT_COLOR::WHITE, TFT_COLOR::BLACK);

  //Цифры
  for (uint8_t i = 0, h = 0; i < 12; i++, h += 2)
  {
    tft.setCursor(24 + 22 * i, 188);
    tft.print(leadingZero(h));
  }
  tft.setCursor(24 + 22 * 12, 188);
  tft.print("23");

  //draw data
  tft.setTextSize(2);
  tft.setCursor(320 / 2 - ((4 * 2 * 14 + 14 * 2) / 2) - 10, 7);
  tft.setTextColor(TFT_COLOR::BLUE);
  tft.print(String(char(17)) + " " + dateString(list_day, list_month, list_year) + " " + char(16));

  uint8_t page_6_total = 0;
  File file = SD.open("feeding/" + dateStringWithoutDot(list_day, list_month, list_year));
  if(file)
  {       
    while (file.available()) 
    {
      uint16_t x1 = static_cast<uint8_t>(file.read()) * 5.5 + 28;
      uint8_t y1 = 186 - (file.read() * 20);  

      tft.fillRect(x1 - 1, y1 - 1, 3, 3, TFT_COLOR::ORANGE);

      while (file.available()) 
      {
        uint16_t x2 = static_cast<uint8_t>(file.read()) * 5.5 + 28;
        uint8_t y2 = 186 - (file.read() * 20);
        tft.drawLine(x1, y1, x2, y2, TFT_COLOR::ORANGE);
        file.seek(file.position() - 2);
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

void page_6_record()
{
  uint8_t page_6_total = 0;
  
  File file = SD.open("feeding/total/" + dateStringWithoutDot(day, month, year));
  if(file)
  {
    page_6_total = file.read();
    file.close();
  }

  SD.remove("feeding/total/" + dateStringWithoutDot(day, month, year));
  file = SD.open("feeding/total/" + dateStringWithoutDot(day, month, year), FILE_WRITE);
  if(file)
  {
    file.write(++page_6_total);
    file.close();
  }
  
  file = SD.open("feeding/" + dateStringWithoutDot(day, month, year), FILE_WRITE);
  if(file)
  {
    file.write((hour * 60 + minute) / 30 );
    file.write(page_6_value / 30);
    file.close();
  }
  
  page_6_Draw();
}
