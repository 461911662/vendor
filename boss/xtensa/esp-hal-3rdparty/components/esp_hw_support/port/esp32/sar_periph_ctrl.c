/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * SAR related peripherals are interdependent. This file
 * provides a united control to these registers, as multiple
 * components require these controls.
 *
 * Related peripherals are:
 * - ADC
 * - PWDET
 */

#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_private/sar_periph_ctrl.h"
#include "hal/sar_ctrl_ll.h"

#ifdef __NuttX__
#include <nuttx/spinlock.h>
#else
#include "freertos/FreeRTOS.h"
#endif

#ifdef __NuttX__
#define ENTER_CRITICAL_SECTION(lock) do { \
            assert(g_flags == UINT32_MAX); \
            g_flags = spin_lock_irqsave(lock); \
        } while(0)
#define LEAVE_CRITICAL_SECTION(lock) do { \
            spin_unlock_irqrestore((lock), g_flags); \
            g_flags = UINT32_MAX; \
        } while(0)

static spinlock_t rtc_spinlock;
static irqstate_t g_flags = UINT32_MAX;
#else
#define ENTER_CRITICAL_SECTION(lock)    portENTER_CRITICAL_SAFE(lock)
#define LEAVE_CRITICAL_SECTION(lock)    portEXIT_CRITICAL_SAFE(lock)

extern portMUX_TYPE rtc_spinlock;
#endif

static const char *TAG = "sar_periph_ctrl";

void sar_periph_ctrl_init(void)
{
    //Put SAR control mux to ON state
    sar_ctrl_ll_set_power_mode(SAR_CTRL_LL_POWER_ON);

    //Add other periph power control initialisation here
}

void sar_periph_ctrl_power_enable(void)
{
    ENTER_CRITICAL_SECTION(&rtc_spinlock);
    sar_ctrl_ll_set_power_mode(SAR_CTRL_LL_POWER_ON);
    LEAVE_CRITICAL_SECTION(&rtc_spinlock);
}

void sar_periph_ctrl_power_disable(void)
{
    ENTER_CRITICAL_SECTION(&rtc_spinlock);
    sar_ctrl_ll_set_power_mode(SAR_CTRL_LL_POWER_OFF);
    LEAVE_CRITICAL_SECTION(&rtc_spinlock);
}

/**
 * This gets incremented when s_sar_power_acquire() is called,
 * and decremented when s_sar_power_release() is called.
 * PWDET is powered down when the value reaches zero.
 * Should be modified within critical section.
 */
static int s_sar_power_on_cnt;

static void s_sar_power_acquire(void)
{
    ENTER_CRITICAL_SECTION(&rtc_spinlock);
    s_sar_power_on_cnt++;
    if (s_sar_power_on_cnt == 1) {
        sar_ctrl_ll_set_power_mode(SAR_CTRL_LL_POWER_ON);
    }
    LEAVE_CRITICAL_SECTION(&rtc_spinlock);
}

static void s_sar_power_release(void)
{
    ENTER_CRITICAL_SECTION(&rtc_spinlock);
    s_sar_power_on_cnt--;
    if (s_sar_power_on_cnt < 0) {
        portEXIT_CRITICAL(&rtc_spinlock);
        ESP_LOGE(TAG, "%s called, but s_sar_power_on_cnt == 0", __func__);
        abort();
    } else if (s_sar_power_on_cnt == 0) {
        sar_ctrl_ll_set_power_mode(SAR_CTRL_LL_POWER_FSM);
    }
    LEAVE_CRITICAL_SECTION(&rtc_spinlock);
}


/*------------------------------------------------------------------------------
* PWDET Power
*----------------------------------------------------------------------------*/
void sar_periph_ctrl_pwdet_power_acquire(void)
{
    s_sar_power_acquire();
}

void sar_periph_ctrl_pwdet_power_release(void)
{
    s_sar_power_release();
}


/*------------------------------------------------------------------------------
* ADC Power
*----------------------------------------------------------------------------*/
void sar_periph_ctrl_adc_oneshot_power_acquire(void)
{
    s_sar_power_acquire();
}

void sar_periph_ctrl_adc_oneshot_power_release(void)
{
    s_sar_power_release();
}

void sar_periph_ctrl_adc_continuous_power_acquire(void)
{
    s_sar_power_acquire();
}

void sar_periph_ctrl_adc_continuous_power_release(void)
{
    s_sar_power_release();
}
