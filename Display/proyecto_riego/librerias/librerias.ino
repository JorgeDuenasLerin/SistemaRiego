#include <Wire.h>
#include <ThreeWire.h> 
#include <RtcDS1302.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>


/* Display IIC OLED SSD1306 */

// OLED display TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(4);

/*
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
*/

/* Display IIC OLED SSD1306 */



/* Reloj DS1302 RTC */

ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

#define countof(a) (sizeof(a) / sizeof(a[0]))

/* Reloj DS1302 RTC */












/*

Documentación del código:

Conexiones:

Para el display uso
  A4 -> SDA
  A5 -> SCL

Para el reloj uso:
  D5 -> CLK
  D4 -> DAT
  D2 -> RST
*/




/* Riego - RELES */

enum ESTADO_SISTEMA__RIEGO {
  REPOSO,
  ABRIENDO,
  REGANDO,
  CERRANDO
};


// const int SEG_ABRIR_CERRAR = 10;
// const int MIN_RIEGO        = 15;

const int SEG_SEGURIDAD    = 10;

const int SEG_ABRIR_CERRAR = 1; // Testing
const int MIN_RIEGO        = 1;// Testing


// Calculados
const int SEG_RIEGO        = 60 * MIN_RIEGO;

// Conexiones

const int ABRIR    = 11;  // Relé1
const int BOMBA    = 10;  // Relé2
const int CERRAR   = 9;  // Relé3

void setupRele(){
  pinMode(ABRIR, OUTPUT);
  pinMode(BOMBA, OUTPUT);
  pinMode(CERRAR, OUTPUT);
}

RtcDateTime tAbrir;
RtcDateTime tRegar;
RtcDateTime tCerrar;

/*
Establece cuando se terminará cada evento
*/
void configuraTiemposRiego(){
  RtcDateTime now = Rtc.GetDateTime();

  tAbrir  = now + SEG_ABRIR_CERRAR;
  tRegar  = now + SEG_ABRIR_CERRAR + SEG_RIEGO;
  tCerrar = now + SEG_ABRIR_CERRAR + SEG_RIEGO + SEG_ABRIR_CERRAR;

  Serial.println("Se configuran los tiempos del riego");

  printDateTime(tAbrir);
  printDateTime(tRegar);
  printDateTime(tCerrar);
  
  /*
  // Abrimos grifo
  digitalWrite(ABRIR, HIGH);
  delay(2500);
  digitalWrite(ABRIR, LOW);
  delay(2500);

  // Potencia a la bomba
  digitalWrite(BOMBA, HIGH);
  delay(2500);
  digitalWrite(BOMBA, LOW);
  delay(2500);

  // Abrimos grifo
  digitalWrite(CERRAR, HIGH);
  delay(2500);
  digitalWrite(CERRAR, LOW);
  delay(2500);

  digitalWrite(ABRIR, LOW);
  digitalWrite(BOMBA, LOW);
  digitalWrite(CERRAR, LOW);
  */
}
