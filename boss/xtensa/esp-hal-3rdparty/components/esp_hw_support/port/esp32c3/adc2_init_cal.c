/*
 * SPDX-FileCopyrightText: 2016-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* This file is used to get `adc2_init_code_calibration` executed before the APP when the ADC2 is used by Wi-Fi or other drivers.
The linker will link constructor (adc2_init_code_calibration) only when any sections inside the same file (adc2_cal_include) is used.
Don't put any other code into this file. */

#ifdef __NuttX__
#include <nuttx/spinlock.h>
#else
#include "freertos/FreeRTOS.h"
#endif
#include "hal/adc_types.h"
#include "hal/adc_hal_common.h"
#include "esp_private/adc_share_hw_ctrl.h"

#ifdef __NuttX__
#define ENTER_CRITICAL_SECTION(lock) do { \
            assert(g_flags == UINT32_MAX); \
            g_flags = spin_lock_irqsave(lock); \
        } while(0)
#define LEAVE_CRITICAL_SECTION(lock) do { \
            spin_unlock_irqrestore((lock), g_flags); \
            g_flags = UINT32_MAX; \
        } while(0)

static irqstate_t g_flags = UINT32_MAX;
extern spinlock_t rtc_spinlock;
#else
#define ENTER_CRITICAL_SECTION(lock)    portENTER_CRITICAL_SAFE(lock)
#define LEAVE_CRITICAL_SECTION(lock)    portEXIT_CRITICAL_SAFE(lock)

extern portMUX_TYPE rtc_spinlock;
#endif

/**
 * @brief Set initial code to ADC2 after calibration. ADC2 RTC and ADC2 PWDET controller share the initial code.
 *        This API be called in before `app_main()`.
 */
static __attribute__((constructor)) void adc2_init_code_calibration(void)
{
    adc_hal_calibration_init(ADC_UNIT_2);
    adc_calc_hw_calibration_code(ADC_UNIT_2, ADC_ATTEN_DB_12);
    ENTER_CRITICAL_SECTION(&rtc_spinlock);
    adc_set_hw_calibration_code(ADC_UNIT_2, ADC_ATTEN_DB_12);
    LEAVE_CRITICAL_SECTION(&rtc_spinlock);
}

/** Don't call `adc2_cal_include` in user code. */
void adc2_cal_include(void)
{
    /* When this empty function is called, the `adc2_init_code_calibration` constructor will be linked and executed before the app.*/
}
