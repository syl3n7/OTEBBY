void eat()
{
  babyHunger = babyHunger + 5;
  if (babyHunger >= 85) 
  {
    babyHunger = 100;
    if (!hungry) readimu();
    hungry = false;
  }
  delay(defaultDelay);
}

void makehunger()
{
  babyHunger = babyHunger - 5;
  if (babyHunger <= 30) 
  {
    babyHunger = 0;
    hungry = true;
  }
  delay(defaultDelay);
}
