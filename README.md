# ESP32 Ruuvi decoder

This is a ESP-IDF component for decoding data sent by a Ruuvi tag. A Ruuvi tag [https://ruuvi.com/] broadcasts its data as BLE advertisements.

## Usage

Checkout this repo under components/ of your ESP32 project.

The following sdkconfig defines are needed:

```
CONFIG_BT_ENABLED=y
CONFIG_BTDM_CONTROLLER_MODE_BLE_ONLY=y
CONFIG_BTDM_CONTROLLER_MODE_BR_EDR_ONLY=
CONFIG_BTDM_CONTROLLER_MODE_BTDM=
```

