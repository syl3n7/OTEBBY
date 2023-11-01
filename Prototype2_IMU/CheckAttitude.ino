void checkAttitude (){
  
  if (babyTemperature <= 18)
  {
    babyAttitude = babyAttitude - 30;
  }
  else if(babyTemperature => 24)
  {
    babyAttitude = babyAttitude - 30;
  }
  else 
  {
    babyAttitude = babyAttitude + 15;
  }  

  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
  
  delay(2000);
}


//cabo sata power
