/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

char* get_chip_model_name(int chip_model_num)
{
    switch (chip_model_num)
    {
        case 2: return "ESP32-S2";
        case 1: return "ESP32";
        case 9: return "ESP32-S3";
        case 5: return "ESP32-C3";
        case 12: return "ESP32-C2";
        case 13: return "ESP32-C6";
        case 16: return "ESP32-H2";
        case 18: return "ESP32-P4";
        case 999: return "POSIX SIMULATOR";
        default: return "unknown";
    }

}

void app_main(void)
{
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;


    // get chip info
    esp_chip_info(&chip_info);

    //print chip info
    printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
           //CONFIG_IDF_TARGET, //< optional to get chip model from sdconfig
           get_chip_model_name(chip_info.model),
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
           (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    // get chip revision
    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;

    // print chip revision
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);

    // get flash size
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    // print flash info
    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    // print heap info
    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

    // count 10 seconds
    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    // restart
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}
