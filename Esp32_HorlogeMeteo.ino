//     ---------------------------------------------------------------------------------
//     ESP32 Prototype Horloge analogique, numerique et Station meteo OpenWeatherOneCall
//     Projet de base a completer par 
//     - affichage date dans cercle horloge jour de la semaine complet
//     - jour et mois format JJ/MM
//     ---------------------------------------------------------------------------------
//     Sources d'inspiration
//     ---------------------
//     https://github.com/Bodmer/TFT_eSPI/blob/master/examples/320%20x%20240/TFT_Clock/TFT_Clock.ino
//     https://github.com/Bodmer/TFT_eSPI/blob/master/examples/Generic/TFT_SPIFFS_BMP/TFT_SPIFFS_BMP.ino
//     https://github.com/ThingPulse/esp8266-weather-station/blob/master/examples/OpenWeatherMapCurrentDemo/OpenWeatherMapCurrentDemo.ino
//     https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/
//     https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/#more-75765
//     https://fr.freepik.com/vecteurs-libre/jeu-icones-meteo_1538501.htm#query=M%C3%A9t%C3%A9o%20icones&position=22&from_view=search&track=ais
//     https://www.gimp.org/downloads/
//
/*
//     Schema de connexion ILI9488 et fichier User_Setup de TFT_eSPI
//     -------------------------------------------------------------

#define USER_SETUP_INFO "User_Setup"

//#define ILI9341_DRIVER       // Generic driver for common displays
#define ILI9488_DRIVER
//_______________________________________________________
#define TFT_MOSI 27
#define TFT_SCLK 14
#define TFT_CS   25
#define TFT_DC   26
#define TFT_RST  -1//  RST 3,3vcc
#define TFT_MISO 12
#define TOUCH_CS 13
//-------------------------------------------------------
#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT
#define SPI_FREQUENCY       40000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000
//_______________________________________________________________________________
*/
//      NE PAS OUBLIER DE CHARGER 'data' par " Outils, ESP32 Sketch Data Upload "
//_______________________________________________________________________________


#define FS_NO_GLOBALS
#include <FS.h>

#ifdef ESP32
  #include "SPIFFS.h"  // For ESP32 only
#endif

//____________________________________________________________________________
#include <TFT_eSPI.h> 
          TFT_eSPI tft = TFT_eSPI(); 

//____________________________________________________________________________
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiUdp.h>
    const char *ssid     = "@@@@@@@@@@";
    const char *password = "@@@@@@@@@@";
          WiFiMulti WiFiMulti; 
      int TryNum = 0;

//____________________________________________________________________________      
#include "time.h"
const char* ntpServer = "de.pool.ntp.org";
const long  gmtOffset_sec = 0;//3600;
const int   daylightOffset_sec = 3600;
     bool firstTimeCall = true;
      int timeCall = (55)*1000;// pour 55 secondes en microsecondes
 unsigned long lastTimeCall;
 
//____________________________________________________________________________      
#include <OpenWeatherOneCall.h>
#define   ONECALLKEY "@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
    float myLATITUDE = 48.4769;
    float myLONGITUDE = 7.67806;
//      int myCITYID = 2857798;  
      int myUNITS = METRIC; 
      int myHISTORY = NULL;
//      int myEXCLUDES = EXCL_D+EXCL_H+EXCL_M+EXCL_A;
          OpenWeatherOneCall OWOC; 
      int oneCall = (15*60)*1000;// pour 15 minutes en microsecondes
//      int oneCall = (3)*1000;// pour secondes en microsecondes pour test
 unsigned long lastCall;
     bool firstCall = true;
     bool foreCast = false;
      int foreCastDayLine; 
      int iconeCode, iconeTft;
   String iconeCast;
    float VentVitesse, Direction;
   String VentDirection;
const char* iconeBmp[16] = { "_",
                             "/01d.bmp", "/01n.bmp", "/02d.bmp", "/02n.bmp", 
                             "/03dn.bmp", "/04dn.bmp", "/04dn.bmp",
                             "/10d.bmp", "/10n.bmp"," /11d.bmp",  "/11n.bmp",
                             "/13dn.bmp", "/50dn.bmp", 
                             "/maxi.bmp", "/mini.bmp" };
   
//____________________________________________________________________________ 
    float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0;       // Saved H, M, S x & y multipliers
    float sdeg=0, mdeg=0, hdeg=0;
 uint16_t osx=120, osy=120, omx=120, omy=120, ohx=120, ohy=120;  // Saved H, M, S x & y coords
 uint16_t x0=0, x1=0, yy0=0, yy1=0;
      int hh, mm;
   String mmTxt, hhTxt;
   
//____________________________________________________________________________ 


void connectWifi() {
  
     Serial.print("Connection .");
     WiFiMulti.addAP(ssid, password);
     while (WiFiMulti.run() != WL_CONNECTED) {
            Serial.print ( "." );
            delay ( 50 );
            TryNum++;
            if (TryNum > 20) {
                Serial.print("\nConnection impossible !\n");
                if (WiFi.status() != WL_CONNECTED) {
                    ESP.restart();
                   }
                delay(50);
                for (;;);
               }
           }
     Serial.print("\nconnecte a "); Serial.println(ssid);
     
} 

//____________________________________________________________________________ 


void setup() {

     Serial.begin(115200); Serial.print("\n\n");

     tft.init();
     tft.setRotation(1);
     tft.fillScreen(TFT_BLACK);  
     tft.setTextColor(TFT_WHITE); 
     tft.drawString("Initialisation systeme", 150, 110, 4);   
     tft.setTextColor(TFT_CYAN);//            affiche logo connexion
     tft.drawString("@", 110, 110, 4);
     
     if (!SPIFFS.begin()) {
         Serial.println("SPIFFS initialisation failed!");
         while (1) yield();
        }
     Serial.println("\r\nSPIFFS Ok");

     while (WiFi.status() != WL_CONNECTED) {
            connectWifi();
           }  

      tft.setTextColor(TFT_BLACK);//           efface logo connexion
      tft.drawString("@", 110, 110, 4);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
              
     configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

     OWOC.setOpenWeatherKey(ONECALLKEY);
     OWOC.setLatLon(myLATITUDE, myLONGITUDE);
//     OWOC.setLatLon(myCITYID); 
     OWOC.setUnits(myUNITS);

     horlogeCadran();
         
}


void loop() {

     if (WiFi.status() != WL_CONNECTED) {
         ESP.restart();
        }
     delay(50);

     if (((millis() - lastTimeCall) > timeCall) || (firstTimeCall == true)) {
         lastTimeCall = millis();
         firstTimeCall = false;
         tft.setTextColor(TFT_CYAN);//            affiche logo connexion
         tft.drawString("@", 110, 110, 4);
         localTime();
         tft.setTextColor(TFT_BLACK);//           efface logo connexion
         tft.drawString("@", 110, 110, 4);
         tft.setTextColor(TFT_WHITE, TFT_BLACK);
         horlogeAfficheTemps();
        }

     if (((millis() - lastCall) > oneCall) || (firstCall == true)) {
         lastCall = millis();
         firstCall = false;
         tft.setTextColor(TFT_CYAN);//            affiche logo connexion
         tft.drawString("@", 110, 110, 4);
         currentCast();
         tft.setTextColor(TFT_BLACK);//           efface logo connexion
         tft.drawString("@", 110, 110, 4);
         tft.setTextColor(TFT_WHITE, TFT_BLACK);
         afficheIconeCast();
         afficheMeteo();
        }
        
}
