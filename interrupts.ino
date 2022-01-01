ISR(TIMER5_COMPA_vect)
{
  ds3231Check = true;

  static uint8_t counterDHT = 0;
  if(++counterDHT == 2)
  {
    dht22Check = true;
    counterDHT = 0;
  }

  if(second == 0)
    dht22Counter60sec = true;
}
