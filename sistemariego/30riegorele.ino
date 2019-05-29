/* Riego - RELES */

// Conexiones

const int ABRIR    = 11;  // Relé1
const int BOMBA    = 10;  // Relé2
const int CERRAR   = 9;  // Relé3

void setupRele(){
  pinMode(ABRIR, OUTPUT);
  pinMode(BOMBA, OUTPUT);
  pinMode(CERRAR, OUTPUT);
}

bool estadoAbrirRiego = false;
void onAbrirRiego(){
  if(!estadoAbrirRiego) {
    estadoAbrirRiego = true;
    digitalWrite(ABRIR, HIGH);
  }
}

void offAbrirRiego(){
  estadoAbrirRiego = false;
  digitalWrite(ABRIR, LOW);
}

bool estadoRiego = false;
void onRiego(){
  if(!estadoRiego) {
    estadoRiego = true;
    digitalWrite(BOMBA, HIGH);
  }
}

void offRiego(){
  estadoRiego = false;
  digitalWrite(BOMBA, LOW);
}

bool estadoCerrarRiego = false;
void onCerrarRiego(){
  if(!estadoCerrarRiego) {
    estadoCerrarRiego = true;
    digitalWrite(CERRAR, HIGH);
  }
}

void offCerrarRiego(){
  estadoCerrarRiego = false;
  digitalWrite(CERRAR, LOW);
}
