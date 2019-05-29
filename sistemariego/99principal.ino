const int ACTUALIZA = 1000;

void setup() {
  setupRele();
  setupRTC();
  
  actualizaTiempo();
  iniciarEstado();
  
  setupDisplay();
}

void loop() {
  actualizaTiempo();
  
  displayInfo();

  if(esTiempoDeRiego() && estado == REPOSO){
    configuraTiemposRiego();
    iniciarRiego();
  }

  if(estado != REPOSO){
    procesaSiguienteEstadoRiego();
  }
  

  delay(ACTUALIZA);
}
