void displayInfo() {
  display.clearDisplay();
  display.setCursor(1,1);
  
  char datestring[20]="asd";
  getStringDateFormated(datestring, 20, tAhora);
  

  int m = tAhora.Minute();
  int s = tAhora.Second();
  display.print(datestring);

  if(m%2==0){
    display.drawCircle(84, 15, 6, WHITE);
    if(s<2) {
      configuraTiemposRiego();
    }
  }
  
  // update display with all of the above graphics
  display.display();
}

void displayClockSerial() {
    RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now);
    Serial.println();
    /*
    if (!now.IsValid())
    {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }*/
}


void setupDisplay(){
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(1,1);
}
