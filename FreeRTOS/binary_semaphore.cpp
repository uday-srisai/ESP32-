/*
FREE RTOS - BINARY SEMAPHORE

A binary semaphore is a synchronization mechanism used
to signal an event between tasks.

It has only two states:
- Available (1)
- Not Available (0)

In this program:
- Sender Task gives the semaphore every 2 seconds.
- Receiver Task waits for the semaphore.
- When the semaphore is received, the Receiver Task
  prints a message.

API Used:
xSemaphoreCreateBinary() - Creates a binary semaphore.
xSemaphoreGive() - Gives/releases the semaphore.
xSemaphoreTake() - Takes/acquires the semaphore.

A binary semaphore is mainly used for task
synchronization and event signaling, not for
transferring data between tasks
*/

#include <Arduino.h>

SemaphoreHandle_t binarySemaphore;

//sender task
void senderTask(void *pvParameters)
{
    while(1)
    {
      Serial.println("sender giving signal");
      xSemaphoreGive(binarySemaphore);
      vTaskDelay(2000/portTICK_PERIOD_MS);
    }
  }


//receiver task
void receiverTask(void *pvParameters)
{
  while(1)
  {
    if(xSemaphoreTake(binarySemaphore,portMAX_DELAY))
    {
      Serial.println("Receiver Task:Signal Received");
    }
  }
}

void setup()
{
  Serial.begin(115200);
  //create binary semaphore
  binarySemaphore=xSemaphoreCreateBinary();
  
  //create tasks
  xTaskCreate(
    senderTask,
    "Sender Task",
    2048,
    NULL,
    1,
    NULL
    
  );

  xTaskCreate(
    receiverTask,
    "Receiver Task",
    2048,
    NULL,
    1,
    NULL
  );

}
void loop()
{

}