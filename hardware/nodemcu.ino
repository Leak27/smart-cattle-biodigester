#include <SoftwareSerial.h>
  
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors
 
int firstVal, secondVal,thirdVal; // sensors 

 
void setup()
{
  // Debug console
  Serial.begin(9600);
}
 
void loop()
{
     
  if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
   // Serial.print(rdata);
    if( rdata == '\n')
    {
   //  Serial.println(myString); 
  // Serial.println("fahad");
// new code
String l = getValue(myString, ',', 0);
String m = getValue(myString, ',', 1);
String n = getValue(myString, ',', 2); 
 
 
firstVal = l.toInt();
Serial.println(firstVal);
secondVal = m.toInt();
Serial.println(secondVal);
thirdVal = n.toInt();
Serial.println(thirdVal);
delay(1000);
 
  myString = "";
// end new code
    }
  }
 
}
  
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
