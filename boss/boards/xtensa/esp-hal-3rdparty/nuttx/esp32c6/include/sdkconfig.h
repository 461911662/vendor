/*
 * Copyright (c) 2021 Espressif Systems (Shanghai) Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#define CONFIG_SOC_ADC_SUPPORTED 1
#define CONFIG_SOC_DEDICATED_GPIO_SUPPORTED 1
#define CONFIG_SOC_UART_SUPPORTED 1
#define CONFIG_SOC_GDMA_SUPPORTED 1
#define CONFIG_SOC_GPTIMER_SUPPORTED 1
#define CONFIG_SOC_PCNT_SUPPORTED 1
#define CONFIG_SOC_MCPWM_SUPPORTED 1
#define CONFIG_SOC_TWAI_SUPPORTED 1
#define CONFIG_SOC_ETM_SUPPORTED 1
#define CONFIG_SOC_PARLIO_SUPPORTED 1
#define CONFIG_SOC_BT_SUPPORTED 1
#define CONFIG_SOC_IEEE802154_SUPPORTED 1
#define CONFIG_SOC_ASYNC_MEMCPY_SUPPORTED 1
#define CONFIG_SOC_USB_SERIAL_JTAG_SUPPORTED 1
#define CONFIG_SOC_TEMP_SENSOR_SUPPORTED 1
#define CONFIG_SOC_WIFI_SUPPORTED 1
#define CONFIG_SOC_SUPPORTS_SECURE_DL_MODE 1
#define CONFIG_SOC_ULP_SUPPORTED 1
#define CONFIG_SOC_LP_CORE_SUPPORTED 1
#define CONFIG_SOC_EFUSE_KEY_PURPOSE_FIELD 1
#define CONFIG_SOC_RTC_FAST_MEM_SUPPORTED 1
#define CONFIG_SOC_RTC_MEM_SUPPORTED 1
#define CONFIG_SOC_I2S_SUPPORTED 1
#define CONFIG_SOC_RMT_SUPPORTED 1
#define CONFIG_SOC_SDM_SUPPORTED 1
#define CONFIG_SOC_GPSPI_SUPPORTED 1
#define CONFIG_SOC_LEDC_SUPPORTED 1
#define CONFIG_SOC_I2C_SUPPORTED 1
#define CONFIG_SOC_SYSTIMER_SUPPORTED 1
#define CONFIG_SOC_SUPPORT_COEXISTENCE 1
#define CONFIG_SOC_AES_SUPPORTED 1
#define CONFIG_SOC_MPI_SUPPORTED 1
#define CONFIG_SOC_SHA_SUPPORTED 1
#define CONFIG_SOC_HMAC_SUPPORTED 1
#define CONFIG_SOC_DIG_SIGN_SUPPORTED 1
#define CONFIG_SOC_ECC_SUPPORTED 1
#define CONFIG_SOC_FLASH_ENC_SUPPORTED 1
#define CONFIG_SOC_SECURE_BOOT_SUPPORTED 1
#define CONFIG_SOC_SDIO_SLAVE_SUPPORTED 1
#define CONFIG_SOC_BOD_SUPPORTED 1
#define CONFIG_SOC_APM_SUPPORTED 1
#define CONFIG_SOC_PMU_SUPPORTED 1
#define CONFIG_SOC_PAU_SUPPORTED 1
#define CONFIG_SOC_LP_TIMER_SUPPORTED 1
#define CONFIG_SOC_LP_AON_SUPPORTED 1
#define CONFIG_SOC_LP_I2C_SUPPORTED 1
#define CONFIG_SOC_XTAL_SUPPORT_40M 1
#define CONFIG_SOC_AES_SUPPORT_DMA 1
#define CONFIG_SOC_AES_GDMA 1
#define CONFIG_SOC_AES_SUPPORT_AES_128 1
#define CONFIG_SOC_AES_SUPPORT_AES_256 1
#define CONFIG_SOC_ADC_DIG_CTRL_SUPPORTED 1
#define CONFIG_SOC_ADC_DIG_IIR_FILTER_SUPPORTED 1
#define CONFIG_SOC_ADC_MONITOR_SUPPORTED 1
#define CONFIG_SOC_ADC_DMA_SUPPORTED 1
#define CONFIG_SOC_ADC_PERIPH_NUM 1
#define CONFIG_SOC_ADC_MAX_CHANNEL_NUM 7
#define CONFIG_SOC_ADC_ATTEN_NUM 4
#define CONFIG_SOC_ADC_DIGI_CONTROLLER_NUM 1
#define CONFIG_SOC_ADC_PATT_LEN_MAX 8
#define CONFIG_SOC_ADC_DIGI_MAX_BITWIDTH 12
#define CONFIG_SOC_ADC_DIGI_MIN_BITWIDTH 12
#define CONFIG_SOC_ADC_DIGI_IIR_FILTER_NUM 2
#define CONFIG_SOC_ADC_DIGI_MONITOR_NUM 2
#define CONFIG_SOC_ADC_DIGI_RESULT_BYTES 4
#define CONFIG_SOC_ADC_DIGI_DATA_BYTES_PER_CONV 4
#define CONFIG_SOC_ADC_SAMPLE_FREQ_THRES_HIGH 83333
#define CONFIG_SOC_ADC_SAMPLE_FREQ_THRES_LOW 611
#define CONFIG_SOC_ADC_RTC_MIN_BITWIDTH 12
#define CONFIG_SOC_ADC_RTC_MAX_BITWIDTH 12
#define CONFIG_SOC_ADC_CALIBRATION_V1_SUPPORTED 1
#define CONFIG_SOC_ADC_SELF_HW_CALI_SUPPORTED 1
#define CONFIG_SOC_ADC_CALIB_CHAN_COMPENS_SUPPORTED 1
#define CONFIG_SOC_ADC_TEMPERATURE_SHARE_INTR 1
#define CONFIG_SOC_BROWNOUT_RESET_SUPPORTED 1
#define CONFIG_SOC_SHARED_IDCACHE_SUPPORTED 1
#define CONFIG_SOC_CACHE_FREEZE_SUPPORTED 1
#define CONFIG_SOC_CPU_CORES_NUM 1
#define CONFIG_SOC_CPU_INTR_NUM 32
#define CONFIG_SOC_CPU_HAS_FLEXIBLE_INTC 1
#define CONFIG_SOC_INT_PLIC_SUPPORTED 1
#define CONFIG_SOC_CPU_BREAKPOINTS_NUM 4
#define CONFIG_SOC_CPU_WATCHPOINTS_NUM 4
#define CONFIG_SOC_CPU_WATCHPOINT_SIZE 0x80000000
#define CONFIG_SOC_CPU_HAS_PMA 1
#define CONFIG_SOC_CPU_IDRAM_SPLIT_USING_PMP 1
#define CONFIG_SOC_DS_SIGNATURE_MAX_BIT_LEN 3072
#define CONFIG_SOC_DS_KEY_PARAM_MD_IV_LENGTH 16
#define CONFIG_SOC_DS_KEY_CHECK_MAX_WAIT_US 1100
#define CONFIG_SOC_GDMA_GROUPS 1
#define CONFIG_SOC_GDMA_PAIRS_PER_GROUP 3
#define CONFIG_SOC_GDMA_SUPPORT_ETM 1
#define CONFIG_SOC_ETM_GROUPS 1
#define CONFIG_SOC_ETM_CHANNELS_PER_GROUP 50
#define CONFIG_SOC_GPIO_PORT 1
#define CONFIG_SOC_GPIO_PIN_COUNT 31
#define CONFIG_SOC_GPIO_SUPPORT_PIN_GLITCH_FILTER 1
#define CONFIG_SOC_GPIO_FLEX_GLITCH_FILTER_NUM 8
#define CONFIG_SOC_GPIO_SUPPORT_ETM 1
#define CONFIG_SOC_GPIO_SUPPORT_RTC_INDEPENDENT 1
#define CONFIG_SOC_GPIO_SUPPORT_DEEPSLEEP_WAKEUP 1
#define CONFIG_SOC_GPIO_DEEP_SLEEP_WAKE_VALID_GPIO_MASK 0
#define CONFIG_SOC_GPIO_VALID_DIGITAL_IO_PAD_MASK 0x000000007FFFFF00
#define CONFIG_SOC_GPIO_SUPPORT_FORCE_HOLD 1
#define CONFIG_SOC_GPIO_SUPPORT_HOLD_SINGLE_IO_IN_DSLP 1
#define CONFIG_SOC_RTCIO_PIN_COUNT 8
#define CONFIG_SOC_RTCIO_INPUT_OUTPUT_SUPPORTED 1
#define CONFIG_SOC_RTCIO_HOLD_SUPPORTED 1
#define CONFIG_SOC_RTCIO_WAKE_SUPPORTED 1
#define CONFIG_SOC_DEDIC_GPIO_OUT_CHANNELS_NUM 8
#define CONFIG_SOC_DEDIC_GPIO_IN_CHANNELS_NUM 8
#define CONFIG_SOC_DEDIC_PERIPH_ALWAYS_ENABLE 1
#define CONFIG_SOC_I2C_NUM 1
#define CONFIG_SOC_I2C_FIFO_LEN 32
#define CONFIG_SOC_I2C_CMD_REG_NUM 8
#define CONFIG_SOC_I2C_SUPPORT_SLAVE 1
#define CONFIG_SOC_I2C_SUPPORT_HW_CLR_BUS 1
#define CONFIG_SOC_I2C_SUPPORT_XTAL 1
#define CONFIG_SOC_I2C_SUPPORT_RTC 1
#define CONFIG_SOC_LP_I2C_NUM 1
#define CONFIG_SOC_LP_I2C_FIFO_LEN 16
#define CONFIG_SOC_I2S_NUM 1
#define CONFIG_SOC_I2S_HW_VERSION_2 1
#define CONFIG_SOC_I2S_SUPPORTS_XTAL 1
#define CONFIG_SOC_I2S_SUPPORTS_PLL_F160M 1
#define CONFIG_SOC_I2S_SUPPORTS_PCM 1
#define CONFIG_SOC_I2S_SUPPORTS_PDM 1
#define CONFIG_SOC_I2S_SUPPORTS_PDM_TX 1
#define CONFIG_SOC_I2S_PDM_MAX_TX_LINES 2
#define CONFIG_SOC_I2S_SUPPORTS_TDM 1
#define CONFIG_SOC_LEDC_SUPPORT_PLL_DIV_CLOCK 1
#define CONFIG_SOC_LEDC_SUPPORT_XTAL_CLOCK 1
#define CONFIG_SOC_LEDC_CHANNEL_NUM 6
#define CONFIG_SOC_LEDC_TIMER_BIT_WIDTH 20
#define CONFIG_SOC_LEDC_SUPPORT_FADE_STOP 1
#define CONFIG_SOC_LEDC_GAMMA_CURVE_FADE_SUPPORTED 1
#define CONFIG_SOC_LEDC_GAMMA_CURVE_FADE_RANGE_MAX 16
#define CONFIG_SOC_LEDC_FADE_PARAMS_BIT_WIDTH 10
#define CONFIG_SOC_MMU_PAGE_SIZE_CONFIGURABLE 1
#define CONFIG_SOC_MMU_PERIPH_NUM 1
#define CONFIG_SOC_MMU_LINEAR_ADDRESS_REGION_NUM 1
#define CONFIG_SOC_MMU_DI_VADDR_SHARED 1
#define CONFIG_SOC_MPU_MIN_REGION_SIZE 0x20000000
#define CONFIG_SOC_MPU_REGIONS_MAX_NUM 8
#define CONFIG_SOC_PCNT_GROUPS 1
#define CONFIG_SOC_PCNT_UNITS_PER_GROUP 4
#define CONFIG_SOC_PCNT_CHANNELS_PER_UNIT 2
#define CONFIG_SOC_PCNT_THRES_POINT_PER_UNIT 2
#define CONFIG_SOC_PCNT_SUPPORT_RUNTIME_THRES_UPDATE 1
#define CONFIG_SOC_RMT_GROUPS 1
#define CONFIG_SOC_RMT_TX_CANDIDATES_PER_GROUP 2
#define CONFIG_SOC_RMT_RX_CANDIDATES_PER_GROUP 2
#define CONFIG_SOC_RMT_CHANNELS_PER_GROUP 4
#define CONFIG_SOC_RMT_MEM_WORDS_PER_CHANNEL 48
#define CONFIG_SOC_RMT_SUPPORT_RX_PINGPONG 1
#define CONFIG_SOC_RMT_SUPPORT_RX_DEMODULATION 1
#define CONFIG_SOC_RMT_SUPPORT_TX_ASYNC_STOP 1
#define CONFIG_SOC_RMT_SUPPORT_TX_LOOP_COUNT 1
#define CONFIG_SOC_RMT_SUPPORT_TX_LOOP_AUTO_STOP 1
#define CONFIG_SOC_RMT_SUPPORT_TX_SYNCHRO 1
#define CONFIG_SOC_RMT_SUPPORT_TX_CARRIER_DATA_ONLY 1
#define CONFIG_SOC_RMT_SUPPORT_XTAL 1
#define CONFIG_SOC_RMT_SUPPORT_RC_FAST 1
#define CONFIG_SOC_MCPWM_GROUPS 1
#define CONFIG_SOC_MCPWM_TIMERS_PER_GROUP 3
#define CONFIG_SOC_MCPWM_OPERATORS_PER_GROUP 3
#define CONFIG_SOC_MCPWM_COMPARATORS_PER_OPERATOR 2
#define CONFIG_SOC_MCPWM_GENERATORS_PER_OPERATOR 2
#define CONFIG_SOC_MCPWM_TRIGGERS_PER_OPERATOR 2
#define CONFIG_SOC_MCPWM_GPIO_FAULTS_PER_GROUP 3
#define CONFIG_SOC_MCPWM_CAPTURE_TIMERS_PER_GROUP 1
#define CONFIG_SOC_MCPWM_CAPTURE_CHANNELS_PER_TIMER 3
#define CONFIG_SOC_MCPWM_GPIO_SYNCHROS_PER_GROUP 3
#define CONFIG_SOC_MCPWM_SWSYNC_CAN_PROPAGATE 1
#define CONFIG_SOC_MCPWM_SUPPORT_ETM 1
#define CONFIG_SOC_MCPWM_CAPTURE_CLK_FROM_GROUP 1
#define CONFIG_SOC_PARLIO_GROUPS 1
#define CONFIG_SOC_PARLIO_TX_UNITS_PER_GROUP 1
#define CONFIG_SOC_PARLIO_RX_UNITS_PER_GROUP 1
#define CONFIG_SOC_PARLIO_TX_UNIT_MAX_DATA_WIDTH 16
#define CONFIG_SOC_PARLIO_RX_UNIT_MAX_DATA_WIDTH 16
#define CONFIG_SOC_PARLIO_TX_RX_SHARE_INTERRUPT 1
#define CONFIG_SOC_RSA_MAX_BIT_LEN 3072
#define CONFIG_SOC_SHA_DMA_MAX_BUFFER_SIZE 3968
#define CONFIG_SOC_SHA_SUPPORT_DMA 1
#define CONFIG_SOC_SHA_SUPPORT_RESUME 1
#define CONFIG_SOC_SHA_GDMA 1
#define CONFIG_SOC_SHA_SUPPORT_SHA1 1
#define CONFIG_SOC_SHA_SUPPORT_SHA224 1
#define CONFIG_SOC_SHA_SUPPORT_SHA256 1
#define CONFIG_SOC_SDM_GROUPS 1
#define CONFIG_SOC_SDM_CHANNELS_PER_GROUP 4
#define CONFIG_SOC_SDM_CLK_SUPPORT_PLL_F80M 1
#define CONFIG_SOC_SDM_CLK_SUPPORT_XTAL 1
#define CONFIG_SOC_SPI_PERIPH_NUM 2
#define CONFIG_SOC_SPI_MAX_CS_NUM 6
#define CONFIG_SOC_SPI_MAXIMUM_BUFFER_SIZE 64
#define CONFIG_SOC_SPI_SUPPORT_DDRCLK 1
#define CONFIG_SOC_SPI_SLAVE_SUPPORT_SEG_TRANS 1
#define CONFIG_SOC_SPI_SUPPORT_CD_SIG 1
#define CONFIG_SOC_SPI_SUPPORT_CONTINUOUS_TRANS 1
#define CONFIG_SOC_SPI_SUPPORT_SLAVE_HD_VER2 1
#define CONFIG_SOC_SPI_SUPPORT_CLK_XTAL 1
#define CONFIG_SOC_SPI_SUPPORT_CLK_PLL_F80M 1
#define CONFIG_SOC_SPI_SUPPORT_CLK_RC_FAST 1
#define CONFIG_SOC_MEMSPI_IS_INDEPENDENT 1
#define CONFIG_SOC_SPI_MAX_PRE_DIVIDER 16
#define CONFIG_SOC_SPI_MEM_SUPPORT_AUTO_WAIT_IDLE 1
#define CONFIG_SOC_SPI_MEM_SUPPORT_AUTO_SUSPEND 1
#define CONFIG_SOC_SPI_MEM_SUPPORT_AUTO_RESUME 1
#define CONFIG_SOC_SPI_MEM_SUPPORT_IDLE_INTR 1
#define CONFIG_SOC_SPI_MEM_SUPPORT_SW_SUSPEND 1
#define CONFIG_SOC_SPI_MEM_SUPPORT_CHECK_SUS 1
#define CONFIG_SOC_SPI_MEM_SUPPORT_WRAP 1
#define CONFIG_SOC_MEMSPI_SRC_FREQ_80M_SUPPORTED 1
#define CONFIG_SOC_MEMSPI_SRC_FREQ_40M_SUPPORTED 1
#define CONFIG_SOC_MEMSPI_SRC_FREQ_20M_SUPPORTED 1
#define CONFIG_SOC_SYSTIMER_COUNTER_NUM 2
#define CONFIG_SOC_SYSTIMER_ALARM_NUM 3
#define CONFIG_SOC_SYSTIMER_BIT_WIDTH_LO 32
#define CONFIG_SOC_SYSTIMER_BIT_WIDTH_HI 20
#define CONFIG_SOC_SYSTIMER_FIXED_DIVIDER 1
#define CONFIG_SOC_SYSTIMER_SUPPORT_RC_FAST 1
#define CONFIG_SOC_SYSTIMER_INT_LEVEL 1
#define CONFIG_SOC_SYSTIMER_ALARM_MISS_COMPENSATE 1
#define CONFIG_SOC_SYSTIMER_SUPPORT_ETM 1
#define CONFIG_SOC_LP_TIMER_BIT_WIDTH_LO 32
#define CONFIG_SOC_LP_TIMER_BIT_WIDTH_HI 16
#define CONFIG_SOC_TIMER_GROUPS 2
#define CONFIG_SOC_TIMER_GROUP_TIMERS_PER_GROUP 1
#define CONFIG_SOC_TIMER_GROUP_COUNTER_BIT_WIDTH 54
#define CONFIG_SOC_TIMER_GROUP_SUPPORT_XTAL 1
#define CONFIG_SOC_TIMER_GROUP_SUPPORT_RC_FAST 1
#define CONFIG_SOC_TIMER_GROUP_TOTAL_TIMERS 2
#define CONFIG_SOC_TIMER_SUPPORT_ETM 1
#define CONFIG_SOC_MWDT_SUPPORT_XTAL 1
#define CONFIG_SOC_TWAI_CONTROLLER_NUM 2
#define CONFIG_SOC_TWAI_CLK_SUPPORT_XTAL 1
#define CONFIG_SOC_TWAI_BRP_MIN 2
#define CONFIG_SOC_TWAI_BRP_MAX 32768
#define CONFIG_SOC_TWAI_SUPPORTS_RX_STATUS 1
#define CONFIG_SOC_EFUSE_DIS_DOWNLOAD_ICACHE 1
#define CONFIG_SOC_EFUSE_DIS_PAD_JTAG 1
#define CONFIG_SOC_EFUSE_DIS_USB_JTAG 1
#define CONFIG_SOC_EFUSE_DIS_DIRECT_BOOT 1
#define CONFIG_SOC_EFUSE_SOFT_DIS_JTAG 1
#define CONFIG_SOC_EFUSE_DIS_ICACHE 1
#define CONFIG_SOC_EFUSE_BLOCK9_KEY_PURPOSE_QUIRK 1
#define CONFIG_SOC_SECURE_BOOT_V2_RSA 1
#define CONFIG_SOC_SECURE_BOOT_V2_ECC 1
#define CONFIG_SOC_EFUSE_SECURE_BOOT_KEY_DIGESTS 3
#define CONFIG_SOC_EFUSE_REVOKE_BOOT_KEY_DIGESTS 1
#define CONFIG_SOC_SUPPORT_SECURE_BOOT_REVOKE_KEY 1
#define CONFIG_SOC_FLASH_ENCRYPTED_XTS_AES_BLOCK_MAX 32
#define CONFIG_SOC_FLASH_ENCRYPTION_XTS_AES 1
#define CONFIG_SOC_FLASH_ENCRYPTION_XTS_AES_128 1
#define CONFIG_SOC_CRYPTO_DPA_PROTECTION_SUPPORTED 1
#define CONFIG_SOC_UART_NUM 2
#define CONFIG_SOC_UART_FIFO_LEN 128
#define CONFIG_SOC_UART_BITRATE_MAX 5000000
#define CONFIG_SOC_UART_SUPPORT_PLL_F80M_CLK 1
#define CONFIG_SOC_UART_SUPPORT_RTC_CLK 1
#define CONFIG_SOC_UART_SUPPORT_XTAL_CLK 1
#define CONFIG_SOC_UART_SUPPORT_WAKEUP_INT 1
#define CONFIG_SOC_UART_SUPPORT_FSM_TX_WAIT_SEND 1
#define CONFIG_SOC_COEX_HW_PTI 1
#define CONFIG_SOC_EXTERNAL_COEX_ADVANCE 1
#define CONFIG_SOC_PHY_DIG_REGS_MEM_SIZE 21
#define CONFIG_SOC_WIFI_LIGHT_SLEEP_CLK_WIDTH 12
#define CONFIG_SOC_PM_SUPPORT_WIFI_WAKEUP 1
#define CONFIG_SOC_PM_SUPPORT_BEACON_WAKEUP 1
#define CONFIG_SOC_PM_SUPPORT_BT_WAKEUP 1
#define CONFIG_SOC_PM_SUPPORT_EXT1_WAKEUP 1
#define CONFIG_SOC_PM_SUPPORT_EXT1_WAKEUP_MODE_PER_PIN 1
#define CONFIG_SOC_PM_SUPPORT_CPU_PD 1
#define CONFIG_SOC_PM_SUPPORT_MODEM_PD 1
#define CONFIG_SOC_PM_SUPPORT_XTAL32K_PD 1
#define CONFIG_SOC_PM_SUPPORT_RC32K_PD 1
#define CONFIG_SOC_PM_SUPPORT_RC_FAST_PD 1
#define CONFIG_SOC_PM_SUPPORT_VDDSDIO_PD 1
#define CONFIG_SOC_PM_SUPPORT_TOP_PD 1
#define CONFIG_SOC_PM_SUPPORT_HP_AON_PD 1
#define CONFIG_SOC_PM_SUPPORT_MAC_BB_PD 1
#define CONFIG_SOC_PM_SUPPORT_RTC_PERIPH_PD 1
#define CONFIG_SOC_PM_SUPPORT_PMU_MODEM_STATE 1
#define CONFIG_SOC_PM_SUPPORT_DEEPSLEEP_CHECK_STUB_ONLY 1
#define CONFIG_SOC_PM_CPU_RETENTION_BY_SW 1
#define CONFIG_SOC_PM_MODEM_RETENTION_BY_REGDMA 1
#define CONFIG_SOC_PM_RETENTION_HAS_CLOCK_BUG 1
#define CONFIG_SOC_PM_PAU_LINK_NUM 4
#define CONFIG_SOC_CLK_RC_FAST_SUPPORT_CALIBRATION 1
#define CONFIG_SOC_MODEM_CLOCK_IS_INDEPENDENT 1
#define CONFIG_SOC_CLK_XTAL32K_SUPPORTED 1
#define CONFIG_SOC_CLK_OSC_SLOW_SUPPORTED 1
#define CONFIG_SOC_CLK_RC32K_SUPPORTED 1
#define CONFIG_SOC_TEMPERATURE_SENSOR_SUPPORT_FAST_RC 1
#define CONFIG_SOC_TEMPERATURE_SENSOR_SUPPORT_XTAL 1
#define CONFIG_SOC_TEMPERATURE_SENSOR_INTR_SUPPORT 1
#define CONFIG_SOC_WIFI_HW_TSF 1
#define CONFIG_SOC_WIFI_FTM_SUPPORT 1
#define CONFIG_SOC_WIFI_GCMP_SUPPORT 1
#define CONFIG_SOC_WIFI_WAPI_SUPPORT 1
#define CONFIG_SOC_WIFI_CSI_SUPPORT 1
#define CONFIG_SOC_WIFI_MESH_SUPPORT 1
#define CONFIG_SOC_WIFI_HE_SUPPORT 1
#define CONFIG_SOC_BLE_SUPPORTED 1
#define CONFIG_SOC_BLE_MESH_SUPPORTED 1
#define CONFIG_SOC_ESP_NIMBLE_CONTROLLER 1
#define CONFIG_SOC_BLE_50_SUPPORTED 1
#define CONFIG_SOC_BLE_DEVICE_PRIVACY_SUPPORTED 1
#define CONFIG_SOC_BLE_POWER_CONTROL_SUPPORTED 1
#define CONFIG_SOC_BLE_PERIODIC_ADV_ENH_SUPPORTED 1
#define CONFIG_SOC_BLUFI_SUPPORTED 1
#define CONFIG_SOC_BLE_MULTI_CONN_OPTIMIZATION 1
#define CONFIG_SOC_BLE_USE_WIFI_PWR_CLK_WORKAROUND 1
#define CONFIG_SOC_PHY_COMBO_MODULE 1
#define CONFIG_SOC_CAPS_NO_RESET_BY_ANA_BOD 1

#define CONFIG_ESP_ROM_HAS_CRC_LE 1
#define CONFIG_ESP_ROM_HAS_CRC_BE 1
#define CONFIG_ESP_ROM_HAS_JPEG_DECODE 1
#define CONFIG_ESP_ROM_UART_CLK_IS_XTAL 1
#define CONFIG_ESP_ROM_USB_SERIAL_DEVICE_NUM 3
#define CONFIG_ESP_ROM_HAS_RETARGETABLE_LOCKING 1
#define CONFIG_ESP_ROM_GET_CLK_FREQ 1
#define CONFIG_ESP_ROM_HAS_RVFPLIB 1
#define CONFIG_ESP_ROM_HAS_HAL_WDT 1
#define CONFIG_ESP_ROM_HAS_HAL_SYSTIMER 1
#define CONFIG_ESP_ROM_HAS_HEAP_TLSF 1
#define CONFIG_ESP_ROM_TLSF_CHECK_PATCH 1
#define CONFIG_ESP_ROM_HAS_LAYOUT_TABLE 1
#define CONFIG_ESP_ROM_HAS_SPI_FLASH 1
#define CONFIG_ESP_ROM_HAS_REGI2C_BUG 1
#define CONFIG_ESP_ROM_HAS_NEWLIB_NORMAL_FORMAT 1
#define CONFIG_ESP_ROM_REV0_HAS_NO_ECDSA_INTERFACE 1
#define CONFIG_ESP_ROM_WDT_INIT_PATCH 1
#define CONFIG_ESP_ROM_NEEDS_SET_CACHE_MMU_SIZE 1
#define CONFIG_ESP_ROM_RAM_APP_NEEDS_MMU_INIT 1

#define CONFIG_EFUSE_MAX_BLK_LEN 256

#define CONFIG_ESP_MAC_ADDR_UNIVERSE_WIFI_STA 1
#define CONFIG_ESP_MAC_ADDR_UNIVERSE_WIFI_AP 1
#define CONFIG_ESP_MAC_ADDR_UNIVERSE_BT 1
#define CONFIG_ESP_MAC_ADDR_UNIVERSE_ETH 1
#define CONFIG_ESP_MAC_ADDR_UNIVERSE_IEEE802154 1
#define CONFIG_ESP_MAC_UNIVERSAL_MAC_ADDRESSES_FOUR 1
#define CONFIG_ESP32C6_UNIVERSAL_MAC_ADDRESSES_FOUR 1
#define CONFIG_ESP32C6_UNIVERSAL_MAC_ADDRESSES 4

#define CONFIG_ESP_PHY_MAX_WIFI_TX_POWER 20
#define CONFIG_ESP_PHY_MAX_TX_POWER 20
#define CONFIG_ESP_PHY_RF_CAL_PARTIAL 1
#define CONFIG_ESP_PHY_CALIBRATION_MODE 0

#define CONFIG_HAL_ASSERTION_EQUALS_SYSTEM 1
#define CONFIG_HAL_DEFAULT_ASSERTION_LEVEL 2
#define CONFIG_HAL_SYSTIMER_USE_ROM_IMPL 1
#define CONFIG_HAL_WDT_USE_ROM_IMPL 1
#define CONFIG_HAL_SPI_MASTER_FUNC_IN_IRAM 1
#define CONFIG_HAL_SPI_SLAVE_FUNC_IN_IRAM 1


#define CONFIG_NEWLIB_STDOUT_LINE_ENDING_CRLF 1
#define CONFIG_NEWLIB_STDIN_LINE_ENDING_CR 1
#define CONFIG_NEWLIB_TIME_SYSCALL_USE_RTC_HRT 1

#include <nuttx/config.h>

#undef CONFIG_MBEDTLS_INTERNAL_MEM_ALLOC
#undef CONFIG_MBEDTLS_ASYMMETRIC_CONTENT_LEN
#undef CONFIG_MBEDTLS_SSL_IN_CONTENT_LEN
#undef CONFIG_MBEDTLS_SSL_OUT_CONTENT_LEN
#undef CONFIG_MBEDTLS_SSL_KEEP_PEER_CERTIFICATE
#undef CONFIG_MBEDTLS_PKCS7_C
#undef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
#undef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE_DEFAULT_FULL
#undef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE_MAX_CERTS
#undef CONFIG_MBEDTLS_HARDWARE_AES
#undef CONFIG_MBEDTLS_AES_USE_INTERRUPT
#undef CONFIG_MBEDTLS_HARDWARE_MPI
#undef CONFIG_MBEDTLS_MPI_USE_INTERRUPT
#undef CONFIG_MBEDTLS_HARDWARE_SHA
#undef CONFIG_MBEDTLS_HARDWARE_ECC
#undef CONFIG_MBEDTLS_ECC_OTHER_CURVES_SOFT_FALLBACK
#undef CONFIG_MBEDTLS_ROM_MD5
#undef CONFIG_MBEDTLS_HAVE_TIME
#undef CONFIG_MBEDTLS_ECDSA_DETERMINISTIC
#undef CONFIG_MBEDTLS_SHA512_C
#undef CONFIG_MBEDTLS_TLS_SERVER_AND_CLIENT
#undef CONFIG_MBEDTLS_TLS_SERVER
#undef CONFIG_MBEDTLS_TLS_CLIENT
#undef CONFIG_MBEDTLS_TLS_ENABLED
#undef CONFIG_MBEDTLS_KEY_EXCHANGE_RSA
#undef CONFIG_MBEDTLS_KEY_EXCHANGE_ELLIPTIC_CURVE
#undef CONFIG_MBEDTLS_KEY_EXCHANGE_ECDHE_RSA
#undef CONFIG_MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA
#undef CONFIG_MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA
#undef CONFIG_MBEDTLS_KEY_EXCHANGE_ECDH_RSA
#undef CONFIG_MBEDTLS_SSL_RENEGOTIATION
#undef CONFIG_MBEDTLS_SSL_PROTO_TLS1_2
#undef CONFIG_MBEDTLS_SSL_ALPN
#undef CONFIG_MBEDTLS_CLIENT_SSL_SESSION_TICKETS
#undef CONFIG_MBEDTLS_SERVER_SSL_SESSION_TICKETS
#undef CONFIG_MBEDTLS_AES_C
#undef CONFIG_MBEDTLS_CCM_C
#undef CONFIG_MBEDTLS_GCM_C
#undef CONFIG_MBEDTLS_PEM_PARSE_C
#undef CONFIG_MBEDTLS_PEM_WRITE_C
#undef CONFIG_MBEDTLS_X509_CRL_PARSE_C
#undef CONFIG_MBEDTLS_X509_CSR_PARSE_C
#undef CONFIG_MBEDTLS_ECP_C
#undef CONFIG_MBEDTLS_ECDH_C
#undef CONFIG_MBEDTLS_ECDSA_C
#undef CONFIG_MBEDTLS_ECP_DP_SECP192R1_ENABLED
#undef CONFIG_MBEDTLS_ECP_DP_SECP224R1_ENABLED
#undef CONFIG_MBEDTLS_ECP_DP_SECP256R1_ENABLED
#undef CONFIG_MBEDTLS_ECP_DP_SECP384R1_ENABLED
#undef CONFIG_MBEDTLS_ECP_DP_SECP521R1_ENABLED
#undef CONFIG_MBEDTLS_ECP_DP_SECP192K1_ENABLED
#undef CONFIG_MBEDTLS_ECP_DP_SECP224K1_ENABLED
#undef CONFIG_MBEDTLS_ECP_DP_SECP256K1_ENABLED
#undef CONFIG_MBEDTLS_ECP_DP_BP256R1_ENABLED
#undef CONFIG_MBEDTLS_ECP_DP_BP384R1_ENABLED
#undef CONFIG_MBEDTLS_ECP_DP_BP512R1_ENABLED
#undef CONFIG_MBEDTLS_ECP_DP_CURVE25519_ENABLED
#undef CONFIG_MBEDTLS_ECP_NIST_OPTIM
#undef CONFIG_MBEDTLS_LARGE_KEY_SOFTWARE_MPI

#define CONFIG_MBEDTLS_ASYMMETRIC_CONTENT_LEN 1
#define CONFIG_MBEDTLS_SSL_IN_CONTENT_LEN 16384
#define CONFIG_MBEDTLS_SSL_OUT_CONTENT_LEN 4096
#define CONFIG_MBEDTLS_SSL_KEEP_PEER_CERTIFICATE 1
#define CONFIG_MBEDTLS_PKCS7_C 1
#define CONFIG_MBEDTLS_AES_USE_INTERRUPT 1
#define CONFIG_MBEDTLS_MPI_USE_INTERRUPT 1
#define CONFIG_MBEDTLS_ECC_OTHER_CURVES_SOFT_FALLBACK 1
#define CONFIG_MBEDTLS_ROM_MD5 1
#define CONFIG_MBEDTLS_HAVE_TIME 1
#define CONFIG_MBEDTLS_ECDSA_DETERMINISTIC 1
#define CONFIG_MBEDTLS_SHA512_C 1
#define CONFIG_MBEDTLS_TLS_SERVER_AND_CLIENT 1
#define CONFIG_MBEDTLS_TLS_SERVER 1
#define CONFIG_MBEDTLS_TLS_CLIENT 1
#define CONFIG_MBEDTLS_TLS_ENABLED 1
#define CONFIG_MBEDTLS_KEY_EXCHANGE_RSA 1
#define CONFIG_MBEDTLS_KEY_EXCHANGE_ELLIPTIC_CURVE 1
#define CONFIG_MBEDTLS_KEY_EXCHANGE_ECDHE_RSA 1
#define CONFIG_MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA 1
#define CONFIG_MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA 1
#define CONFIG_MBEDTLS_KEY_EXCHANGE_ECDH_RSA 1
#define CONFIG_MBEDTLS_SSL_RENEGOTIATION 1
#define CONFIG_MBEDTLS_SSL_PROTO_TLS1_2 1
#define CONFIG_MBEDTLS_SSL_ALPN 1
#define CONFIG_MBEDTLS_CLIENT_SSL_SESSION_TICKETS 1
#define CONFIG_MBEDTLS_SERVER_SSL_SESSION_TICKETS 1
#define CONFIG_MBEDTLS_AES_C 1
#define CONFIG_MBEDTLS_CCM_C 1
#define CONFIG_MBEDTLS_GCM_C 1
#define CONFIG_MBEDTLS_PEM_PARSE_C 1
#define CONFIG_MBEDTLS_PEM_WRITE_C 1
#define CONFIG_MBEDTLS_X509_CRL_PARSE_C 1
#define CONFIG_MBEDTLS_X509_CSR_PARSE_C 1
#define CONFIG_MBEDTLS_ECP_C 1
#define CONFIG_MBEDTLS_ECDH_C 1
#define CONFIG_MBEDTLS_ECDSA_C 1
#define CONFIG_MBEDTLS_ECP_DP_SECP192R1_ENABLED 1
#define CONFIG_MBEDTLS_ECP_DP_SECP224R1_ENABLED 1
#define CONFIG_MBEDTLS_ECP_DP_SECP256R1_ENABLED 1
#define CONFIG_MBEDTLS_ECP_DP_SECP384R1_ENABLED 1
#define CONFIG_MBEDTLS_ECP_DP_SECP521R1_ENABLED 1
#define CONFIG_MBEDTLS_ECP_DP_SECP192K1_ENABLED 1
#define CONFIG_MBEDTLS_ECP_DP_SECP224K1_ENABLED 1
#define CONFIG_MBEDTLS_ECP_DP_SECP256K1_ENABLED 1
#define CONFIG_MBEDTLS_ECP_DP_BP256R1_ENABLED 1
#define CONFIG_MBEDTLS_ECP_DP_BP384R1_ENABLED 1
#define CONFIG_MBEDTLS_ECP_DP_BP512R1_ENABLED 1
#define CONFIG_MBEDTLS_ECP_DP_CURVE25519_ENABLED 1
#define CONFIG_MBEDTLS_ECP_NIST_OPTIM 1
#define CONFIG_MBEDTLS_LARGE_KEY_SOFTWARE_MPI 1

#ifdef CONFIG_ESPRESSIF_WIFI
#define CONFIG_ESP_WIFI_ENABLED 1
#define CONFIG_ESP_WIFI_STATIC_RX_BUFFER_NUM CONFIG_ESPRESSIF_WIFI_STATIC_RX_BUFFER_NUM
#define CONFIG_ESP_WIFI_DYNAMIC_RX_BUFFER_NUM CONFIG_ESPRESSIF_WIFI_DYNAMIC_RX_BUFFER_NUM
#define CONFIG_ESP_WIFI_DYNAMIC_TX_BUFFER 1
#define CONFIG_ESP_WIFI_STATIC_RX_MGMT_BUFFER 1
#define CONFIG_ESP_WIFI_DYNAMIC_RX_MGMT_BUF 0
#define CONFIG_ESP_WIFI_RX_MGMT_BUF_NUM_DEF 5
#define CONFIG_ESP_WIFI_TX_BUFFER_TYPE 1
#define CONFIG_ESP_WIFI_DYNAMIC_TX_BUFFER_NUM CONFIG_ESPRESSIF_WIFI_DYNAMIC_TX_BUFFER_NUM
#define CONFIG_ESP_WIFI_AMPDU_TX_ENABLED CONFIG_ESPRESSIF_WIFI_AMPDU_TX_ENABLED
#define CONFIG_ESP_WIFI_TX_BA_WIN CONFIG_ESPRESSIF_WIFI_TX_BA_WIN
#define CONFIG_ESP_WIFI_AMPDU_RX_ENABLED CONFIG_ESPRESSIF_WIFI_AMPDU_RX_ENABLED
#define CONFIG_ESP_WIFI_RX_BA_WIN CONFIG_ESPRESSIF_WIFI_RX_BA_WIN
#define CONFIG_ESP_WIFI_NVS_ENABLED 1
#define CONFIG_ESP_WIFI_SOFTAP_BEACON_MAX_LEN 752
#define CONFIG_ESP_WIFI_MGMT_SBUF_NUM 32
#define CONFIG_ESP_WIFI_IRAM_OPT 1
#define CONFIG_ESP_WIFI_RX_IRAM_OPT 1
#define CONFIG_ESP_WIFI_ENABLE_WPA3_SAE CONFIG_ESPRESSIF_WIFI_ENABLE_WPA3_SAE
#define CONFIG_ESP_WIFI_ENABLE_SAE_PK CONFIG_ESPRESSIF_WIFI_ENABLE_SAE_PK
#define CONFIG_ESP_WIFI_SOFTAP_SAE_SUPPORT CONFIG_ESPRESSIF_WIFI_SOFTAP_SAE_SUPPORT
#define CONFIG_ESP_WIFI_ENABLE_WPA3_OWE_STA CONFIG_ESPRESSIF_WIFI_ENABLE_WPA3_OWE_STA
#define CONFIG_ESP_WIFI_SLP_DEFAULT_MIN_ACTIVE_TIME 50
#define CONFIG_ESP_WIFI_SLP_DEFAULT_MAX_ACTIVE_TIME 10
#define CONFIG_ESP_WIFI_SLP_DEFAULT_WAIT_BROADCAST_DATA_TIME 15
#define CONFIG_ESP_WIFI_STA_DISCONNECTED_PM_ENABLE CONFIG_ESPRESSIF_WIFI_STA_DISCONNECT_PM
#define CONFIG_ESP_WIFI_GMAC_SUPPORT 1
#if defined(CONFIG_ESPRESSIF_WIFI_SOFTAP) || defined(CONFIG_ESPRESSIF_WIFI_STATION_SOFTAP)
#define CONFIG_ESP_WIFI_SOFTAP_SUPPORT 1
#endif
#define CONFIG_ESP_WIFI_ESPNOW_MAX_ENCRYPT_NUM 7
#define CONFIG_ESP_WIFI_ENABLE_WIFI_TX_STATS 1
#define CONFIG_ESP_WIFI_MBEDTLS_CRYPTO 1
#define CONFIG_ESP_WIFI_MBEDTLS_TLS_CLIENT 1
#define CONFIG_ESP_WIFI_ENABLE_WIFI_RX_STATS 1
#define CONFIG_ESP_WIFI_ENABLE_WIFI_RX_MU_STATS 1
#endif

#ifdef CONFIG_WIRELESS_IEEE802154
#define CONFIG_IEEE802154_ENABLED 1
#define CONFIG_IEEE802154_RX_BUFFER_SIZE 20
#define CONFIG_IEEE802154_CCA_ED 1
#define CONFIG_IEEE802154_CCA_MODE 1
#define CONFIG_IEEE802154_CCA_THRESHOLD -60
#define CONFIG_IEEE802154_PENDING_TABLE_SIZE 20
#endif

#define CONFIG_ESP_REV_MIN_FULL 0
#define CONFIG_ESP_REV_MAX_FULL 99
#define CONFIG_IDF_TARGET_ARCH_RISCV 1
#define CONFIG_IDF_TARGET_ARCH "riscv"
#define CONFIG_IDF_TARGET "esp32c6"
#define CONFIG_IDF_TARGET_ESP32C6 1
#define CONFIG_IDF_FIRMWARE_CHIP_ID 0x000D
#define CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ CONFIG_ESPRESSIF_CPU_FREQ_MHZ
#define CONFIG_RTC_CLK_SRC_INT_RC 1
#define CONFIG_RTC_CLK_CAL_CYCLES 1024
#define CONFIG_RTC_CLOCK_BBPLL_POWER_ON_WITH_USB 1
#define CONFIG_XTAL_FREQ 40

#define CONFIG_HAL_SYSTIMER_USE_ROM_IMPL 1
#define CONFIG_HAL_WDT_USE_ROM_IMPL 1

#define CONFIG_MMU_PAGE_SIZE 0x10000
#define SOC_MMU_PAGE_SIZE CONFIG_MMU_PAGE_SIZE
#define CONFIG_LOG_TIMESTAMP_SOURCE_RTOS 1

#define CONFIG_IDF_ENV_FPGA 0

#define CONFIG_ESPTOOLPY_FLASHMODE_DIO 1

#ifdef CONFIG_ESPRESSIF_BROWNOUT_DET
#define CONFIG_ESP_BROWNOUT_DET_LVL CONFIG_ESPRESSIF_BROWNOUT_DET_LVL
#else
#define CONFIG_ESP_BROWNOUT_DET 0
#endif

#if (defined(CONFIG_UART0_SERIAL_CONSOLE) && defined(CONFIG_ESPRESSIF_UART0)) || defined(CONFIG_ESPRESSIF_USBSERIAL)
#define CONFIG_ESP_CONSOLE_UART_NUM 0
#elif defined(CONFIG_UART1_SERIAL_CONSOLE) && defined(CONFIG_ESPRESSIF_UART1)
#define CONFIG_ESP_CONSOLE_UART_NUM 1
#endif

#if defined(CONFIG_DEBUG_INFO)
#define CONFIG_LOG_DEFAULT_LEVEL 3
#define CONFIG_LOG_MAXIMUM_LEVEL 3
#elif defined(CONFIG_DEBUG_WARN)
#define CONFIG_LOG_DEFAULT_LEVEL 2
#define CONFIG_LOG_MAXIMUM_LEVEL 2
#elif defined(CONFIG_DEBUG_ERROR)
#define CONFIG_LOG_DEFAULT_LEVEL 1
#define CONFIG_LOG_MAXIMUM_LEVEL 1
#else
#define CONFIG_LOG_DEFAULT_LEVEL 0
#define CONFIG_LOG_MAXIMUM_LEVEL 0
#endif

#if defined(CONFIG_ESPRESSIF_RTC_CLK_EXT_XTAL)
#define CONFIG_RTC_CLK_SRC_EXT_CRYS     1
#elif defined(CONFIG_ESPRESSIF_RTC_CLK_EXT_OSC)
#define CONFIG_RTC_CLK_SRC_EXT_OSC      1
#elif defined(CONFIG_ESPRESSIF_RTC_CLK_INT_8MD256)
#define CONFIG_RTC_CLK_SRC_INT_8MD256   1
#endif

#if defined (CONFIG_ESPRESSIF_SIMPLE_BOOT) || \
    defined (CONFIG_ESPRESSIF_BOOTLOADER_MCUBOOT)
#  define CONFIG_ESP_CONSOLE_UART               1
#  define CONFIG_ESP_CONSOLE_UART_BAUDRATE      115200
#  define CONFIG_PARTITION_TABLE_OFFSET         0x0000
#  define CONFIG_BOOTLOADER_OFFSET_IN_FLASH     0x0000
#  define IDF_VER                               0
#  define CONFIG_FREERTOS_UNICORE               1
#  define CONFIG_BOOTLOADER_FLASH_XMC_SUPPORT   1
#endif

/* List of deprecated options */
#define CONFIG_BROWNOUT_DET CONFIG_ESP_BROWNOUT_DET
#define CONFIG_BROWNOUT_DET_LVL CONFIG_ESP_BROWNOUT_DET_LVL
#define CONFIG_BROWNOUT_DET_LVL_SEL_7 CONFIG_ESP_BROWNOUT_DET_LVL_SEL_7
#define CONFIG_COMPILER_OPTIMIZATION_LEVEL_DEBUG CONFIG_COMPILER_OPTIMIZATION_DEFAULT
#define CONFIG_CONSOLE_UART CONFIG_ESP_CONSOLE_UART
#define CONFIG_CONSOLE_UART_BAUDRATE CONFIG_ESP_CONSOLE_UART_BAUDRATE
#define CONFIG_CONSOLE_UART_DEFAULT CONFIG_ESP_CONSOLE_UART_DEFAULT
#define CONFIG_CONSOLE_UART_NUM CONFIG_ESP_CONSOLE_UART_NUM
#define CONFIG_ESP32_APPTRACE_DEST_NONE CONFIG_APPTRACE_DEST_NONE
#define CONFIG_ESP32_APPTRACE_LOCK_ENABLE CONFIG_APPTRACE_LOCK_ENABLE
#define CONFIG_ESP32_ENABLE_COREDUMP_TO_NONE CONFIG_ESP_COREDUMP_ENABLE_TO_NONE
#define CONFIG_ESP32_PHY_CALIBRATION_AND_DATA_STORAGE CONFIG_ESP_PHY_CALIBRATION_AND_DATA_STORAGE
#define CONFIG_ESP32_PHY_MAX_TX_POWER CONFIG_ESP_PHY_MAX_TX_POWER
#define CONFIG_ESP32_PHY_MAX_WIFI_TX_POWER CONFIG_ESP_PHY_MAX_WIFI_TX_POWER
#define CONFIG_ESP32_PTHREAD_STACK_MIN CONFIG_PTHREAD_STACK_MIN
#define CONFIG_ESP32_PTHREAD_TASK_CORE_DEFAULT CONFIG_PTHREAD_TASK_CORE_DEFAULT
#define CONFIG_ESP32_PTHREAD_TASK_NAME_DEFAULT CONFIG_PTHREAD_TASK_NAME_DEFAULT
#define CONFIG_ESP32_PTHREAD_TASK_PRIO_DEFAULT CONFIG_PTHREAD_TASK_PRIO_DEFAULT
#define CONFIG_ESP32_PTHREAD_TASK_STACK_SIZE_DEFAULT CONFIG_PTHREAD_TASK_STACK_SIZE_DEFAULT
#define CONFIG_ESP32_WIFI_AMPDU_RX_ENABLED CONFIG_ESP_WIFI_AMPDU_RX_ENABLED
#define CONFIG_ESP32_WIFI_AMPDU_TX_ENABLED CONFIG_ESP_WIFI_AMPDU_TX_ENABLED
#define CONFIG_ESP32_WIFI_DYNAMIC_RX_BUFFER_NUM CONFIG_ESP_WIFI_DYNAMIC_RX_BUFFER_NUM
#define CONFIG_ESP32_WIFI_DYNAMIC_TX_BUFFER CONFIG_ESP_WIFI_DYNAMIC_TX_BUFFER
#define CONFIG_ESP32_WIFI_DYNAMIC_TX_BUFFER_NUM CONFIG_ESP_WIFI_DYNAMIC_TX_BUFFER_NUM
#define CONFIG_ESP32_WIFI_ENABLED CONFIG_ESP_WIFI_ENABLED
#define CONFIG_ESP32_WIFI_ENABLE_WPA3_OWE_STA CONFIG_ESP_WIFI_ENABLE_WPA3_OWE_STA
#define CONFIG_ESP32_WIFI_ENABLE_WPA3_SAE CONFIG_ESP_WIFI_ENABLE_WPA3_SAE
#define CONFIG_ESP32_WIFI_IRAM_OPT CONFIG_ESP_WIFI_IRAM_OPT
#define CONFIG_ESP32_WIFI_MGMT_SBUF_NUM CONFIG_ESP_WIFI_MGMT_SBUF_NUM
#define CONFIG_ESP32_WIFI_NVS_ENABLED CONFIG_ESP_WIFI_NVS_ENABLED
#define CONFIG_ESP32_WIFI_RX_BA_WIN CONFIG_ESP_WIFI_RX_BA_WIN
#define CONFIG_ESP32_WIFI_RX_IRAM_OPT CONFIG_ESP_WIFI_RX_IRAM_OPT
#define CONFIG_ESP32_WIFI_SOFTAP_BEACON_MAX_LEN CONFIG_ESP_WIFI_SOFTAP_BEACON_MAX_LEN
#define CONFIG_ESP32_WIFI_STATIC_RX_BUFFER_NUM CONFIG_ESP_WIFI_STATIC_RX_BUFFER_NUM
#define CONFIG_ESP32_WIFI_SW_COEXIST_ENABLE CONFIG_ESP_COEX_SW_COEXIST_ENABLE
#define CONFIG_ESP32_WIFI_TX_BA_WIN CONFIG_ESP_WIFI_TX_BA_WIN
#define CONFIG_ESP32_WIFI_TX_BUFFER_TYPE CONFIG_ESP_WIFI_TX_BUFFER_TYPE
#define CONFIG_ESP_GRATUITOUS_ARP CONFIG_LWIP_ESP_GRATUITOUS_ARP
#define CONFIG_ESP_SYSTEM_PM_POWER_DOWN_CPU CONFIG_PM_POWER_DOWN_CPU_IN_LIGHT_SLEEP
#define CONFIG_ESP_TASK_WDT CONFIG_ESP_TASK_WDT_INIT
#define CONFIG_ESP_WIFI_SW_COEXIST_ENABLE CONFIG_ESP_COEX_SW_COEXIST_ENABLE
#define CONFIG_FLASHMODE_DIO CONFIG_ESPTOOLPY_FLASHMODE_DIO
#define CONFIG_GARP_TMR_INTERVAL CONFIG_LWIP_GARP_TMR_INTERVAL
#define CONFIG_INT_WDT CONFIG_ESP_INT_WDT
#define CONFIG_INT_WDT_TIMEOUT_MS CONFIG_ESP_INT_WDT_TIMEOUT_MS
#define CONFIG_IPC_TASK_STACK_SIZE CONFIG_ESP_IPC_TASK_STACK_SIZE
#define CONFIG_LOG_BOOTLOADER_LEVEL CONFIG_BOOTLOADER_LOG_LEVEL
#define CONFIG_LOG_BOOTLOADER_LEVEL_INFO CONFIG_BOOTLOADER_LOG_LEVEL_INFO
#define CONFIG_MAIN_TASK_STACK_SIZE CONFIG_ESP_MAIN_TASK_STACK_SIZE
#define CONFIG_MONITOR_BAUD CONFIG_ESPTOOLPY_MONITOR_BAUD
#define CONFIG_OPTIMIZATION_ASSERTIONS_ENABLED CONFIG_COMPILER_OPTIMIZATION_ASSERTIONS_ENABLE
#define CONFIG_OPTIMIZATION_ASSERTION_LEVEL CONFIG_COMPILER_OPTIMIZATION_ASSERTION_LEVEL
#define CONFIG_OPTIMIZATION_LEVEL_DEBUG CONFIG_COMPILER_OPTIMIZATION_DEFAULT
#define CONFIG_POST_EVENTS_FROM_IRAM_ISR CONFIG_ESP_EVENT_POST_FROM_IRAM_ISR
#define CONFIG_POST_EVENTS_FROM_ISR CONFIG_ESP_EVENT_POST_FROM_ISR
#define CONFIG_SEMIHOSTFS_MAX_MOUNT_POINTS CONFIG_VFS_SEMIHOSTFS_MAX_MOUNT_POINTS
#define CONFIG_SPI_FLASH_WRITING_DANGEROUS_REGIONS_ABORTS CONFIG_SPI_FLASH_DANGEROUS_WRITE_ABORTS
#define CONFIG_STACK_CHECK_NONE CONFIG_COMPILER_STACK_CHECK_MODE_NONE
#define CONFIG_SUPPORT_TERMIOS CONFIG_VFS_SUPPORT_TERMIOS
#define CONFIG_SUPPRESS_SELECT_DEBUG_OUTPUT CONFIG_VFS_SUPPRESS_SELECT_DEBUG_OUTPUT
#define CONFIG_SW_COEXIST_ENABLE CONFIG_ESP_COEX_SW_COEXIST_ENABLE
#define CONFIG_SYSTEM_EVENT_QUEUE_SIZE CONFIG_ESP_SYSTEM_EVENT_QUEUE_SIZE
#define CONFIG_SYSTEM_EVENT_TASK_STACK_SIZE CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE
#define CONFIG_TASK_WDT CONFIG_ESP_TASK_WDT_INIT
#define CONFIG_TASK_WDT_CHECK_IDLE_TASK_CPU0 CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
#define CONFIG_TASK_WDT_TIMEOUT_S CONFIG_ESP_TASK_WDT_TIMEOUT_S
#define CONFIG_TCPIP_RECVMBOX_SIZE CONFIG_LWIP_TCPIP_RECVMBOX_SIZE
#define CONFIG_TCPIP_TASK_AFFINITY CONFIG_LWIP_TCPIP_TASK_AFFINITY
#define CONFIG_TCPIP_TASK_AFFINITY_NO_AFFINITY CONFIG_LWIP_TCPIP_TASK_AFFINITY_NO_AFFINITY
#define CONFIG_TCPIP_TASK_STACK_SIZE CONFIG_LWIP_TCPIP_TASK_STACK_SIZE
#define CONFIG_TCP_MAXRTX CONFIG_LWIP_TCP_MAXRTX
#define CONFIG_TCP_MSL CONFIG_LWIP_TCP_MSL
#define CONFIG_TCP_MSS CONFIG_LWIP_TCP_MSS
#define CONFIG_TCP_OVERSIZE_MSS CONFIG_LWIP_TCP_OVERSIZE_MSS
#define CONFIG_TCP_QUEUE_OOSEQ CONFIG_LWIP_TCP_QUEUE_OOSEQ
#define CONFIG_TCP_RECVMBOX_SIZE CONFIG_LWIP_TCP_RECVMBOX_SIZE
#define CONFIG_TCP_SND_BUF_DEFAULT CONFIG_LWIP_TCP_SND_BUF_DEFAULT
#define CONFIG_TCP_SYNMAXRTX CONFIG_LWIP_TCP_SYNMAXRTX
#define CONFIG_TCP_WND_DEFAULT CONFIG_LWIP_TCP_WND_DEFAULT
#define CONFIG_TIMER_QUEUE_LENGTH CONFIG_FREERTOS_TIMER_QUEUE_LENGTH
#define CONFIG_TIMER_TASK_PRIORITY CONFIG_FREERTOS_TIMER_TASK_PRIORITY
#define CONFIG_TIMER_TASK_STACK_DEPTH CONFIG_FREERTOS_TIMER_TASK_STACK_DEPTH
#define CONFIG_TIMER_TASK_STACK_SIZE CONFIG_ESP_TIMER_TASK_STACK_SIZE
#define CONFIG_UDP_RECVMBOX_SIZE CONFIG_LWIP_UDP_RECVMBOX_SIZE
#define CONFIG_WPA_MBEDTLS_CRYPTO CONFIG_ESP_WIFI_MBEDTLS_CRYPTO
#define CONFIG_WPA_MBEDTLS_TLS_CLIENT CONFIG_ESP_WIFI_MBEDTLS_TLS_CLIENT
