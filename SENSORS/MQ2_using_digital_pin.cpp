/*
MQ2 Smoke Detection System using ESP32

Components Used:
1. ESP32
2. MQ2 Gas Sensor Module
3. SSD1306 OLED Display
4. Jumper Wires
5. Breadboard

Output:
- Detects smoke using MQ2 sensor module
- OLED displays smoke detection status
- Serial Monitor shows sensor state
- Displays "DETECTED" when smoke is present
- Displays "SAFE" when no smoke is detected
*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const uint8_t MQ2_PIN=27;
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
//I2C oled display object
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1);

void setup()
{
    Serial.begin(115200);
    pinMode(MQ2_PIN,INPUT);
    //oled init
  if(!display.begin(SSD1306_SWITCHCAPVCC,0X3C))
  {
    Serial.println("OLED intialization failed");
    while(true);
  }

  display.clearDisplay(); //clear buffer
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.display(); //show on OLED

}
void loop()
{
    int gas_state=digitalRead(MQ2_PIN);

    display.clearDisplay();
    display.setCursor(30,10);
    display.print("SMOKE");
    display.setCursor(10,40);

    if(gas_state==0)
    {
        display.print("DETECTED");
    }
    else
    {
        display.print("SAFE");
    }
   display.display();

   //display on serial monitor
   Serial.print("Gas State: ");
   Serial.println(gas_state);
   delay(1000);
}