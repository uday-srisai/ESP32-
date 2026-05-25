/*
5-Channel IR Sensor Array Monitoring System using ESP32

Components Used:
1. ESP32
2. 5-Channel IR Sensor Array
3. SSD1306 OLED Display
4. Buzzer
5. LED
6. Jumper Wires
7. Breadboard

Output:
- OLED displays status of all IR sensor channels
- Serial Monitor shows sensor readings
- Buzzer and LED turn ON when any channel detects an object
- Buzzer and LED remain OFF when no object is detected
*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
//I2C oled display object
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1);

const uint8_t buzzer =18;
const uint8_t red_led=19;

const uint8_t sensor_pins[5]={23,25,26,27,32};
uint8_t sensor_values[5];
void setup()
{
 Serial.begin(115200);
 if(!display.begin(SSD1306_SWITCHCAPVCC,0X3C))
  {
    Serial.println("OLED intialization failed");
    while(true);
  }
  //sensor pins as input
  for(int i=0;i<5;i++)
  {
    pinMode(sensor_pins[i],INPUT);
  }
 pinMode(buzzer,OUTPUT);
 pinMode(red_led,OUTPUT);

 display.clearDisplay();
 display.setTextSize(1);
 display.setTextColor(SSD1306_WHITE);
}

void loop()
{
    bool object_detected=false;
 
    //read sensor values
    for(int i=0;i<5;i++)
    {
        sensor_values[i]=digitalRead(sensor_pins[i]);

        if(sensor_values[i]==HIGH)
        {
            object_detected=true;
        }
    }
   //serial monitor display
   for(int i=0;i<5;i++)
   {
        Serial.print("S");
        Serial.print(i+1);
        Serial.print(":");
        Serial.print(sensor_values[i]);
        Serial.println(" ");
   }
   //display on oled
   display.clearDisplay();
   for(int i=0;i<5;i++)
   {
        display.setCursor(10,i*10);
        display.print("S");
        display.print(i+1);
        display.print(":");
        display.print(sensor_values[i]);   
        
   }
   display.display();

   // led and buzzer
   if(object_detected)
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
