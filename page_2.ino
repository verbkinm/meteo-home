//Страница отображения текущего месяца

void page_2_Draw()
{
    tft.setTextSize(2);
    tft.setCursor(150 - strlen(monthList[month - 1].c_str()) * 4, 7);
    tft.print(monthList[month - 1]);

    tft.drawRect(13, 26, 294, 168, TFT_COLOR::GREY);

    tft.setTextSize(1);
    for(uint8_t i = 0; i < 7; i++)
    {
      tft.drawLine(13 + 42 * i, 26, 13 + 42 * i, 192, TFT_COLOR::GREY); 
      tft.drawLine(13, 26 + 24 * i, 306, 26 + 24 * i, TFT_COLOR::GREY);
      tft.setCursor(26 + 42 * i, 36);
      tft.print(weekDays[i]);
    }

    //День недели первого числа текущего месяца!
    uint8_t tmpW = weekDay;
    for(uint8_t i = day; i > 1; i--)
      tmpW = Dec(tmpW, 6, 0);
    
    uint8_t counter = 1;
    for(uint8_t j = 0; j < 6; j++)
    {     
      uint8_t x = 30 + 42 * tmpW, y = 60 + 24 * j;
      for(uint8_t i = tmpW; i < 6; i++, x += 42)
      {
        if(dayInMonthF(month - 1) < counter)
          break;
        
        tft.setCursor(x, y);
        page_2_Draw_day(counter++);
      }
      
      if(dayInMonthF(month - 1) < counter)
        break; 
      tft.setCursor(280, y);
      page_2_Draw_day(counter++);
      
      tmpW = 0;
    }
}

void page_2_Draw_day(int counter)
{
  if(counter == day)
    tft.setTextColor(TFT_COLOR::RED, TFT_COLOR::BLACK);
    
  tft.print(String(counter));
  tft.setTextColor(TFT_COLOR::WHITE, TFT_COLOR::BLACK);
}
