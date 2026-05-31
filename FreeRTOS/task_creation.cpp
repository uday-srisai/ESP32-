
/*
FREE RTOS - TASK CREATION

Task creation is the process of creating independent
tasks using xTaskCreate() so that different activities
can execute concurrently under the control of the
FreeRTOS scheduler.
-
In this program:
- One task controls the Red LED.
- Another task controls the Green LED.
- Both tasks are created using xTaskCreate().
- The scheduler switches between the tasks.
- vTaskDelay() blocks a task for a specified time,
  allowing other tasks to run.

API Used:
xTaskCreate() -> Creates a task
vTaskDelay() -> Delays (blocks) a task
*/
#include <Arduino.h>

//led pins
const uint8_t RED_LED=25;
const uint8_t GREEN_LED=26;

void redLedTask(void *pvParameters)
{
  while(1)
  {
    digitalWrite(RED_LED,HIGH);
    Serial.println("red led on");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(RED_LED,LOW);
    Serial.println("red led off");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void greenLedTask(void *pvParameters)
{
  while(1)
  {
    digitalWrite(GREEN_LED,HIGH);
    Serial.println("green led on");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(GREEN_LED,LOW);
    Serial.println("green led off");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
void setup()
{
  Serial.begin(115200);

  //gpio
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);

  //create tasks
  xTaskCreate(
    redLedTask,
    "Red Led Task",
    2048,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    greenLedTask,
    "Green Led Task",
    2048,
    NULL,
    1,
    NULL
  );

}
void loop()
{

}