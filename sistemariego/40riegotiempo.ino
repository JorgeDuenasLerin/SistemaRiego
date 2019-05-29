RtcDateTime tAbrirINI;
RtcDateTime tAbrirFIN;
RtcDateTime tRegarINI;
RtcDateTime tRegarFIN;
RtcDateTime tCerrarINI;
RtcDateTime tCerrarFIN;


const int SEG_SEGURIDAD    = 12;

const int SEG_ABRIR_CERRAR = 10;

// const int MIN_RIEGO        = 15;
const int MIN_RIEGO        = 1;// Testing
const int SEG_RIEGO        = 20;//60 * MIN_RIEGO;


bool esTiempoDeRiego() {
  int h = tAhora.Hour();
  int m = tAhora.Minute();
  int s = tAhora.Second();

  return ((m % 2) == 0 ) && s > 0 && s < 10;
}

/*
Establece cuando se terminará cada evento
*/
void configuraTiemposRiego(){
  tAbrirINI = tAhora + SEG_SEGURIDAD;
  tAbrirFIN = tAbrirINI + SEG_ABRIR_CERRAR;
  tRegarINI = tAbrirFIN + SEG_SEGURIDAD;
  tRegarFIN = tRegarINI + SEG_RIEGO;
  tCerrarINI = tRegarFIN + SEG_SEGURIDAD;
  tCerrarFIN = tCerrarINI + SEG_ABRIR_CERRAR + SEG_SEGURIDAD;

  Serial.println("Se configuran los tiempos del riego");

  printDateTime(tAbrirINI);
  printDateTime(tAbrirFIN);
  printDateTime(tRegarINI);
  printDateTime(tRegarFIN);
  printDateTime(tCerrarINI);
  printDateTime(tCerrarFIN);
  
}

void iniciarRiego() {
  estado = ABRIENDO;
}

void procesaSiguienteEstadoRiego(){
  if(tAhora > tCerrarFIN) {
    estado = REPOSO;
    offCerrarRiego();
    return;
  }
  
  if(tAhora > tCerrarINI) {
    estado = CERRANDO;
    onCerrarRiego();
    return;
  }
  
  if(tAhora > tRegarFIN) {
    offRiego();
    return;
  }
  
  if(tAhora > tRegarINI) {
    estado = REGANDO;
    onRiego();
    return;
  }
  
  if(tAhora > tAbrirFIN) {
    offAbrirRiego();
    return;
  }
  
  if(tAhora > tAbrirINI) {
    estado = ABRIENDO;
    onAbrirRiego();
    return;
  }
}
