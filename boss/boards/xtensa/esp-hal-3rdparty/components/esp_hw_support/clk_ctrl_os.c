/*
 * SPDX-FileCopyrightText: 2020-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __NuttX__
#include <nuttx/spinlock.h>
#else
#include <freertos/FreeRTOS.h>
#endif

#include "clk_ctrl_os.h"
#include "soc/rtc.h"
#include "esp_private/esp_clk_tree_common.h"
#include "esp_check.h"

#ifdef __NuttX__
#define ENTER_CRITICAL_SECTION(lock) do { \
            assert(g_flags == UINT32_MAX); \
            g_flags = spin_lock_irqsave(lock); \
        } while(0)
#define LEAVE_CRITICAL_SECTION(lock) do { \
            spin_unlock_irqrestore((lock), g_flags); \
            g_flags = UINT32_MAX; \
        } while(0)
#define LOCK_INITIALIZER_UNLOCKED       0

typedef spinlock_t lock_type_t;
static irqstate_t g_flags = UINT32_MAX;
#else
#define ENTER_CRITICAL_SECTION(lock)    portENTER_CRITICAL_SAFE(lock)
#define LEAVE_CRITICAL_SECTION(lock)    portEXIT_CRITICAL_SAFE(lock)
#define LOCK_INITIALIZER_UNLOCKED       portMUX_INITIALIZER_UNLOCKED

typedef portMUX_TYPE lock_type_t;
#endif

static lock_type_t periph_spinlock = LOCK_INITIALIZER_UNLOCKED;

static uint8_t s_periph_ref_counts = 0;
static uint32_t s_rc_fast_freq = 0; // Frequency of the RC_FAST clock in Hz
#if SOC_CLK_APLL_SUPPORTED
static const char *TAG = "clk_ctrl_os";
// Current APLL frequency, in HZ. Zero if APLL is not enabled.
static uint32_t s_cur_apll_freq = 0;
static int s_apll_ref_cnt = 0;
#endif


bool periph_rtc_dig_clk8m_enable(void)
{
    ENTER_CRITICAL_SECTION(&periph_spinlock);
    if (s_periph_ref_counts == 0) {
        rtc_dig_clk8m_enable();
#if SOC_CLK_RC_FAST_SUPPORT_CALIBRATION
        s_rc_fast_freq = esp_clk_tree_rc_fast_get_freq_hz(ESP_CLK_TREE_SRC_FREQ_PRECISION_EXACT);
        if (s_rc_fast_freq == 0) {
            rtc_dig_clk8m_disable();
            LEAVE_CRITICAL_SECTION(&periph_spinlock);
            return false;
        }
#endif //SOC_CLK_RC_FAST_SUPPORT_CALIBRATION
    }
    s_periph_ref_counts++;
    LEAVE_CRITICAL_SECTION(&periph_spinlock);
    return true;
}

uint32_t periph_rtc_dig_clk8m_get_freq(void)
{
#if !SOC_CLK_RC_FAST_SUPPORT_CALIBRATION
    /* Workaround: CLK8M calibration cannot be performed, we can only return its theoretic value */
    return SOC_CLK_RC_FAST_FREQ_APPROX;
#else
    return s_rc_fast_freq;
#endif
}

void periph_rtc_dig_clk8m_disable(void)
{
    ENTER_CRITICAL_SECTION(&periph_spinlock);
    assert(s_periph_ref_counts > 0);
    s_periph_ref_counts--;
    if (s_periph_ref_counts == 0) {
        s_rc_fast_freq = 0;
        rtc_dig_clk8m_disable();
    }
    LEAVE_CRITICAL_SECTION(&periph_spinlock);
}

#if SOC_CLK_APLL_SUPPORTED
void periph_rtc_apll_acquire(void)
{
    ENTER_CRITICAL_SECTION(&periph_spinlock);
    s_apll_ref_cnt++;
    if (s_apll_ref_cnt == 1) {
        // For the first time enable APLL, need to set power up
        rtc_clk_apll_enable(true);
    }
    LEAVE_CRITICAL_SECTION(&periph_spinlock);
}

void periph_rtc_apll_release(void)
{
    ENTER_CRITICAL_SECTION(&periph_spinlock);
    assert(s_apll_ref_cnt > 0);
    s_apll_ref_cnt--;
    if (s_apll_ref_cnt == 0) {
        // If there is no peripheral using APLL, shut down the power
        s_cur_apll_freq = 0;
        rtc_clk_apll_enable(false);
    }
    LEAVE_CRITICAL_SECTION(&periph_spinlock);
}

esp_err_t periph_rtc_apll_freq_set(uint32_t expt_freq, uint32_t *real_freq)
{
    uint32_t o_div = 0;
    uint32_t sdm0 = 0;
    uint32_t sdm1 = 0;
    uint32_t sdm2 = 0;
    // Guarantee 'periph_rtc_apll_acquire' has been called before set apll freq
    assert(s_apll_ref_cnt > 0);
    uint32_t apll_freq = rtc_clk_apll_coeff_calc(expt_freq, &o_div, &sdm0, &sdm1, &sdm2);

    ESP_RETURN_ON_FALSE(apll_freq, ESP_ERR_INVALID_ARG, TAG, "APLL coefficients calculate failed");
    bool need_config = true;
    ENTER_CRITICAL_SECTION(&periph_spinlock);
    /* If APLL is not in use or only one peripheral in use, its frequency can be changed as will
     * But when more than one peripheral refers APLL, its frequency is not allowed to change once it is set */
    if (s_cur_apll_freq == 0 || s_apll_ref_cnt < 2) {
        s_cur_apll_freq = apll_freq;
    } else {
        apll_freq = s_cur_apll_freq;
        need_config = false;
    }
    LEAVE_CRITICAL_SECTION(&periph_spinlock);
    *real_freq = apll_freq;

    if (need_config) {
        ESP_LOGD(TAG, "APLL will working at %d Hz with coefficients [sdm0] %d [sdm1] %d [sdm2] %d [o_div] %d",
                       apll_freq, sdm0, sdm1, sdm2, o_div);
        /* Set coefficients for APLL, notice that it doesn't mean APLL will start */
        rtc_clk_apll_coeff_set(o_div, sdm0, sdm1, sdm2);
    } else {
        return ESP_ERR_INVALID_STATE;
    }

    return ESP_OK;
}
#endif // SOC_CLK_APLL_SUPPORTED
