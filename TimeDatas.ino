
//____________________________________________________________________________ 

void localTime() {
  
     Serial.println("Connexion time");
     struct tm timeinfo;
     if(!getLocalTime(&timeinfo)){
        Serial.println("Failed to obtain time");
        return;
       }

     Serial.println();
     Serial.println("Time variables");
     char timeWeekDay[10];
     strftime(timeWeekDay,10, "%A", &timeinfo);
     Serial.println(timeWeekDay);
     char timeHour[3];
     strftime(timeHour,3, "%H", &timeinfo);
     Serial.print(timeHour); Serial.print(":");
     char timeMinute[3];
     strftime(timeMinute,3, "%M", &timeinfo);
     Serial.println(timeMinute);    

     hh = String(timeHour).toInt();
     mm = String(timeMinute).toInt();

     Serial.print("jour de la semaine (lundi = 1)    %u > "); Serial.println(&timeinfo, "%u");

     Serial.print("jour format 01 a 31               %d > "); Serial.println(&timeinfo, "%d");
     Serial.print("mois format 1 a 12                %m > "); Serial.println(&timeinfo, "%m");

     Serial.print("heure format 24h                  %H > "); Serial.println(&timeinfo, "%H");
     Serial.print("minutes                           %M > "); Serial.println(&timeinfo, "%M");
     
}
