#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"  //< semaphore lib

SemaphoreHandle_t mutexBus;


void writeToBus(char *message)
{
  printf(message);
}

void task1(void *params)
{
  while (true)
  {
    printf("reading temperature \n");
    //< aguarda o semaforo-mutex por 1s
    //< se receber: chama writeToBus
    if (xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS))
    {
      writeToBus("temperature is 25c\n");

      //< libera o semaforo-mutex após o acesso
      xSemaphoreGive(mutexBus);
    }
    else
    {
      //< sinaliza timeout caso o semaforo não seja recebido a tempo
      printf("writing temperature timed out \n");
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task2(void *params)
{
  while (true)
  {
    printf("reading humidity\n");

    //< aguarda o semaforo-mutex por 1s
    //< se receber: chama writeToBus
    if (xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS))
    {
      writeToBus("humidity is 50%% \n");

      //< libera o semaforo-mutex após o acesso
      xSemaphoreGive(mutexBus);
    }
    else
    {
      //< sinaliza timeout caso o semaforo não seja recebido a tempo
      printf("writing humidity timed out \n");
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void app_main(void)
{
  //< cria um semáforo mutex para controlar acesso exclusivo a task writeToBus
  mutexBus = xSemaphoreCreateMutex();

  //< cria as tasks
  xTaskCreate(&task1, "temperature reading", 2048, NULL, 2, NULL);
  xTaskCreate(&task2, "humidity reading", 2048, NULL, 2, NULL);
}