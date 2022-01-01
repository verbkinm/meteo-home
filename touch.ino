void touch_page_1_1()
{
  //Стрелки вверх для даты 
  if(tp.x < 310 && tp.x > 225)
  {
    if(tp.y < 735 && tp.y > 670)
        weekDay = Inc(weekDay, 6, 0);
    else if(tp.y < 615 && tp.y > 555)
        day = Inc(day, dayInMonthF(month - 1), 1);
    else if(tp.y < 535 && tp.y > 465)
    {
        month = Inc(month, 12, 1);
        if(day > dayInMonthF(month - 1))
          day = dayInMonthF(month - 1);
    }
    else if(tp.y < 430 && tp.y > 360)
        year = Inc(year, 99, 0);
  }
  //Стрелки вниз для даты 
  else if(tp.x < 485 && tp.x > 405)
  {
    if(tp.y < 735 && tp.y > 670)
        weekDay = Dec(weekDay, 6, 0);
    else if(tp.y < 615 && tp.y > 555)
        day = Dec(day, dayInMonthF(month - 1), 1);
    else if(tp.y < 535 && tp.y > 465)
    {
        month = Dec(month, 12, 1);
        if(day > dayInMonthF(month - 1))
          day = dayInMonthF(month - 1);
    }
    else if(tp.y < 430 && tp.y > 360)
        year = Dec(year, 99, 0);
  }
  //Стрелки вверх для часов
  else if(tp.x < 605 && tp.x > 525)
  {
    if(tp.y < 750 && tp.y > 685)
        hour = Inc(hour, 23, 0);
    else if(tp.y < 670 && tp.y > 610)
        minute = Inc(minute, 59, 0);
  }
  //Стрелки вниз для часов
  else if(tp.x < 780 && tp.x > 700)
  {
    if(tp.y < 750 && tp.y > 685)
        hour = Dec(hour, 23, 0);
    else if(tp.y < 780 && tp.y > 610)
        minute = Dec(minute, 59, 0);
  }
}
void touch_page_1_2()
{
  //Стрелки вверх для температуры 
  if(tp.x < 370 && tp.x > 280)
  {
    if(tp.y < 540 && tp.y > 480)
    {
        temperature_low = Inc(temperature_low, 30, -20);
        eeprom_write_byte(T_LOW, temperature_low);
    }
    else if(tp.y < 400 && tp.y > 345)
    {
        temperature_high = Inc(temperature_high, 30, -20);
        eeprom_write_byte(T_HIGH, temperature_high);
    }
  }
  //Стрелки вниз для температуры 
  else if(tp.x < 510 && tp.x > 445)
  {
    if(tp.y < 540 && tp.y > 480)
    {
        temperature_low = Dec(temperature_low, 30, -20);
        eeprom_write_byte(T_LOW, temperature_low);
    }
    else if(tp.y < 400 && tp.y > 345)
    {
        temperature_high = Dec(temperature_high, 30, -20);
        eeprom_write_byte(T_HIGH, temperature_high);
    }
  }
  //Стрелки вверх для влажности 
  else if(tp.x < 590 && tp.x > 520)
  {
    if(tp.y < 540 && tp.y > 480)
    {
        humidity_low = Inc(humidity_low, 100, 0);
        eeprom_write_byte(H_LOW, humidity_low);
    }
    else if(tp.y < 400 && tp.y > 345)
    {
        humidity_high = Inc(humidity_high, 100, 0);
        eeprom_write_byte(H_HIGH, humidity_high);
    }
  }
  //Стрелки вниз для влажности 
  else if(tp.x < 750 && tp.x > 660)
  {
    if(tp.y < 540 && tp.y > 480)
    {
        humidity_low = Dec(humidity_low, 100, 0);
        eeprom_write_byte(H_LOW, humidity_low);
    }
    else if(tp.y < 400 && tp.y > 345)
    {
        humidity_high = Dec(humidity_high, 100, 0);
        eeprom_write_byte(H_HIGH, humidity_high);
    }
  }
}
