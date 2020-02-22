
#define RUUVI_TAG "ruuvi-decoder"
#include "decoder.h"

void esp32_ruuvi_decode(uint8_t* buffer, size_t buffer_len, struct esp32_ruuvi_dataset *output) {
    bool retval = false;

    switch (buffer[0]) {
        case 0x03:
            ESP_LOGE(RUUVI_TAG, "Ruuvi decoder does not support RAWv1 format (0x03)!");
            retval = false;
            break;
        case 0x05:
            if (buffer_len != 24) {
                ESP_LOGE(RUUVI_TAG, "Bad length for RAWv2: %i", buffer_len);
                retval = false;
                break;
            }

            int16_t t_val = buffer[1] << 8 | buffer[2];
            float temperature = t_val * 0.005;
            ESP_LOGI(RUUVI_TAG, "temperature is %f", temperature);
            output->temperature = temperature;

            uint16_t h_val = buffer[3] << 8 | buffer[4];
            float humidity = h_val * 0.0025;
            ESP_LOGI(RUUVI_TAG, "humidity is %f", humidity);
            output->relative_humidity = humidity;

            int pressure = (buffer[5] << 8 | buffer[6]) + 50000;
            ESP_LOGI(RUUVI_TAG, "pressure is %i", pressure);
            output->pressure = pressure;

            int16_t a_x_val = buffer[7] << 8 | buffer[8];
            ESP_LOGI(RUUVI_TAG, "accel x %f", a_x_val / 1000.0);
            output->acceleration.x = a_x_val;

            int16_t a_y_val = buffer[9] << 8 | buffer[10];
            ESP_LOGI(RUUVI_TAG, "accel y %f", a_y_val / 1000.0);
            output->acceleration.y = a_y_val;

            int16_t a_z_val = buffer[11] << 8 | buffer[12];
            ESP_LOGI(RUUVI_TAG, "accel z %f", a_z_val / 1000.0);
            output->acceleration.z = a_z_val;

            uint16_t v_bat_tx_pwr = (buffer[13] << 8 | buffer[14]);
            float v_bat =  (v_bat_tx_pwr >> 5) / 1000.0 + 1.6;
            ESP_LOGI(RUUVI_TAG, "v_bat is %f", v_bat);
            output->v_bat = v_bat;

            int8_t tx_pwr = (buffer[14] & 0x1f) * 2 - 40;
            ESP_LOGI(RUUVI_TAG, "tx power is %i", tx_pwr);
            output->tx_power;

            uint8_t mov_cnt = buffer[15];
            ESP_LOGI(RUUVI_TAG, "movement cnt %i", mov_cnt);
            output->movement_cnt;

            uint16_t seq_num = buffer[16] << 8 | buffer[17];
            ESP_LOGI(RUUVI_TAG, "seq num %u", seq_num);
            output->seq_num;

            memcpy(output->src_mac_addr, &buffer[18], RUUVI_MAC_ADDR_LEN);
            
            /* Successful decode */
            retval = true;

            break;
    }

    return retval;
}