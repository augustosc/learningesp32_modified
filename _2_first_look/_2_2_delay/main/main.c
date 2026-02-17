#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"  //< para usar vTaskDelay
#include "freertos/task.h"      //< para usar vTaskDelay

#define pdSecond 1000 / portTICK_PERIOD_MS  //< 1 segundo

#define TAG "DELAY"

void app_main(void)
{
  int i = 0;
  while (1)
  {
    vTaskDelay(pdSecond * 2);
    ESP_LOGI(TAG, "in loop %d", i++);
  }
}