#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
  char c = 0;
  char str[100];
  
  memset(str, 0, sizeof(str));  //< fill str with 0

  setvbuf(stdout, NULL, _IONBF, 0); //< disable stdout line buffering
  //< stdout: screen
  //< NULL: null buffer pointer
  //< _IONBF: no buffering mode
  //< 0: buffer size

  printf("type anything: ");

  while (c != '\n')   //< stop after <enter> char
  {
    c = getchar();    //< Reads the next character from stdin.
    
    if (c != 0xff)    //< discard 
    {
      str[strlen(str)] = c; //< strlen increments when new character is included
      printf("%c", c);
  
    }
    vTaskDelay(100 / portTICK_PERIOD_MS); //< wait 100 ms before read another char
  }

  printf("you typed: %s\n", str); 
}
