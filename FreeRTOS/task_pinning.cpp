/*
FREE RTOS - TASK PINNING TO CORE

Task pinning is the process of assigning a task to a
specific CPU core using xTaskCreatePinnedToCore().

In ESP32, there are two cores:
- Core 0
- Core 1

By pinning a task to a specific core, we can control
where the task executes.

In this program:
- Red LED Task is pinned to Core 0.
- Green LED Task is pinned to Core 1.
- xPortGetCoreID() is used to display the core on
  which the task is running.

API Used:
xTaskCreatePinnedToCore() -> Creates a task on a
specific core.

xPortGetCoreID() -> Returns the current core ID.
vTaskDelay() -> Delays (blocks) a task.
*/

#include <Arduino.h>

//led pins
const uint8_t RED_LED=25;
const uint8_t GREEN_LED =26;

//task running on core 0
void redLedTask(void *pvParameters)
{
  while(1)
  {
    digitalWrite(RED_LED,HIGH);
    Serial.print("Task running on core:");
    Serial.println(xPortGetCoreID());
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(RED_LED,LOW);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
//task running on core 1
void greenLedTask(void *pvParameters)
{
  while(1)
  {
    digitalWrite(GREEN_LED,HIGH);
    Serial.print("Task running on core:");
    Serial.println(xPortGetCoreID());
    vTaskDelay(500/portTICK_PERIOD_MS);
    digitalWrite(GREEN_LED,LOW);
    vTaskDelay(500/portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);

  //gpio
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
 
  //create tasks
  xTaskCreatePinnedToCore(
    redLedTask,
    "Red Led Task",
    2048,
    NULL,
    1,
    NULL,
    0
  );

  xTaskCreatePinnedToCore(
    greenLedTask,
    "Green Led Task",
    2048,
    NULL,
    1,
    NULL,
    1
  );

}
void loop()
{

}