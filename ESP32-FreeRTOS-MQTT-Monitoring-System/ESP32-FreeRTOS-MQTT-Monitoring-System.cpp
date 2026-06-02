#include <Arduino.h>
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include<PubSubClient.h>

const uint8_t DHT_PIN=18;
#define DHT_TYPE DHT11

//DHT object
DHT dht(DHT_PIN,DHT_TYPE);

const uint8_t LDR_PIN=34;//ldr pin
const uint8_t MQ2_PIN=35;//mq2

const uint8_t RED_LED=25;
const uint8_t GREEN_LED=26;
const uint8_t RELAY_PIN=27;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
//I2C oled display object
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1);

const char *ssid="yourwifiusername";// change this
const char *password="yourwifipassword";//change this
const char *mqtt_server = "broker.hivemq.com";

typedef struct
{
  float temperature;
  float humidity;
  int gas_value;
  int ldr_state;

  bool dht_error;
  
}sensor_data;

sensor_data sd={0};//global 

SemaphoreHandle_t sensor_data_mutex;

WiFiClient espClient;
PubSubClient client(espClient);

void sensor_task(void *pvParameters)
{
  
  while(1)
 {
   
   float temp=dht.readTemperature();
   float hum=dht.readHumidity();
   int gas=analogRead(MQ2_PIN);
   int ldr=digitalRead(LDR_PIN);

  
  
    if(xSemaphoreTake(sensor_data_mutex,portMAX_DELAY))
    {
      sd.temperature=temp;
      sd.humidity=hum;
      sd.gas_value=gas;
      sd.ldr_state=ldr;

      sd.dht_error=(isnan(temp)||isnan(hum));
      xSemaphoreGive(sensor_data_mutex);
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void oled_task(void *pvParameters) 
{
  sensor_data received_data;
     while(1)
    { 
      if(xSemaphoreTake(sensor_data_mutex,portMAX_DELAY))
      {
          received_data=sd;
          xSemaphoreGive(sensor_data_mutex);
      }
      
       if(received_data.dht_error)
       {
          Serial.println("DHT sensor read failed");
          display.clearDisplay();
          display.setCursor(0,0);
          display.println("DHT read failed");
          display.display();
          vTaskDelay(1000/portTICK_PERIOD_MS);//RTOS delay
          continue;
       }
        display.clearDisplay();
        display.setCursor(20,0);
        display.println("SMART MONITOR");
        display.setCursor(10,20);
        display.print("TEMPERATURE: ");
        display.print(received_data.temperature);
        display.print("C");

        display.setCursor(10,30);
        display.print("HUMIDITY: ");
        display.print(received_data.humidity);
        display.print("%");

        display.setCursor(10,50);

        if(received_data.gas_value>400)
        {
          display.print("ALERT:");
          display.print(received_data.gas_value);
        }
        else
        {
          display.print("SAFE:");
          display.print(received_data.gas_value);
        }
        //ldr
        display.setCursor(10,40);
        if(received_data.ldr_state==0)
        {
          display.print("Light:Bright");
        }
        else
        {
          display.print("Light:Dark");
        }
    
        display.display();

        //display on serial monitor
        Serial.print("TEMPERATURE: ");
        Serial.print(received_data.temperature);
        Serial.println(" C");

        Serial.print("HUMIDITY: ");
        Serial.print(received_data.humidity);
        Serial.println(" %");

        Serial.print("Gas Value: ");
        Serial.println(received_data.gas_value);

   
        Serial.print("LDR state: ");
        Serial.println(received_data.ldr_state);

        Serial.println();
      
         vTaskDelay(1000/portTICK_PERIOD_MS);
      }
 }
  

 void alert_task(void *pvParameters)
 {
    sensor_data rx;
  while(1)
  {
     if(xSemaphoreTake(sensor_data_mutex,portMAX_DELAY))
     {
      rx=sd;
      xSemaphoreGive(sensor_data_mutex);
     }
     
      if(rx.gas_value>400)
      {
        digitalWrite(RED_LED,HIGH);
        digitalWrite(GREEN_LED,LOW);
        digitalWrite(RELAY_PIN,LOW);
      }
      else
      {
      
        digitalWrite(GREEN_LED,HIGH);
        digitalWrite(RED_LED,LOW);
        digitalWrite(RELAY_PIN,HIGH);//off
      }
      vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void wifi_task(void *pvParameters)
{
  sensor_data wifi_data;
  Serial.println("Connecting to WIFI...");
  WiFi.begin(ssid,password);//connect esp32 to wifi router
  while(WiFi.status()!=WL_CONNECTED) //connecting wifi at first time
  {
    vTaskDelay(500/portTICK_PERIOD_MS);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WIFI conncected");
  client.setServer(mqtt_server,1883);//address,port number

  while(1)
  {
    if(WiFi.status()==WL_DISCONNECTED) //wifi reconnects again if lost 
    {
        WiFi.reconnect();
        continue;
    }
  
    if(!client.connected()) //MQTT reconnects if the connection is lost.
   {
    if(client.connect("SmartMonitorESP32"))
    {
        Serial.println("MQTT Connected");
    }
    else
    {
        Serial.println("MQTT Connection Failed");
        vTaskDelay(5000/portTICK_PERIOD_MS);
       continue;
    }
  }

    if(xSemaphoreTake(sensor_data_mutex,portMAX_DELAY))
     {
       wifi_data=sd;
       xSemaphoreGive(sensor_data_mutex);
     }

    //converting int ,float values to string using snprintf
    char temp_str[10];
    snprintf(temp_str,sizeof(temp_str),"%.2f",wifi_data.temperature);
    client.publish("smart_monitor/temperature", temp_str); //
    
    char hum_str[10];
    snprintf(hum_str,sizeof(hum_str),"%.2f",wifi_data.humidity);
    client.publish("smart_monitor/humidity",hum_str);

    char ldr_str[10];
    snprintf(ldr_str,sizeof(ldr_str),"%d",wifi_data.ldr_state);
    client.publish("smart_monitor/ldr", ldr_str);

    char gas_str[10];
    snprintf(gas_str,sizeof(gas_str),"%d",wifi_data.gas_value);
    client.publish("smart_monitor/gas",gas_str);

     Serial.println("All Sensor Data Published");
     client.loop();
     vTaskDelay(5000/portTICK_PERIOD_MS);
  }
}

void setup()
{
    Serial.begin(115200);

    dht.begin(); //dht init
    pinMode(LDR_PIN,INPUT);
    pinMode(RELAY_PIN,OUTPUT);
    pinMode(RED_LED,OUTPUT);
    pinMode(GREEN_LED,OUTPUT);
    digitalWrite(RELAY_PIN,HIGH);//off intially

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

  sensor_data_mutex=xSemaphoreCreateMutex();
  // sensor task
  xTaskCreate(
    sensor_task,
    "Sensor Task",
    4096,
    NULL,
    2,
    NULL
  );
  //oled task
  xTaskCreate(
    oled_task,
    "Oled Task",
    4096,
    NULL,
    1,
    NULL
  );
  
  //alert task
  xTaskCreate(
    alert_task,
    "Alert Task",
    4096,
    NULL,
    3,
    NULL
  );
//wifi task
  xTaskCreate(
    wifi_task,
    "WIFI Task",
    4096,
    NULL,
    1,
    NULL
  );

}
void loop()
{

}
