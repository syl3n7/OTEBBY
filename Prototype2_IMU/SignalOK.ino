void signalAOK()
{
    // make sound and signal thats everything OK
    digitalWrite(2, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(100);
    digitalWrite(2, LOW); // turn the LED off by making the voltage LOW
    delay(100);
    digitalWrite(2, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(100);
    digitalWrite(2, LOW); // turn the LED off by making the voltage LOW
}

// BabyCryingHard1.mp3 - Name of the first audio file to play (testing only) its placed on the root of the sd card.
