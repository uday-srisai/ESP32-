/*
MQ2 Gas and Smoke Monitoring System using ESP32

Components Used:
1. ESP32
2. MQ2 Gas Sensor
3. SSD1306 OLED Display
4. Jumper Wires
5. Breadboard

Output:
- Detects gas and smoke levels using MQ2 sensor
- OLED displays gas sensor readings
- Serial Monitor shows gas sensor values
*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const uint8_t MQ2_PIN=35;
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
//I2C oled display object
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1);

void setup()
{
    Serial.begin(115200);
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
    int gas_state=analogRead(MQ2_PIN);

    display.clearDisplay();
    display.setCursor(30,10);
    display.print("SMOKE");
    display.setCursor(10,40);
    display.print(gas_state);
    display.display();

   //display on serial monitor
   Serial.print("Gas State: ");
   Serial.println(gas_state);
   delay(1000);
}