#include <Arduino.h>
#include <menuv2.h>
#include <ws2812.h>

void setup() {
    Serial.begin(115200);
}

void loop() {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}