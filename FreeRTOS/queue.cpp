/*
FREE RTOS - QUEUE

A queue is an inter-task communication mechanism used
to transfer data safely between tasks.

In this program:
- Sender Task sends integer values to the queue.
- Receiver Task receives values from the queue.
- The queue stores up to 5 integer values.

API Used:
xQueueCreate() - Creates a queue.
xQueueSend() - Sends data to the queue.
xQueueReceive() - Receives data from the queue.


A queue is used for data transfer between tasks,
whereas semaphores and mutexes are mainly used for
synchronization and resource protection.
*/

#include <Arduino.h>

QueueHandle_t numberQueue;
void senderTask(void *pvParameters)
{
  
    int count=0;
    while(1)
    {
      xQueueSend(numberQueue,&count,portMAX_DELAY);
      Serial.print("sent:");
      Serial.println(count);
      count++;
      vTaskDelay(1000/portTICK_PERIOD_MS);
    }
  }



void receiverTask(void *pvParameters)
{
  int receivedValue;
  while(1)
  {
    
    if(xQueueReceive(numberQueue,&receivedValue,portMAX_DELAY))
    {
    Serial.print("received:");
    Serial.println(receivedValue);
    
    }
  }
}

void setup()
{
  Serial.begin(115200);
  numberQueue=xQueueCreate(5,sizeof(int));//create queue
  
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