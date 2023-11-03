void wake()
{
  sleeping = false;
  Serial.println("AWAKE");
  if (babyAttitude > 70)
  {
    myDFPlayer.play(1);
    delay(soundDelay);
  }
  else if (babyAttitude < 20)
  {
    myDFPlayer.play(10);
    delay(soundDelay);
  }
  else
  {
    myDFPlayer.play(12);
    delay(soundDelay);
  }
  checkAttitude();
}
