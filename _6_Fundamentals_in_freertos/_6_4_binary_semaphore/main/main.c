#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"


SemaphoreHandle_t binSemaphore;   // cria o handle para o semáforo


void listenForHTTP(void *params)
//< task que libera o semáforo
{
  while (true)
  {
    printf("received http message\n");
    xSemaphoreGive(binSemaphore);
    printf("processed http message\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void doSomething(void *params)
//< task que aguarada o semáforo livre para executar alguma função
{
  while (true)
  {
    xSemaphoreTake(binSemaphore, portMAX_DELAY);
    printf("doing something with http\n");
  }
}

void app_main(void)
{
  //< cria o semáforo
  binSemaphore = xSemaphoreCreateBinary();

  //< cria as tasks

  //< com prioridade maior doSomething é executada logo após a liberação do semáforo
  xTaskCreate(&doSomething, "do something with http", 2048, NULL, 2, NULL);

  xTaskCreate(&listenForHTTP, "get http", 2048, NULL, 1, NULL);

  
  
}