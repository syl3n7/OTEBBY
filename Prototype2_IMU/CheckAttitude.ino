void checkAttitude ()
{
  
  if (babyTemperature <= 18)
  {
    babyAttitude = babyAttitude - 30;
  }
  else if(babyTemperature >= 24)
  {
    babyAttitude = babyAttitude - 30;
  }
  else 
  {
    babyAttitude = babyAttitude + 15;
  }  

}
