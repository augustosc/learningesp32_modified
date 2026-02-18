#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"


//< task 1, no core PRO_CPU
void task1(void * params)
{
  while (true)
  {
    //< xPortGetCoreID identifica o core em que a task está alocada
    ESP_LOGI("TASK1", "running on core %d", xPortGetCoreID());
    printf("reading temperature from %s\n", (char *) params);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

//< task 2, no core APP_CPU
void task2(void * params) 
{
  while (true)
  {
    //< xPortGetCoreID identifica o core em que a task está alocada
    ESP_LOGI("TASK2", "running on core %d", xPortGetCoreID());
    printf("reading humidity from %s\n", (char *) params);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void app_main(void)
{
  //< cria as tasks 1 e 2
  //< task1 no core ) (PRO_CPU)
  //< task2 no core 1 (APP_CPU)
   xTaskCreatePinnedToCore(&task1, "temperature reading", 2048, "task 1", 2, NULL,PRO_CPU_NUM);
   xTaskCreatePinnedToCore(&task2, "humidity reading", 2048, "task 2", 2, NULL,APP_CPU_NUM);
}