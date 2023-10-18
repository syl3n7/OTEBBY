void btRead() {
  if (btserial.available()) btIN = btserial.read();
  delay(1000);
}
