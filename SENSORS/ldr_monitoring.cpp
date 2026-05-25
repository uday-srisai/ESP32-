/*
LDR Light Monitoring System using ESP32

Components Used:
1. ESP32
2. LDR Sensor Module
3. SSD1306 OLED Display
4. Jumper Wires
5. Breadboard

Output:
- OLED displays light condition status
- Serial Monitor shows LDR sensor state
- Displays "Light: Bright" in bright condition
- Displays "Light: Dark" in dark condition
*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const uint8_t LDR_PIN=34;//ldr pin
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
//I2C oled display object
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1);

void setup()
{
    Serial.begin(115200);

    pinMode(LDR_PIN,INPUT);
    //oled init
  if(!display.begin(SSD1306_SWITCHCAPVCC,0X3C))
  {
    Serial.println("OLED intialization failed");
    while(true);
  }

  display.clearDisplay(); //clear buffer
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.display(); //show on OLED

}
void loop()
{

   int ldr_state=digitalRead(LDR_PIN);;

   display.clearDisplay();
   display.setCursor(30,0);
   display.print("LDR MONITOR");
   display.setCursor(10,30);

   if(ldr_state==0)
   {
        display.print("Light:Bright");
   }
   else
   {
        display.print("Light:Dark");
   }

   display.display();

   //display on serial monitor
   
   Serial.print("LDR state: ");
   Serial.println(ldr_state);

   Serial.println();

   delay(1000);
}