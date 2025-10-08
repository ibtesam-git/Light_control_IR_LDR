#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

// Pin definitions
#define LDR_PIN GPIO_NUM_12   // LDR sensor input
#define IR_PIN  GPIO_NUM_5    // IR sensor input
#define LED_PIN GPIO_NUM_2    // Normal LED output

// Globals
static bool ldrActive = false;     // Is LDR control active
static bool lastIrState = true;    // Last IR sensor reading

static const char *TAG = "LDR_IR";

void app_main(void) {
    // Configure pins
    gpio_reset_pin(LDR_PIN);
    gpio_set_direction(LDR_PIN, GPIO_MODE_INPUT);

    gpio_reset_pin(IR_PIN);
    gpio_set_direction(IR_PIN, GPIO_MODE_INPUT);

    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN, 0); // LED initially OFF

    while (1) {
        bool irState = gpio_get_level(IR_PIN);   // IR sensor reading
        bool ldrState = gpio_get_level(LDR_PIN); // LDR sensor reading

        // IR sensor toggles LDR active state
        if (irState == 0 && lastIrState == 1) {  
            ldrActive = !ldrActive; 
            ESP_LOGI(TAG, "IR detected: LDR control %s", ldrActive ? "ENABLED" : "DISABLED");

            if (!ldrActive) {
                gpio_set_level(LED_PIN, 0); // Turn LED OFF when LDR stops working
                ESP_LOGI(TAG, "LDR disabled → LED OFF");
            }
            vTaskDelay(pdMS_TO_TICKS(200)); // debounce delay
        }
        lastIrState = irState;

        // LDR works only when active
        if (ldrActive) {
            if (ldrState == 0) { // DARK
                gpio_set_level(LED_PIN, 0); // LED OFF in dark
                ESP_LOGI(TAG, "🌑 Dark detected → LED OFF");
            } else { // BRIGHT
                gpio_set_level(LED_PIN, 1); // LED ON in bright
                ESP_LOGI(TAG, "💡 Bright detected → LED ON");
            }
        }

        vTaskDelay(pdMS_TO_TICKS(50)); // loop delay
    }
}
