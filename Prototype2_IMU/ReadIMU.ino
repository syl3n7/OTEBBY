void readimu()
{
  sensor.getAcceleration(&ax, &ay, &az);
  sensor.getRotation(&gx, &gy, &gz);
  float ax_m_s2 = ax * (9.81 / 16384.0);
  float ay_m_s2 = ay * (9.81 / 16384.0);
  float az_m_s2 = az * (9.81 / 16384.0);
  // float gx_deg_s = gx * (250.0 / 32768.0);
  // float gy_deg_s = gy * (250.0 / 32768.0);
  // float gz_deg_s = gz * (250.0 / 32768.0);

  // DEBUG PRINTS
  total = float(ax_m_s2 + ay_m_s2 + az_m_s2);
  Serial.println(total);

  delay(100);
}
