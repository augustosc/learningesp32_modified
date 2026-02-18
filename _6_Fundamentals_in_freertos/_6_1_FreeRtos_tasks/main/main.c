#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define pdSECOND 1000 / portTICK_PERIOD_MS 

//< print temperature each 1s
void task1(void * params)
{
  uint32_t temp =10;

  while (true)
  {
    printf("%s: reading temperature = %lu \n", (char *) params, temp);
    vTaskDelay(pdSECOND);
    if (++temp == 30) { temp = 10;}
  }
}

//< print humidity each 2s
void task2(void * params) 
{
  uint32_t hum = 20;
  while (true)
  {
    printf("%s: reading humidity = %lu \n", (char *) params, hum);
    vTaskDelay(pdSECOND * 2);
    if (++hum == 40) { hum = 20;}
  }
}

void app_main(void)
{
  // create tasks 2 and 2
   xTaskCreate(&task1, "temperature reading", 2048, "task 1", 2, NULL);
   xTaskCreate(&task2, "humidity reading", 2048, "task 2", 2, NULL);
}