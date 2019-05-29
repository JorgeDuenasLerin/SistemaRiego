void setup() {
  setupRele();
  setupRTC();
  actualizaTiempo();
  
  setupDisplay();
}

void loop() {
  actualizaTiempo();
  
  //displayClockSerial();
  displayInfo();
  configuraTiemposRiego();

  delay(900);
}
