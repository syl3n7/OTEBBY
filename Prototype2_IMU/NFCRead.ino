void readNFC()
{
    if (rfid.PICC_IsNewCardPresent()) {
      myDFPlayer.volume(100); // Set volume value. From 0 to 30
      myDFPlayer.play(3);     // Play the first mp3
    }
}
