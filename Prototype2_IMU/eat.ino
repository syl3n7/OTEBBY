void eat()
{
  babyHunger = babyHunger + 5;
  if (babyHunger >= 100) 
  {
    babyHunger = 100;
    //if (!hungry) readimu();
    hungry = false;
  }
  delay(defaultDelay);
}

void makehunger()
{
  babyHunger = babyHunger - 7;
  if (babyHunger <= 50) hungry = true;
  if (babyHunger <= 0) babyHunger = 0;
  delay(defaultDelay);
}
