/*
const char* iconeBmp[15] = { "_",
                             "/01d.bmp", "/01n.bmp", "/02d.bmp", "/02n.bmp",
                             "/03dn.bmp", "/04dn.bmp", "/09dn.bmp", 
                             "/10d.bmp", "/10n.bmp"," /11d.bmp",  "/11n.bmp",
                             "/13dn.bmp", "/50dn.bmp", 
                             "/maxi.bmp", "/mini.bmp" };
*/

void afficheIconeCast() {

     tft.fillRect(250, 0, 250, 380, TFT_BLACK);
     tft.drawString(String(hh)+" : " + mmTxt, 400, 15, 2);  
         
     if (iconeCast == "01d") { iconeTft = 1; }
     if (iconeCast == "01n") { iconeTft = 2; }
     if (iconeCast == "02d") { iconeTft = 3; }
     if (iconeCast == "02n") { iconeTft = 4; }
     if (iconeCast == "03d" || iconeCast == "03n") { iconeTft = 5; }
     if (iconeCast == "04d" || iconeCast == "04n") { iconeTft = 6; }
     if (iconeCast == "09d" || iconeCast == "09n") { iconeTft = 7; }
     if (iconeCast == "10d") { iconeTft = 8; }
     if (iconeCast == "10n") { iconeTft = 9; }
     if (iconeCast == "11d") { iconeTft = 10; }
     if (iconeCast == "11n") { iconeTft = 11; }
     if (iconeCast == "13d" || iconeCast == "13n") { iconeTft = 12; }
     if (iconeCast == "50d" || iconeCast == "50n") { iconeTft = 13; }

     drawBmp(iconeBmp[iconeTft], 250, 5); delay(50);
     drawBmp("/humid.bmp", 288, 130);
     drawBmp("/pression.bmp", 288, 190);
     drawBmp("/vent.bmp", 288, 250);         

}

//____________________________________________________________________________ 

void afficheMeteo() {

     tft.drawString(String(int(OWOC.current->temperature)), 380, 45, 7); 
     tft.drawString("O", 460, 45, 4); 
     tft.drawString(String(int(OWOC.current->humidity)), 380, 128, 7); 
     tft.drawString("o", 450, 125, 4); tft.drawString("/", 462, 140, 4); tft.drawString("o", 466, 150, 4); 
     tft.drawString(String(int(OWOC.current->pressure)), 360, 206, 4); 
     tft.drawString("hPa", 430, 206, 4); 
     tft.drawString(String(VentVitesse) + " km/h ", 360, 252, 4);
     tft.drawString("> " + VentDirection, 360, 277, 4);
          
}
