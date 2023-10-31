void eat(){
  babyThirst = babyThirst + 3;
  babyHunger = babyHunger + 1;
  delay(10);
}

void makehunger(){
  babyThirst = babyThirst - 3;
  babyHunger = babyHunger - 1;
  delay(10);
}