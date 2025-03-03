/*
 * SPDX-FileCopyrightText: 2019-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SUPPLICANT_OPT_H
#define _SUPPLICANT_OPT_H

#include "sdkconfig.h"

#ifdef __NuttX__
#ifdef CONFIG_WPA_DEBUG_PRINT
#define DEBUG_PRINT
#if defined(CONFIG_LOG_DEFAULT_LEVEL_DEBUG) || defined(CONFIG_LOG_DEFAULT_LEVEL_VERBOSE)
#define ELOOP_DEBUG
#endif
#endif
#else
#if CONFIG_WPA_DEBUG_PRINT
#define DEBUG_PRINT
#if defined(CONFIG_LOG_DEFAULT_LEVEL_DEBUG) || defined(CONFIG_LOG_DEFAULT_LEVEL_VERBOSE)
#define ELOOP_DEBUG
#endif
#endif
#endif

#if CONFIG_ESP_WIFI_SCAN_CACHE
#define SCAN_CACHE_SUPPORTED
#endif

#endif /* _SUPPLICANT_OPT_H */
