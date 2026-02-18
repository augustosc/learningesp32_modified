#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static TaskHandle_t receiverHandler = NULL; 

void sender(void * params)
{
  //< envia 4 notificações e bloqueia por 5s
    while (true)
    {
      printf("task %s sending notifications\n", (char*) params);
      //< cada notificação incrementa o contador da task receiver
      xTaskNotifyGive(receiverHandler); 
      xTaskNotifyGive(receiverHandler);
      xTaskNotifyGive(receiverHandler);
      xTaskNotifyGive(receiverHandler);
      vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    
}

void receiver(void * params) 
{
  //< permanece bloqueada enquanto o contador !=0
  //< a cada notificação que recebe incrementa o contador
  while (true)
  {
    //< com pdFALSE TaskNotifyTake decrmenta o contador antes de retornar
    //< com pdTRUE TaskNotifyTake zera o contador antes de retornar
    int count = ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
    printf("task %s received notification %d times\n", (char*) params, count);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
  
}

void app_main(void)
{
  //< cria as tasks receiver e sender e passa o nome como parâmetro
   xTaskCreate(&receiver, "receiver", 2048, "receiver", 2, &receiverHandler);
   xTaskCreate(&sender, "sender", 2048, "sender", 2, NULL);
}