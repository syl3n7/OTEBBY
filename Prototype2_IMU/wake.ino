void wake(){
  if (babyAttitude > 70){
    myDFPlayer.play(1);
    LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
  }else if(babyAttitude <20){
    myDFPlayer.play(10);
  }else {
    myDFPlayer.play(12);
    LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
  }
  delay(10000);
}
