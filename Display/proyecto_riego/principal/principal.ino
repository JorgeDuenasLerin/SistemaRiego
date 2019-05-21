#include <Wire.h>
#include <ThreeWire.h> 
#include <RtcDS1302.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

/*

Display IIC OLED SSD1306

*/

// OLED display TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(4);

/*
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
*/

void setupDisplay(){
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(1,1);
}

/*

Reloj DS1302 RTC

*/
ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

#define countof(a) (sizeof(a) / sizeof(a[0]))

void getStringDateFormated(char salida[], int salidaSize, const RtcDateTime& dt) {
    snprintf_P(salida, 
            salidaSize,
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
}

void printDateTime(const RtcDateTime& dt) {
    char datestring[20];

    getStringDateFormated(datestring, 20, dt);
    
    Serial.print(datestring);
}

void setupRTC(){
  Serial.begin(57600);

  Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);

  Rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println();

  /*if (!Rtc.IsDateTimeValid()) 
  {
      // Common Causes:
      //    1) first time you ran and the device wasn't running yet
      //    2) the battery on the device is low or even missing

      Serial.println("RTC lost confidence in the DateTime!");
      Rtc.SetDateTime(compiled);
  }*/
  // Rtc.SetDateTime(compiled);

  if (Rtc.GetIsWriteProtected())
  {
      Serial.println("RTC was write protected, enabling writing now");
      Rtc.SetIsWriteProtected(false);
  }

  if (!Rtc.GetIsRunning())
  {
      Serial.println("RTC was not actively running, starting now");
      Rtc.SetIsRunning(true);
  }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled) 
  {
      Serial.println("RTC is older than compile time!  (Updating DateTime)");
      Rtc.SetDateTime(compiled);
  }
  else if (now > compiled) 
  {
      Serial.println("RTC is newer than compile time. (this is expected)");
      Rtc.SetDateTime(compiled);
  }
  else if (now == compiled) 
  {
      Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }
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

char buffer[100];

void displayInfo() {
  display.clearDisplay();
  display.setCursor(1,1);
  
  RtcDateTime now = Rtc.GetDateTime();    
  
  char datestring[20]="asd";
  getStringDateFormated(datestring, 20, now);
  

  int m = now.Minute();
  int s = now.Second();
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

const int ABRIR    = 10;  // Relé1
const int BOMBA    = 9;  // Relé2
const int CERRAR   = 8;  // Relé3

void setupRele(){
  pinMode(ABRIR, OUTPUT);
  pinMode(BOMBA, OUTPUT);
  pinMode(CERRAR, OUTPUT);
}

RtcDateTime tAbrir  = NULL;
RtcDateTime tRegar  = NULL;
RtcDateTime tCerrar = NULL;

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
  delay(TIEMPO_ABRIR);
  digitalWrite(ABRIR, LOW);
  delay(TIEMPO_SEGURIDAD);

  // Potencia a la bomba
  digitalWrite(BOMBA, HIGH);
  delay(TIEMPO_RIEGO);
  digitalWrite(BOMBA, LOW);
  delay(TIEMPO_SEGURIDAD);

  // Abrimos grifo
  digitalWrite(CERRAR, HIGH);
  delay(TIEMPO_ABRIR);
  digitalWrite(CERRAR, LOW);
  delay(TIEMPO_SEGURIDAD);

  digitalWrite(ABRIR, LOW);
  digitalWrite(BOMBA, LOW);
  digitalWrite(CERRAR, LOW);
  */
}

void setup() {
  setupRele();
  setupRTC();
  setupDisplay();
}

void loop() {
  
  //displayClockSerial();
  displayInfo();
  

  delay(900);
}
