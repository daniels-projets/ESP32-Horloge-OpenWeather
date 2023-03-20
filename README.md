# ESP32-Horloge-OpenWeather

Projet pour Station météo utilisant OpenWeatherOneCall combiné à une horloge analogique et digitale.
Materiel requis.
  . Esp32 Dev Kit V4
  . Tft 3,5' Ili9488
  
Sources d'inspiration/

Horloge analogique

 https://github.com/Bodmer/TFT_eSPI/blob/master/examples/320%20x%20240/TFT_Clock/TFT_Clock.ino

Stockage images bmp dans SPITTF de Esp32

 https://github.com/Bodmer/TFT_eSPI/blob/master/examples/Generic/TFT_SPIFFS_BMP/TFT_SPIFFS_BMP.ino

Base de connaissances pour datas de OpenWeatherMapCast

 https://github.com/ThingPulse/esp8266-weather-station/blob/master/examples/OpenWeatherMapCurrentDemo/OpenWeatherMapCurrentDemo.ino

Base de Connaissances pour datas NTP Time

 https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/

Base pour installation SPIFFS files uploader

 https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/#more-75765

Source des icones utilisées (dont certaines sont modifiées avec Gimp)

 https://fr.freepik.com/vecteurs-libre/jeu-icones-meteo_1538501.htm#query=M%C3%A9t%C3%A9o%20icones&position=22&from_view=search&track=ais

Lien officiel de telechargement du logiciel Gimp

 https://www.gimp.org/downloads/
 
 
 
*
![Copie ecran](https://user-images.githubusercontent.com/126287326/226423286-7b93348f-e707-41e5-bc1a-96fcd28c66b2.jpg)



*
Il faut aussi créer le onglets pour les sous programmes
(voir copie d´ecran)

![Esp32_HorlogeMeteo](https://user-images.githubusercontent.com/126287326/226418485-30eed734-c6a0-4089-883b-1fe460e52538.jpeg)



*
Il faut aussi placer le fichier ´data´ comprennant les images

![Structure](https://user-images.githubusercontent.com/126287326/226419532-a313b098-029d-4b3d-a0c7-c04795191fd1.jpeg)

