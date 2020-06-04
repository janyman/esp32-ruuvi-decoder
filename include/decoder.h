#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define RUUVI_MAC_ADDR_LEN 6

/** Structure representing decoded acceleration sensor data from a Ruuvi tag */
struct ruuvi_accel_data {
    int16_t x, y, z;      
};

struct esp32_ruuvi_dataset {
    uint8_t src_mac_addr[RUUVI_MAC_ADDR_LEN];
    float temperature;
    float relative_humidity;
    int pressure;
    struct ruuvi_accel_data acceleration;
    float v_bat;
    int8_t tx_power;
    uint8_t movement_cnt;
    uint16_t seq_num;
};

/** Decode a data buffer containing the received BLE advert data.
 * @param buffer
 * @param buffer_len
 * @param dataset_out The decoded data will be saved to struct pointed by this
 * @return false, if there was an error while decodding
 */
bool esp32_ruuvi_decode(uint8_t* buffer, size_t buffer_len, struct esp32_ruuvi_dataset *dataset_out);