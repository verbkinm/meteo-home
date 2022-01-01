void page_3_Draw()
{
    tft.setTextSize(2);
    tft.setCursor(150 - 8 * 4, 7);
    tft.print("Alarm #1");

    tft.drawRect(13, 26 + 30, 294, 48, TFT_COLOR::GREY);
    tft.drawLine(13, 26 + 24 + 30, 306, 26 + 24 + 30, TFT_COLOR::GREY);

    tft.setTextSize(1);
    for(uint8_t i = 0; i < 7; i++)
    {
      tft.drawLine(13 + 42 * i, 26 + 30, 13 + 42 * i, 26 + 47 + 30, TFT_COLOR::GREY); 
      tft.setCursor(26 + 42 * i, 36 + 30);
      tft.print(weekDays[i]);
    }

    page_3_Draw_mainText();

    tft.setTextSize(3);
    tft.setTextColor(TFT_COLOR::BLUE, TFT_COLOR::BLACK);
    tft.setCursor(195, 114);
    tft.print(char(30));
    tft.print("  ");
    tft.print(char(30));
    
    tft.setCursor(195, 165);
    tft.print(char(31));
    tft.print("  ");
    tft.print(char(31));

    tft.setTextColor(TFT_COLOR::WHITE, TFT_COLOR::BLACK);
}

void page_3_Draw_mainText()
{
  tft.setTextSize(1);
  tft.setCursor(17, 36);
  tft.print("Enable: ");

  if(a1_status_reg & 0x80)
    tft.print("on ");
  else
    tft.print("off");
      
  tft.setTextSize(3);
  tft.setCursor(60, 140);
  if(a1_status_reg & 0x80)
    tft.print("Alarm: " + leadingZero(a1_hour) + ":" + leadingZero(a1_minute));
  else
    tft.print("Alarm: --:--");

  tft.setTextSize(1);
  for(uint8_t i = 0; i < 7; i++)
  {     
    tft.setCursor(32 + 42 * i, 60 + 30);
    if( (a1_status_reg >> i) & 0x01)
      tft.print("+");      
    else
      tft.print("-");   
  }
}
