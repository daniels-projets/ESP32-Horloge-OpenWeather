
//____________________________________________________________________________ 

void currentCast(){

     Serial.println("Connexion cast");
     OWOC.parseWeather();
     Serial.print("Meteo id   : "); Serial.println(OWOC.current->id);
     iconeCode = (OWOC.current->id);
     Serial.print("Meteo icone: "); Serial.println(OWOC.current->icon);
     iconeCast = (OWOC.current->icon);         
     Serial.print("Temperature: "); Serial.println(OWOC.current->temperature);
     Serial.print("Ressenti:    "); Serial.println(OWOC.current->apparentTemperature);
     Serial.print("Humidite   : "); Serial.println(OWOC.current->humidity);
     Serial.print("Vent: ");
     VentVitesse = (OWOC.current->windSpeed) * 3.6;
     Serial.print(VentVitesse); Serial.print(" Km/H direction: ");
     Direction = (OWOC.current->windBearing);
     if (Direction > 337.5 || Direction <= 22.5) { Serial.println("Nord"); VentDirection = "Nord"; }
     if (Direction > 22.5 && Direction <= 67.5) { Serial.println("Nord Est"); VentDirection = "N.Est"; }
     if (Direction > 67.5 && Direction <= 112.5) { Serial.println("Est"); VentDirection = "Est"; }
     if (Direction > 112.5 && Direction <= 157.5) { Serial.println("Sud Est"); VentDirection = "S.Est"; }
     if (Direction > 157.5 && Direction <= 202.5) { Serial.println("Sud"); VentDirection = "Sud"; }
     if (Direction > 202.5 && Direction <= 247.5) { Serial.println("Sud Ouest"); VentDirection = "S.Ouest"; }
     if (Direction > 247.5 && Direction <= 292.5) { Serial.println("Ouest"); VentDirection = "Ouest"; }
     if (Direction > 292.5 && Direction <= 337.5) { Serial.println("Nord Ouest"); VentDirection = "N.Ouest"; }  
     Serial.print("Description:   "); Serial.print(OWOC.current->main);
     Serial.print(", "); Serial.println(OWOC.current->summary);
     Serial.print("Qualite le l'air: "); Serial.println(OWOC.quality->aqi);
  
}
