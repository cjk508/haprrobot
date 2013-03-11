void ADC_IRQHandler(void) {
  //Disable further interrupts for now
  NVIC_DisableIRQ(ADC_IRQn);
  abortMode = 1;
  
  //0 = FL, 1 = BL, 2 = BR, 4 = FR
  //Read the value
  uint16_t fl = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_0);
  uint16_t bl = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_1);
  uint16_t fr = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_4);
  uint16_t br = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_2);
  
  if (fl < 10 && bl > 50 && fr > 50 && br > 50) {
    //Set to Follow Line Mode
    stateOverride = 0;
    cmdDoPlay("<b");
    return;
  }
  
  if (fl < 50 && bl > 50 && fr > 10 && br > 50) {
    //Set to Follow Wall Mode
    stateOverride = 1;
    cmdDoPlay("<c");
    return;
  }
  
  if (fl < 50 && bl > 10 && fr > 50 && br > 50) {
    //Set to Mouse Tracking Mode
    stateOverride = 2;
    cmdDoPlay("<d");
    return;
  }
  
  if (fl < 50 && bl > 50 && fr > 50 && br > 10) {
    //Set to Docking Mode
    stateOverride = 1;
    cmdDoPlay("<e");
    return;
  }
  
  if (fl < 50 && bl > 10 && fr > 50 && br > 10) {
    //Set to Short Course Mode
    courseType = 0;
    cmdDoPlay("<ff");
    return;
  }
  
  if (fl < 10 && bl > 50 && fr > 10 && br > 50) {
    //Set to Long Course Mode
    cmdDoPlay("<gg");
    courseType = 1;
    return;
  }
  
  NVIC_EnableIRQ(ADC_IRQ);
  abortMode = 0;
}

void waitForInitialInputThenGo(void) {
  //Initialise ADC IRQ Handlers


  NVIC_EnableIRQ(ADC_IRQn);
  //5s of beep, then wait
  cmdDoPlay("bRbRbRbRb");
  int i;
  for (i = 0; i < 10; i++) {
    //If an option has been triggered, start
    delay(500);
    if (abortMode) break;
  }
  NVIC_DisableIRQ(ADC_IRQn);
  doTheDemo();
}
