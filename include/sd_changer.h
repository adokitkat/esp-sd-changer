#pragma once

#include <stdint.h>
#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"
#include "driver/gpio.h"
// GPIO Expander
#include "mcp23017.h"
#include "i2c_bus.h"


#define SD_SLOT_COUNT 8
#define SD_PORT_COUNT 2

#define SD_I2C_SCL GPIO_NUM_12
#define SD_I2C_SDA GPIO_NUM_13

#define SD_PORTA_INIT {     \
    .clk = GPIO_NUM_6,    \
    .cmd = GPIO_NUM_7,    \
    .d0 = GPIO_NUM_5,      \
    .d1 = GPIO_NUM_4,      \
    .d2 = GPIO_NUM_16,      \
    .d3 = GPIO_NUM_15,      \
    .cd = SDMMC_SLOT_NO_CD, \
    .wp = SDMMC_SLOT_NO_WP, \
    .width = 4,             \
    .flags = 0,             \
}

#define SD_PORTB_INIT {     \
    .clk = GPIO_NUM_42,    \
    .cmd = GPIO_NUM_41,    \
    .d0 = GPIO_NUM_2,      \
    .d1 = GPIO_NUM_1,      \
    .d2 = GPIO_NUM_39,      \
    .d3 = GPIO_NUM_40,      \
    .cd = SDMMC_SLOT_NO_CD, \
    .wp = SDMMC_SLOT_NO_WP, \
    .width = 4,             \
    .flags = 0,             \
}
#define SDCHNGR_DEFAULT() { \
    .selectedSlot = 0, \
    .detectedCards = 0, \
    .poweredSlots = 0, \
    .portConfigs = {SD_PORTA_INIT, SD_PORTB_INIT}, \
    .mcps = {NULL, NULL}, \
    .curentMcp = NULL, \
    .i2c = NULL, \
}

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief SD Changer handle variables struct
typedef struct esp_sdchngr_dev
{
    uint8_t selectedSlot;
    uint8_t detectedCards;
    uint8_t poweredSlots;
    sdmmc_slot_config_t portConfigs[2];
    mcp23017_handle_t mcps[2];
    mcp23017_handle_t curentMcp;
    i2c_bus_handle_t i2c;
} esp_sdchngr_dev_t;

typedef esp_sdchngr_dev_t* esp_sdchngr_handle_t;

/**
 * @brief Initialize SD Changer handle
 * Creates the I2C bus and both MCP23017 expanders, then powers off all slots
 * and waits for the cards to reset.
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if handle is null
 *      - ESP_FAIL or an I2C error if the I2C bus or an MCP23017 can't be set up
 */
esp_err_t esp_sdchngr_init(esp_sdchngr_handle_t handle);

/**
 * @brief Select SD card to be connected to the sdmmc host
 *
 * SD must be detected by handle to be selected
 * @param handle [IN] sdchanger config struct
 * @param slot [IN] SD card slot [0-7]
 * @param slot_config [OUT] sdmmc slot config
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_NOT_FOUND if SD card is not detected
 *      - ESP_ERR_INVALID_ARG if slot is not supported
 */
esp_err_t esp_sdchngr_set_selected(esp_sdchngr_handle_t handle, uint8_t slot, sdmmc_slot_config_t *slot_config);

/**
 * @brief Turn SD card on/off
 * SD must be detected by handle to be powered
 *
 * @param handle resulting configuration
 * @param slot SD card slot [0-7]
 * @param power false-OFF true-ON
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_NOT_FOUND if SD card is not detected
 */
esp_err_t esp_sdchngr_set_power(esp_sdchngr_handle_t handle, uint8_t slot, bool power);

/**
 * @brief Get number of selected slot
 *
 * @param handle configuration
 * @return [0-7] last selected slot (0 if none was selected yet, or if handle is null)
 */
uint8_t esp_sdchngr_get_selected(esp_sdchngr_handle_t handle);

/**
 * @brief Get bitmask of detected cards
 *
 * @param handle configuration
 * @param nDetected number of detected cards
 * @param slots bitmask of slots with detected cards
 * @return
 *      - ESP_OK on success
 */
esp_err_t esp_sdchngr_get_detected(esp_sdchngr_handle_t handle, uint8_t *nDetected, uint8_t *slots);

/**
 * @brief Get bitmask of powered cards
 *
 * @param handle configuration
 * @param nPowered number of powered cards
 * @param slots bitmask of slots with powered cards
 * @return
 *      - ESP_OK on success
 */
esp_err_t esp_sdchngr_get_powered(esp_sdchngr_handle_t handle, uint8_t *nPowered, uint8_t *slots);

/**
 * @brief
 *
 * @param handle configuration
 * @param slot sd card slot
 * @return true if slot is selected, false otherwise or if handle is null
 */
bool esp_sdchngr_is_selected(esp_sdchngr_handle_t handle, uint8_t slot);

/**
 * @brief
 *
 * @param handle configuration
 * @param slot sd card slot
 * @return true if card is powered, false otherwise or if handle is null
 */
bool esp_sdchngr_is_powered(esp_sdchngr_handle_t handle, uint8_t slot);

/**
 * @brief
 *
 * @param handle configuration
 * @param slot sd card slot
 * @return true if card is detected, false otherwise or if handle is null
 */
bool esp_sdchngr_is_detected(esp_sdchngr_handle_t handle, uint8_t slot);

/**
 * @brief Get the sdmmc slot config (port A or B pins) for a slot
 *
 * @param handle configuration
 * @param slot sd card slot [0-7]
 * @param slot_config [OUT] sdmmc slot config for the slot's port
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if handle or slot_config is null, or slot is out of range
 */
esp_err_t esp_sdchngr_set_port(esp_sdchngr_handle_t handle, uint8_t slot, sdmmc_slot_config_t *slot_config);
/**
 * @brief Set the handle's current MCP23017 (port A or B) for a slot
 *
 * @param handle configuration
 * @param slot sd card slot [0-7]
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if handle is null or slot is out of range
 */
esp_err_t esp_sdchngr_set_mcp(esp_sdchngr_handle_t handle, uint8_t slot);

#ifdef __cplusplus
}
#endif