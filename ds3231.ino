void readDS3231()
{
  year = ds3231.getYear();
  month = ds3231.getMonth(century);
  day = ds3231.getDate();
  weekDay = ds3231.getDoW();
  if(weekDay == 7)
    weekDay = 0;

  hour = ds3231.getHour(h12Flag, pmFlag);
  minute = ds3231.getMinute();
  second = ds3231.getSecond();

  connection_DS3231 = true;
  if(year == 165)
    connection_DS3231 = false;
}

void writeDS3231()
{
  ds3231.setClockMode(false);  // set to 24h
  ds3231.setYear(year);
  ds3231.setMonth(month);
  ds3231.setDate(day);
  ds3231.setDoW(weekDay);
  ds3231.setHour(hour);
  ds3231.setMinute(minute);
  ds3231.setSecond(second);
}
