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




#include <SoftwareSerial.h>
 
SoftwareSerial nodemcu(19,18);
/*
int sensor1 = A0;
int sensor2 = A1; 
int sensor3 = A2; 
 */
int sdata1 = 0; // sensor1 data
int sdata2 = 0; // sensor2 data
int sdata3 = 0; // sensor3 data 

 
String cdata; // complete data, consisting of sensors values
 
void setup()
{
Serial.begin(9600); 
nodemcu.begin(9600);
/*
pinMode(sensor1, INPUT);
pinMode(sensor2, INPUT);
pinMode(sensor3, INPUT);
pinMode(4, OUTPUT); // TO ON/OFF VARIABLE RESISTOR
digitalWrite(4, HIGH); 
*/
}
 
void loop()
{
  /*
    sdata1 = analogRead(sensor1);
    sdata2 = analogRead(sensor2);
    sdata3 = analogRead(sensor3);*/
   sdata1 = 10;
   sdata2 = 11;
   sdata3 = 12;
   cdata = cdata + sdata1+","+sdata2+","+sdata3; // comma will be used a delimeter
   Serial.println(cdata); 
   nodemcu.println(cdata);
   delay(2000); // 100 milli seconds
   cdata = ""; 
 
}
