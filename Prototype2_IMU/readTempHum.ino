void readTempHum() {
  babyHumidity = dht2.readHumidity();
  babyTemperature = 10 + dht2.readTemperature();
  delay(150);
}