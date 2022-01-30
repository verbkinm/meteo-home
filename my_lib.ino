String leadingZero(int8_t digit)
{
  return (digit < 10 && digit >= 0) ? "0" + String(digit) : String(digit);
}

int8_t Inc(int8_t value, int8_t maxValue, int8_t minValue)
{
  return ++value > maxValue ? minValue : value;
}

int8_t Dec(int8_t value, int8_t maxValue, int8_t minValue)
{
  return --value < minValue ? maxValue : value;;
}

uint8_t dayInMonthF(uint8_t month)
{
  if((month == 1) && (year % 4 == 0))
    return 29;
  
  return dayInMonth[month];
}

void draw_statusPanel()
{
    if(connection_WIFI)
        bmpDraw("wifi-on.bmp", 300, 0);
    else
        bmpDraw("wifi-off.bmp", 300, 0);

    if(connection_DS3231)
        bmpDraw("time-on.bmp", 280, 0);
    else
        bmpDraw("time-off.bmp", 280, 0);

    if(connection_DHT22)
        bmpDraw("dht-on.bmp", 260, 0);
    else
        bmpDraw("dht-off.bmp", 260, 0);

    if(sdCheck)
        bmpDraw("sd-on.bmp", 240, 0);
    else
        bmpDraw("sd-off.bmp", 240, 0);
}

float dht22_values(float arg, int8_t maxValue, int8_t minValue)
{
  if(arg > maxValue)
    arg = maxValue;
  else if(arg < -minValue)
    arg = minValue;
  else if(arg == NAN)
    arg = 0xFF;

    return arg;
}

String dateString(uint8_t day, uint8_t month, uint8_t year)
{
  return leadingZero(day) + "." + leadingZero(month) + ".20" + leadingZero(year);
}

String dateStringWithoutDot(uint8_t day, uint8_t month, uint8_t year)
{
  String date = dateString(day, month, year);
  date.remove(2, 1);
  date.remove(4, 1);

  return date;
}

void decListDate()
{
  uint8_t prevMonth = list_month - 1;
  if(prevMonth == 0)
    prevMonth = 12;

  uint8_t maxPrevMonthDay = dayInMonthF(prevMonth - 1);
  
  list_day = Dec(list_day, maxPrevMonthDay, 1);
  if(list_day == maxPrevMonthDay)
  {
    list_month = Dec(list_month, 12, 1);
    if(list_month == 12)
      list_year = Dec(list_year, 99, 0);
  }
}

void incListDate()
{
  list_day = Inc(list_day, dayInMonthF(list_month - 1), 1);
  if(list_day == 1)
  {
    list_month = Inc(list_month, 12, 1);
    if(list_month == 1)
      list_year = Inc(list_year, 99, 0);
  } 
}
