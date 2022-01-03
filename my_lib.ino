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

String dateString()
{
  return leadingZero(day) + "." + leadingZero(month) + ".20" + leadingZero(year);
}

String dateStringWithoutDot()
{
  String date = dateString();
  date.remove(2, 1);
  date.remove(4, 1);

  return date;
}
