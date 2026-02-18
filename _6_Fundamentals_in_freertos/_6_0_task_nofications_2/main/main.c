#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static TaskHandle_t receiverHandler = NULL;

void sender(void *params)
{
  //< envia notificações para setar bits 0 e 1 (decimal 1+2=3)
  //< aguarda 1s 
  //< envia notificações para setar bits 2 e 3 (decimal 4+8=12)
  while (true)
  {
    xTaskNotify(receiverHandler, (1 << 0), eSetBits);
    xTaskNotify(receiverHandler, (1 << 1), eSetBits);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xTaskNotify(receiverHandler, (1 << 2), eSetBits);
    xTaskNotify(receiverHandler, (1 << 3), eSetBits);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void receiver(void *params)
{
  uint32_t state;
  while (true)
  {
    //< recebe a notificação em state
    //< 0xffffffff: clear todos os bits na entrada 
    //< 0: não limpa nenhum bit na saída
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("received state %lu times\n", state);
  }
}

void app_main(void)
{
  xTaskCreate(&receiver, "sender", 2048, NULL, 2, &receiverHandler);
  xTaskCreate(&sender, "receiver", 2048, NULL, 2, NULL);
}