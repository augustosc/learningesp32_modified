#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"  //< semaphore lib

SemaphoreHandle_t mutexBus;


void writeToBus(char *message)
/* somente a tarefa que fez o take pode fazer o "give".
   note que a writeToBus é uma função chamada tanto por task1 quanto por task2,
   logo, writeToBus pertence sempre ao contexto (tarefa) que a chamou.
   Por isso, é possível fazer o "give" dentro da writeToBus.
   Assim, o "give" dentro de task1 e task2 deve ser removido
*/

{
  printf(message);

  //< faz o "give" após o printf, protegendo o print
  xSemaphoreGive(mutexBus);
}

void task1(void *params)
{
  while (true)
  {
    printf("[task1]: reading temperature \n");

    //< aguarda por 1s o semaforo-mutex ficar "unlocked"
    //< após o take o semáforo é alterado para "locked"
    if (xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS))
    {
      //< com o semáforo bloqueado acessa writeToBus
      writeToBus("[writeToBus from task1]: temperature is 25c\n");

      //< desbloqueia o semaforo após o acesso
      //xSemaphoreGive(mutexBus);
    }
    else
    {
      //< sinaliza timeout caso o semaforo não seja recebido a tempo
      printf("[task1]: writing temperature timed out \n");
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task2(void *params)
{
  while (true)
  {
    printf("[task2]: reading humidity\n");

    //< aguarda por 1s o semaforo-mutex ficar "unlocked"
    //< após o take o semáforo é alterado para "locked"
    if (xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS))
    {

      //< com o semáforo bloqueado acessa writeToBus
      writeToBus("[writeToBus from task2]: humidity is 50%% \n");

      //< libera o semaforo-mutex após o acesso
      //xSemaphoreGive(mutexBus);
    }
    else
    {
      //< sinaliza timeout caso o semaforo não seja recebido a tempo
      printf("[task2]: writing humidity timed out \n");
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void app_main(void)
{
  //< cria um semáforo mutex para controlar acesso exclusivo a task writeToBus
  mutexBus = xSemaphoreCreateMutex();
  printf("[main]: mutex semaphore created\n");


  //< verifica que o estado inicial do semáforo-mutex é "unlocked"
  if (xSemaphoreTake(mutexBus, 10 / portTICK_PERIOD_MS))
    {
      printf("[main]: mutex semaphore created unlocked \n");

      //< libera o semaforo-mutex para as tasks
      xSemaphoreGive(mutexBus);
    }
    else
    {
      //< sinaliza timeout caso o semaforo não seja recebido a tempo
      printf("[main]: mutex semaphore created locked \n");
    }

  //< cria as tasks
  printf("[main]: creating task1 and task2\n");

  xTaskCreate(&task1, "temperature reading", 2048, NULL, 2, NULL);
  xTaskCreate(&task2, "humidity reading", 2048, NULL, 2, NULL);
}