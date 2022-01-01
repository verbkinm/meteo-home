bool alarm1Enable()
{
  return (a1_status_reg >> 7) & 0x01;
}

void toAlarm()
{
  
}

void checkAlarm()
{
  if( alarm1Enable() && ((a1_status_reg >> weekDay) & 0x01))
  {
    if( (hour == a1_hour) && (minute == a1_minute) && (second == 0) )
    {
      clearPage();
      bmpDraw("alarm.bmp", 96, 33);

//      while(1)
//      { 
//        tp = ts.getPoint();  
//        if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE)
//          break;
//        for(uint16_t i = 100; i < 3000; i+=100)
//        {
//          tp = ts.getPoint();  
//          if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE)
//            break;
//          tone(ALARMVCC, i);
//          delay(100);
//        }
//        for(uint16_t i = 3000; i > 100; i-=100)
//        {
//          tp = ts.getPoint();  
//          if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE)
//            break;
//          tone(ALARMVCC, i);
//          delay(100);
//        }
//      }
//      noTone(ALARMVCC);
      pageSelect();
    }
  }
}
