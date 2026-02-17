#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_random.h"     //< random 
#include "math.h"           //< math functions

#define TAG "DICE"
#define pdSecond 1000 / portTICK_PERIOD_MS

int dice_role()
{
  int random = esp_random();
  int positiveNumber = abs(random);
  int diceNumber = (positiveNumber % 6) + 1;
  return diceNumber;
}

void app_main(void)
{
  while (1)
  {
    vTaskDelay(pdSecond);
    ESP_LOGI(TAG, "dice result: %d", dice_role());
  }
}