/*
Smart Temperature and Humidity Monitoring System using ESP32

Components Used:
1. ESP32
2. DHT11 Sensor
3. SSD1306 OLED Display
4. Jumper Wires
5. Breadboard

Output:
- OLED displays temperature and humidity values
- Serial Monitor shows sensor readings
- Displays error message if sensor reading fails
*/
#include <Arduino.h>
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const uint8_t DHT_PIN=18;
#define DHT_TYPE DHT11

//DHT object
DHT dht(DHT_PIN,DHT_TYPE);


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
//I2C oled display object
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1);

void setup()
{
    Serial.begin(115200);

    dht.begin(); //dht init
    //oled init
    Wire.begin();
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
   float temp=dht.readTemperature();
   float hum=dht.readHumidity();
   if(isnan(temp)||isnan(hum))
   {
    Serial.println("DHT sensor read failed");
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("DHT read failed");
    display.display();
    return;
   }

  

   display.clearDisplay();
   display.setCursor(20,0);
   display.println("SMART MONITOR");
   display.setCursor(10,20);
   display.print("TEMPERATURE: ");
   display.print(temp);
   display.print("C");

   display.setCursor(10,30);
   display.print("HUMIDITY: ");
   display.print(hum);
   display.print("%");

   
   display.display();

   //display on serial monitor
   Serial.print("TEMPERATURE: ");
   Serial.print(temp);
   Serial.println("C");

   Serial.print("HUMIDITY: ");
   Serial.print(hum);
   Serial.println("%");
   Serial.println();
   delay(2000);
}