#include <MQUnifiedsensor.h>

#define         Board                   ("Arduino NANO")
#define         Pin4                     (A0)  //Analog input 1 of your arduino
#define         Pin135                   (A1)  //Analog input 2 of your arduino
#define         Pin8                     (A2)  //Analog input 6 of your arduino

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


void setup() {
  Serial.begin(9600);

  MQ4.init();
  MQ4.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ4.setR0(14.23);
  MQ135.init();
  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ135.setR0(9.03);
  MQ8.init();
  MQ8.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ8.setR0(0.91);



//calibration portion and calibrate for R0.
  Serial.print("Calibrating please wait.");
  float  MQ4calcR0 = 0,
         MQ135calcR0 = 0,
         MQ8calcR0 = 0;
  for (int i = 1; i <= 10; i ++)
  {
    //Update the voltage lectures
    MQ4.update();
    MQ135.update();
    MQ8.update();

    MQ4calcR0 += MQ4.calibrate(RatioMQ4CleanAir);
    MQ135calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    MQ8calcR0 += MQ8.calibrate(RatioMQ8CleanAir);

    Serial.print(".");
  }
  MQ4.setR0(MQ4calcR0 / 10);
  MQ135.setR0(MQ135calcR0 / 10);
  MQ8.setR0(MQ8calcR0 / 10);
  Serial.println("  done!.");

  Serial.print("(MQ4 - MQ135 - MQ8):");
  Serial.print(MQ4calcR0 / 10); Serial.print(" | ");
  Serial.print(MQ135calcR0 / 10); Serial.print(" | ");
  Serial.print(MQ8calcR0 / 10); Serial.print(" | ");
//Calibration
}

void loop() {
  //Update the voltage lectures
  MQ4.update();
  MQ135.update();
  MQ8.update();

  MQ4.setA(1012.7); MQ4.setB(-2.786); //CH4
float CH4 = MQ4.readSensor();

  MQ135.setA(110.47); MQ135.setB(-2.862); //CO2
float CO2 = MQ135.readSensor();

  MQ8.setA(976.97); MQ8.setB(-0.688); // H2
float H2 = MQ8.readSensor();

  Serial.print("Methane:  "); Serial.println(CH4);
  Serial.print("CO2:      "); Serial.println(CO2);
  Serial.print("H2:       "); Serial.println(H2);
  Serial.println("--------------------------------------------------------");
}
