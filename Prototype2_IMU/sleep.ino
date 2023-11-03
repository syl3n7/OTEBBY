void sleep()
{
  // if the nfc reader detects the bed and the baby isnt hungry or if it detects the bed and it has a good attitude, then he sleeps.
  myDFPlayer.play(6); // Play the mp3 with baby sleep sounds
  makehunger();
  Serial.println("getting hungry! slp");
  if (sleeping)
    Serial.println("going to sleep");
  if (hungry)
    wake();
  delay(5000); // sleep for a minute //changed to 5 seconds for the demo
}
