void readNFC()
{
    if (rfid.PICC_IsNewCardPresent())
    { // new tag is available
        if (rfid.PICC_ReadCardSerial())
        { // NUID has been readed
            MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
            Serial.print("RFID/NFC Tag Type: ");
            Serial.println(rfid.PICC_GetTypeName(piccType));

            // print NUID in Serial Monitor in the hex format
            Serial.print("UID:");
            for (int i = 0; i < rfid.uid.size; i++)
            {
                Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
                Serial.print(rfid.uid.uidByte[i], HEX + "\n");
            }

            rfid.PICC_HaltA();      // halt PICC
            rfid.PCD_StopCrypto1(); // stop encryption on PCD
        }
        signalAOK();
    }
}
