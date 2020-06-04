#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "decoder.h"

void esp32_ruuvi_listener_start(QueueHandle_t output_queue);