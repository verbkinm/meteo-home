void touch_select_page()
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
  else if(tp.y < 415 && tp.y > 280)
      page = PAGE::FEEDING;
//  else if(tp.y < 320 && tp.y > 220)
//      page = 7;
  
  if(page != currentPage)
  {
      currentPage = page;
      menuSelect();
      pageSelect();
  }
}

void touch_setting_page()
{
  if(tp.x > 530 && tp.x < 710 && tp.y < 280 && tp.y > 185)
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

void touch_alarm_page()
{
  if(tp.x > 260 && tp.x < 340 && tp.y < 920 && tp.y > 760)
  {
    a1_status_reg ^= 0x80;
    eeprom_write_byte(A1_REG, a1_status_reg);
  }
  else if(tp.x > 340 && tp.x < 500)
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

void touch_diagram_page()
{
  if(tp.x < 290 && tp.x > 155)
  {
    if(tp.y < 705 && tp.y > 440)
    {
      subPage4 = Inc(subPage4, 2, 1);
      clearPage();
      page_4_Draw();
    }
    else if(subPage4 == 2) //Сутки
    {
      if(tp.y < 800 && tp.y > 705)  
      {
        clearPage();
        decListDate();  
        page_4_Draw();
      }
      else if(tp.y < 400 && tp.y > 330)
      {
        clearPage();
        incListDate();  
        page_4_Draw();
      }
    }
  }  
}

void touch_feeding_select(uint8_t value)
{
  page_6_value = value;
  page_6_Draw();
}

void touch_feeding_page()
{
  if(subPage6 == 1)
  {
    if(tp.x < 380 && tp.x > 200)
    {
      if(tp.y < 890 && tp.y > 760)
        touch_feeding_select(30);
      else if(tp.y < 700 && tp.y > 580)
        touch_feeding_select(60);
      else if(tp.y < 520 && tp.y > 390)
        touch_feeding_select(90);
      else if(tp.y < 340 && tp.y > 200)
        page_6_record();
    }
    else if(tp.x < 625 && tp.x > 450)
    {
      if(tp.y < 890 && tp.y > 760)
        touch_feeding_select(120);
      else if(tp.y < 700 && tp.y > 580)
        touch_feeding_select(150);
      else if(tp.y < 520 && tp.y > 390)
        touch_feeding_select(180);
      else if(tp.y < 340 && tp.y > 200)
      {
        subPage6 = 2;
        page_6_Draw();
      }
    }
  }
  else if(subPage6 == 2)
  {
    if(tp.x < 290 && tp.x > 155)
    {
      if(tp.y < 800 && tp.y > 705)  
      {
        clearPage();
        decListDate();  
        page_6_Draw();
      }
      else if(tp.y < 400 && tp.y > 330)
      {
        clearPage();
        incListDate();  
        page_6_Draw();
      }
    }  
    else if(tp.x < 740 && tp.x > 240)
    {
      subPage6 = 1;
      clearPage();
      page_6_Draw();
    }
  }
}

void touch_page_1_1()
{
  //Стрелки вверх для даты 
  if(tp.x < 310 && tp.x > 180)
  {
    if(tp.y < 710 && tp.y > 650)
        weekDay = Inc(weekDay, 6, 0);
    else if(tp.y < 590 && tp.y > 510)
        day = Inc(day, dayInMonthF(month - 1), 1);
    else if(tp.y < 490 && tp.y > 430)
    {
        month = Inc(month, 12, 1);
        if(day > dayInMonthF(month - 1))
          day = dayInMonthF(month - 1);
    }
    else if(tp.y < 400 && tp.y > 300)
        year = Inc(year, 99, 0);
  }
  //Стрелки вниз для даты 
  else if(tp.x < 440 && tp.x > 330)
  {
    if(tp.y < 710 && tp.y > 650)
        weekDay = Dec(weekDay, 6, 0);
    else if(tp.y < 590 && tp.y > 510)
        day = Dec(day, dayInMonthF(month - 1), 1);
    else if(tp.y < 490 && tp.y > 430)
    {
        month = Dec(month, 12, 1);
        if(day > dayInMonthF(month - 1))
          day = dayInMonthF(month - 1);
    }
    else if(tp.y < 400 && tp.y > 300)
        year = Dec(year, 99, 0);
  }
  //Стрелки вверх для часов
  else if(tp.x < 605 && tp.x > 525)
  {
    if(tp.y < 740 && tp.y > 650)
        hour = Inc(hour, 23, 0);
    else if(tp.y < 650 && tp.y > 570)
        minute = Inc(minute, 59, 0);
  }
  //Стрелки вниз для часов
  else if(tp.x < 750 && tp.x > 605)
  {
    if(tp.y < 740 && tp.y > 650)
        hour = Dec(hour, 23, 0);
    else if(tp.y < 650 && tp.y > 570)
        minute = Dec(minute, 59, 0);
  }
}
void touch_page_1_2()
{
  //Стрелки вверх для температуры 
  if(tp.x < 370 && tp.x > 260)
  {
    if(tp.y < 540 && tp.y > 480)
    {
        temperature_low = Inc(temperature_low, 30, -20);
        eeprom_write_byte(T_LOW, temperature_low);
    }
    else if(tp.y < 380 && tp.y > 285)
    {
        temperature_high = Inc(temperature_high, 30, -20);
        eeprom_write_byte(T_HIGH, temperature_high);
    }
  }
  //Стрелки вниз для температуры 
  else if(tp.x < 505 && tp.x > 415)
  {
    if(tp.y < 540 && tp.y > 480)
    {
        temperature_low = Dec(temperature_low, 30, -20);
        eeprom_write_byte(T_LOW, temperature_low);
    }
    else if(tp.y < 380 && tp.y > 285)
    {
        temperature_high = Dec(temperature_high, 30, -20);
        eeprom_write_byte(T_HIGH, temperature_high);
    }
  }
  //Стрелки вверх для влажности 
  else if(tp.x < 590 && tp.x > 510)
  {
    if(tp.y < 520 && tp.y > 440)
    {
        humidity_low = Inc(humidity_low, 100, 0);
        eeprom_write_byte(H_LOW, humidity_low);
    }
    else if(tp.y < 370 && tp.y > 290)
    {
        humidity_high = Inc(humidity_high, 100, 0);
        eeprom_write_byte(H_HIGH, humidity_high);
    }
  }
  //Стрелки вниз для влажности 
  else if(tp.x < 730 && tp.x > 620)
  {
    if(tp.y < 520 && tp.y > 440)
    {
        humidity_low = Dec(humidity_low, 100, 0);
        eeprom_write_byte(H_LOW, humidity_low);
    }
    else if(tp.y < 370 && tp.y > 290)
    {
        humidity_high = Dec(humidity_high, 100, 0);
        eeprom_write_byte(H_HIGH, humidity_high);
    }
  }
}
