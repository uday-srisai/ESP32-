/*
FREE RTOS - TASK DELETION

Task deletion is the process of removing a task from
the FreeRTOS scheduler when it is no longer required.

vTaskDelete() is used to delete a task.

In this program:
- A task blinks an LED 5 times.
- After completing its work, the task deletes itself
  using vTaskDelete(NULL).

API Used:
vTaskDelete() - Deletes a task
*/

#include <Arduino.h>

//led pins
const uint8_t RED_LED=25;

void redLedTask(void *pvParameters)
{
   for(int i=0;i<5;i++)
  {
    digitalWrite(RED_LED,HIGH);
    Serial.println("red led on");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(RED_LED,LOW);
    Serial.println("red led off");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
  Serial.println("Deleting redLedTask");
  vTaskDelete(NULL);
}

void setup()
{
  Serial.begin(115200);

  //gpio
  pinMode(RED_LED,OUTPUT);
 
  //create task
  xTaskCreate(
    redLedTask,
    "Red Led Task",
    2048,
    NULL,
    1,
    NULL
  );

}
void loop()
{

}