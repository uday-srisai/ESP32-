/*
FREE RTOS - COUNTING SEMAPHORE

A counting semaphore is a synchronization mechanism
that can hold multiple counts and is used to track
multiple events or resources.

In this program:
- Sender Task gives the semaphore every 1 second.
- Receiver Task takes the semaphore every 3 seconds.
- The sender increases the semaphore count.
- The receiver decreases the semaphore count.
- Maximum count = 5
- Initial count = 0

API Used:
xSemaphoreCreateCounting() - Creates a counting semaphore.
xSemaphoreGive() - Increments semaphore count.
xSemaphoreTake() - Decrements semaphore count.

Expected Output:
Sender: Giving semaphore
Receiver: Semaphore taken

Unlike a binary semaphore, a counting semaphore can
store multiple signals/events using a count value.
*/
#include <Arduino.h>

SemaphoreHandle_t countingSemaphore;

//sender task
void senderTask(void *pvParameters)
{
    while(1)
    {
      Serial.println("sender: Giving semaphore");
      xSemaphoreGive(countingSemaphore);
      vTaskDelay(1000/portTICK_PERIOD_MS);
    }
  }


//receiver task
void receiverTask(void *pvParameters)
{
  
  while(1)
  {
    
    if(xSemaphoreTake(countingSemaphore,portMAX_DELAY))
    {
      Serial.println("Receiver:Semaphore taken");
      vTaskDelay(3000/portTICK_PERIOD_MS);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  //create counting semaphore
  countingSemaphore=xSemaphoreCreateCounting(5,0);//max count=5,intialcount=0
  
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