void checkAttitude()
{
 //temperature affects attitude
 if (babyTemperature <= 18)
  {
    babyAttitude = babyAttitude - 2;
    if (babyAttitude <= 0) babyAttitude = 0;
  }
  else if (babyTemperature > 27)
  {
    babyAttitude = babyAttitude - 3;
    if (babyAttitude <= 0) babyAttitude = 0;
  }
  else
  {
    babyAttitude = babyAttitude + 10;
    if (babyAttitude >= 100) babyAttitude = 100;
  }
  Serial.print(" T");
  Serial.print(babyTemperature);
  Serial.print(" A");
  
  //hunger affects attitude
  if (babyHunger < 50)
  {
    babyAttitude = babyAttitude - 11;
    if (babyAttitude <= 0) babyAttitude = 0;
  }
  else if (babyHunger > 70)
  {
    babyAttitude = babyAttitude + 7;
    if (babyAttitude >= 100) babyAttitude = 100;
  }
  else
  {
    babyAttitude = babyAttitude + 5;
    if (babyAttitude >= 100) babyAttitude = 100;
  }
  Serial.print(babyAttitude);
  Serial.print(" H");
  Serial.print(babyHunger);
  Serial.print(" ");
}
