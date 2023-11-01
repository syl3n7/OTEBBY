int readTempHum() {
  babyHumidity = dht2.readHumidity();
  babyTemperature = dht2.readTemperature();
}
