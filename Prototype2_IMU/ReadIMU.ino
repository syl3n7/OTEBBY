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
  float total1 = ax + ay + az;
  float total2 = ax + ay + az;
  float total3 = ax + ay + az;

//  while(!hungry && babyHunger >= 90){
//    
//    if(total1 >= 300 && total2 >= 300 && total3 >= 300)
//    {
//      babyAttitude = babyAttitude + 5;
//      if (babyAttitude >= 100) babyAttitude = 100;
//      int a = random(0,13);
//      if(a == 3 || a == 7 || a == 11) sleep(); // can sleep in the arms if we get number 3, 7, or 11.
//    }
//    
//  }
  Serial.print(" ");
  Serial.print(total);

  delay(100);
}
