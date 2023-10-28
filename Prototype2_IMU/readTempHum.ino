void readTempHum() {
  float umi  = dht2.readHumidity();
  float tempC = dht2.readTemperature();
  Serial.println();
  Serial.println("Humidade: ");
  Serial.print(umi);
  Serial.println("Temp: ");
  Serial.print(tempC);
  Serial.println();
}