/*
FREE RTOS - MUTEX

A mutex is used to protect a shared resource from
simultaneous access by multiple tasks.

In this program:
- Task1 and Task2 share the Serial port.
- Before accessing Serial, a task takes the mutex.
- After using Serial, the task releases the mutex.
- This ensures only one task accesses the Serial
  port at a time.

API Used:
xSemaphoreCreateMutex() - Creates a mutex.
xSemaphoreTake() - Acquires the mutex.
xSemaphoreGive() - Releases the mutex.

A mutex prevents race conditions and ensures
mutual exclusion when multiple tasks access a
shared resource.
*/

#include <Arduino.h>

SemaphoreHandle_t serialMutex;
void task1(void *pvParameters)
{
  while(1)
  {
    //take mutex
    if(xSemaphoreTake(serialMutex,portMAX_DELAY))
    {
      Serial.println("Task1 using serial");

      xSemaphoreGive(serialMutex);//release mutex
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}


void task2(void *pvParameters)
{
  while(1)
  {
    //take mutex
    if(xSemaphoreTake(serialMutex,portMAX_DELAY))
    {
    
     Serial.println("Task2 using serial");

     xSemaphoreGive(serialMutex);//release mutex
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);
  serialMutex=xSemaphoreCreateMutex();//create mutex
  
  //create tasks
  xTaskCreate(
    task1,
    "Task 1",
    2048,
    NULL,
    1,
    NULL
    
  );

  xTaskCreate(
    task2,
    "Task 2",
    2048,
    NULL,
    1,
    NULL
  );

}
void loop()
{

}