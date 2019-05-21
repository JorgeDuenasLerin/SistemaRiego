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
}

int i = 0;
void displayCounter() {
  display.clearDisplay();
  // display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 31, WHITE);
  display.drawPixel(127, 31, WHITE);

  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(1,1);
  display.print("Info de riego!");
  display.print(i);
  i++;
  i=i%10;
  display.drawCircle(64, 15, 4, WHITE);
  // update display with all of the above graphics
  display.display();
}


/*

Reloj DS1302 RTC

*/



ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt) {
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
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
  Rtc.SetDateTime(compiled);

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

void displayClock() {
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



void setup() {
  setupRTC();
  setupDisplay();

}



void loop() {
  
  displayCounter();
  displayClock();
  delay(1500);
}
