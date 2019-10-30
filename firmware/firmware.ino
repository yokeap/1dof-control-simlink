/** 
 * Firmware for simulink.  
 * Author: S. Sukprasertchai  
 * Info: send sensor adc value 10 bit as uint16 to simulink in little endian format.
 */

#include <Servo.h>

const int analogInPin = A1;  // Analog input pin that the potentiometer is attached to

byte ctrlmot=0; 

int sensorValue = 0;        // value read from the pot
int x1 = 0, x2 = 0, x3 = 0, x4 = 0, x5 = 0 , x6 = 0, x7 = 0, x8 = 0;

void setup() {
  // initialize serial communications at 19200 bps:
  Serial.begin(19200);
}

void loop() {
  // read the analog in value:
  unsigned int adcVal = analogRead(analogInPin);
  Serial.write(adcVal & 0x00FF);
  Serial.write((adcVal & 0xFF00) >> 8);             
  Serial.print("\r\n");
  

  if(Serial.available()>0)
  { 
    ctrlmot=Serial.read(); 
    analogWrite(3, ctrlmot);                  // sets the servo position according to the scaled value
    
  }
  delay(10);
}

unsigned int low_pass_filter()
{
  x8 = x7;
  x7 = x6;
  x6 = x5;
  x5 = x4;
  x4 = x3;
  x3 = x2;
  x2 = x1;
  x1 = sensorValue;
  sensorValue = analogRead(analogInPin);
  return (x1 + x2 + x3 +x4 +x5)/5;
}
