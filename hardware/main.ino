#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#include <MQUnifiedsensor.h>

#define         Board                   ("Arduino NANO")
#define         Pin4                     (A2)  //Analog input 1 of your arduino
#define         Pin135                   (A0)  //Analog input 2 of your arduino
#define         Pin8                     (A1)  //Analog input 6 of your arduino

#define         RatioMQ4CleanAir          (4.4) //RS / R0 = 4.4 ppm 
#define         RatioMQ135CleanAir        (3.6) //RS / R0 = 10 ppm  
#define         RatioMQ8CleanAir          (70) //RS / R0 = 70 ppm   
#define         ADC_Bit_Resolution        (10) // 10 bit ADC 
#define         Voltage_Resolution        (5) // Volt resolution to calc the voltage
#define         Type                      ("Arduino NANO") //Board used
//Declare Sensor
MQUnifiedsensor MQ4(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin4, Type);
MQUnifiedsensor MQ135(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin135, Type);
MQUnifiedsensor MQ8(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin8, Type);

Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  lcd.init();

  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("Welcome");
  lcd.setCursor(3,1);
  lcd.print("Scatter-ID");
  delay(5000);
  
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    lcd.setCursor(3,0);
    lcd.print("BME280 Error");
    lcd.setCursor(1,1);
    lcd.print("Restart System");
       
    while (1);
  }                       

  MQ4.init();
  MQ4.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ4.setR0(14.23);
  MQ135.init();
  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ135.setR0(9.03);
  MQ8.init();
  MQ8.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ8.setR0(0.91);
}

void gas (){
  MQ4.update();
  MQ135.update();  
  MQ8.update();

  MQ4.setA(1012.7); MQ4.setB(-2.786); //CH4
  float CH4 = MQ4.readSensor(); 
 
  MQ135.setA(110.47); MQ135.setB(-2.862); //CO2 
  float CO2 = MQ135.readSensor(); 
   
  MQ8.setA(976.97); MQ8.setB(-0.688); // H2
  float H2 = MQ8.readSensor();

  lcd.setCursor (2, 0);
  lcd.print("Getting Data");
  lcd.setCursor (0, 1);
  lcd.print("CO2: ");
  lcd.print(CO2, 2);
  lcd.setCursor(12,1);
  lcd.print("ppm");
  delay(2500);
  lcd.clear(); 

  lcd.setCursor (0, 0);
  lcd.print("H2 : ");
  lcd.print(H2,2);
  lcd.setCursor(12,0);
  lcd.print("ppm");
  lcd.setCursor (0, 1);
  lcd.print("CH4: ");
  lcd.print(CH4, 2);
  lcd.setCursor(13,1);
  lcd.print("ppm");
  delay(2500);
  lcd.clear(); 
}

void bme_val (){
  
  float temp = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F;
  float humid = bme.readHumidity();
  
  lcd.setCursor (0, 0);
  lcd.print(temp, 2);
  lcd.setCursor(6,0);
  lcd.print("C");
  lcd.setCursor (9,0);
  lcd.print(humid, 2);
  lcd.setCursor(15,0);
  lcd.print("%");
  lcd.setCursor (2,1);
  lcd.print(pressure, 2);
  lcd.setCursor(12,1);
  lcd.print("hPa");  
  delay(2500);
  lcd.clear();
  
}

void loop() {
  lcd.init();
  gas();
  bme_val();
  
}

