#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

const byte MQ4_Pin = A0;
const int R_0 = 945; 

#include "MQ135.h"

#include "DHT.h"
#define DHTPIN 14
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
   Serial.begin(9600);
   lcd.begin();
   lcd.setCursor(0,0);
   lcd.print("Astra Jenaka");
   
}
 
void loop() {
   Serial.println(getMethanePPM());
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   float f = dht.readTemperature(true);

   if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  MQ135 gasSensor = MQ135(A0);
  float air_quality = gasSensor.getPPM();
  Serial.print("Air Quality: ");  
  Serial.print(air_quality);
  lcd.setCursor(0,0);
  lcd.print("MQ135 = ");
  lcd.print(air_quality);
  
   
}
 
float getMethanePPM(){
   float a0 = analogRead(A0); 
   float v_o = a0 * 5 / 1023;
   float R_S = (5-v_o) * 1000 / v_o;
   float PPM = pow(R_S/R_0,-2.95) * 1000; 
   return PPM;
}
