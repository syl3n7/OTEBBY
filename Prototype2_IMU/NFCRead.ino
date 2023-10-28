void readNFC()
{
    if (rfid.PICC_IsNewCardPresent()) {
      Serial.println("going to play some audio");
      myDFPlayer.volume(100); // Set volume value. From 0 to 30
      myDFPlayer.play(2);     // Play the first mp3
      delay(2000);
    }
}
