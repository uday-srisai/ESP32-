//Using 5-array IR sensor module
//Only S1 output is connected to ESP32 for detection
/*
IR Object Detection Alert System using ESP32

Components Used:
1. ESP32
2. 5-Channel IR Sensor Module
3. Buzzer
4. LED
5. Jumper Wires
6. Breadboard

Output:
- Detects object using IR sensor module
- Serial Monitor displays sensor status
- Buzzer and LED turn ON when object is detected
- Buzzer and LED turn OFF when no object is detected
*/
#include <Arduino.h>
const uint8_t buzzer =25;
const uint8_t red_led=26;
const uint8_t ir_sensor=18;

void setup()
{
 Serial.begin(115200);
 pinMode(ir_sensor,INPUT); 
 pinMode(buzzer,OUTPUT);
 pinMode(red_led,OUTPUT);

}

void loop()
{
  int sensor_value=digitalRead(ir_sensor);
  Serial.println(sensor_value);
  if(sensor_value==HIGH)
  {
    digitalWrite(buzzer,HIGH);
    digitalWrite(red_led,HIGH);
  }
  else 
  {
    digitalWrite(buzzer,LOW);
    digitalWrite(red_led,LOW);
  }
   delay(100);
}
