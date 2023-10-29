void readNFC() {
  if (rfid.PICC_IsNewCardPresent()) {
    //milis()
    myDFPlayer.volume(100);  // Set volume value. From 0 to 30
    myDFPlayer.play(6);  // Play the first mp3
    // delay(10000);
    // myDFPlayer.stop();
  }
}
