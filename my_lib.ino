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
