/*
Ultrasonic Distance Alert System using ESP32

Components Used:
1. ESP32
2. HC-SR04 Ultrasonic Sensor
3. SSD1306 OLED Display
4. Buzzer
5. LED
6. Jumper Wires
7. Breadboard

Output:
- Measures distance using ultrasonic sensor
- OLED displays distance in centimeters
- Serial Monitor shows distance readings
- Buzzer turns ON when object is very close
- LED turns ON for nearby object detection
*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//I2C oled display object
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1);

const uint8_t trig_pin=18;
const uint8_t echo_pin=23;
const uint8_t led_pin=26;
const uint8_t buzzer=27;

long duration;
float distance_cm;
void setup()
{
    Serial.begin(115200);
    //Wire.begin(21,22);
    //oled init
  if(!display.begin(SSD1306_SWITCHCAPVCC,0X3C))
  {
    Serial.println("OLED intialization failed");
    while(true);
  }
    pinMode(trig_pin,OUTPUT);
    pinMode(echo_pin,INPUT);
    pinMode(led_pin,OUTPUT);
    pinMode(buzzer,OUTPUT);
}

void loop()
{
    //clear trigger pin
    digitalWrite(trig_pin,LOW);
    delayMicroseconds(2);

    //send 10 microseconds puls
    digitalWrite(trig_pin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin,LOW);

    //measure echo pulse duartion
    duration=pulseIn(echo_pin,HIGH);
    //calculate distance
    distance_cm=(duration*0.034)/2;

    if(distance_cm>400)
    {
        Serial.println("out of range");
    }
    else 
    {
    //print distance in serial monitor
    Serial.print("Distance: ");
    Serial.print(distance_cm);
    Serial.print(" cm");
    }
    
    //display on oled
  display.clearDisplay(); //clear buffer
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10,20);
  display.print("Distance: ");
  display.print(distance_cm);
  display.print(" cm");
  display.display(); //show on OLED

 if(distance_cm<10)
{
    digitalWrite(buzzer,HIGH);
}
else if(distance_cm<20)
{
    digitalWrite(buzzer,LOW);
    digitalWrite(led_pin,HIGH);
}
else
{
    digitalWrite(buzzer,LOW);
    digitalWrite(led_pin,LOW);
}
delay(200);

}
