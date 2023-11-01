void sleep() {
  if (rfid.PICC_IsNewCardPresent()) {
    myDFPlayer.play(6);  // Play the first mp3
  }
  delay(100);
  makehunger();
  if (babyHunger < 50 || babyThirst < 50){
    wake();
  }
}
