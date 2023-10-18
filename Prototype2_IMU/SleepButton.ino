void sleepbutton()
{
    if (digitalRead(6) == LOW)
    {
        Serial.println("I'm full!");
        digitalWrite(7, LOW);
    }
    else
    {
        Serial.println("I'm hungry!");
        digitalWrite(7, HIGH);
    }
}