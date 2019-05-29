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

Conexiones:

Para el display uso
  A4 -> SDA
  A5 -> SCL
  VCC -> 3.3
Fuente:
  https://www.amazon.es/Yellow-Serial-Arduino-Display-Raspberry/dp/B07MFQ8DMG
  Voltage: 3V ~ 5V DC

Para el reloj uso:
  D5 -> CLK
  D4 -> DAT
  D2 -> RST
Fuente:
  https://www.velleman.eu/products/view?id=435516&country=us&lang=es
  bajo consumo de potencia: tensión de funcionamiento de 2.0 V a 5.5 V

Relé
  D11 -> 1
  D10 -> 2
  D9  -> 3
Fuente:
  https://www.velleman.eu/products/view?id=435558&country=be&lang=es
  corriente de entrada (de in1 a in4): 5 - 15 mA
  tensión de entrada: 5 - 12 VDC
  salida de relé: 30 VDC 10 A (no inductivo)

*/


void foo() {

}
