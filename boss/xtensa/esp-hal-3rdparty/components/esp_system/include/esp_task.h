/*
 * SPDX-FileCopyrightText: 2019-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Notes:
 * 1. Put all task priority and stack size definition in this file
 * 2. If the task priority is less than 10, use ESP_TASK_PRIO_MIN + X style,
 *    otherwise use ESP_TASK_PRIO_MAX - X style
 * 3. If this is a daemon task, the macro prefix is ESP_TASKD_, otherwise
 *    it's ESP_TASK_
 * 4. If the configMAX_PRIORITIES is modified, please make all priority are
 *    greater than 0
 * 5. Make sure esp_task.h is consistent between wifi lib and idf
 * 6. If changing system task priorities, please check the values documented in /api-guides/performance/speed.rst
 * are up to date
 */

#ifndef _ESP_TASK_H_
#define _ESP_TASK_H_

#include "sdkconfig.h"
#ifndef __NuttX__
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#define ESP_TASK_PRIO_MAX (configMAX_PRIORITIES)
#define ESP_TASK_PRIO_MIN (0)
#else
#define ESP_TASK_PRIO_MAX (SCHED_PRIORITY_MAX)
#define ESP_TASK_PRIO_MIN (SCHED_PRIORITY_MIN)
#endif

/* Bt contoller Task */
/* controller */
#define ESP_TASK_BT_CONTROLLER_PRIO   (ESP_TASK_PRIO_MAX - 2)
#ifdef CONFIG_NEWLIB_NANO_FORMAT
#define TASK_EXTRA_STACK_SIZE      (0)
#else
#define TASK_EXTRA_STACK_SIZE      (512)
#endif

#define BT_TASK_EXTRA_STACK_SIZE      TASK_EXTRA_STACK_SIZE
#define ESP_TASK_BT_CONTROLLER_STACK  (3584 + TASK_EXTRA_STACK_SIZE)

/* Ping Task */
#define ESP_TASK_PING_STACK             (2048 + TASK_EXTRA_STACK_SIZE)


/* idf task */
#define ESP_TASK_TIMER_PRIO           (ESP_TASK_PRIO_MAX - 3)
#define ESP_TASK_TIMER_STACK          (CONFIG_ESP_TIMER_TASK_STACK_SIZE +  TASK_EXTRA_STACK_SIZE)
#define ESP_TASKD_EVENT_PRIO          (ESP_TASK_PRIO_MAX - 5)
#if CONFIG_LWIP_TCPIP_CORE_LOCKING
#define ESP_TASKD_EVENT_STACK         (CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE + TASK_EXTRA_STACK_SIZE + 2048)
#else
#define ESP_TASKD_EVENT_STACK         (CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE + TASK_EXTRA_STACK_SIZE)
#endif /* CONFIG_LWIP_TCPIP_CORE_LOCKING */
#define ESP_TASK_TCPIP_PRIO           (CONFIG_LWIP_TCPIP_TASK_PRIO)
#define ESP_TASK_TCPIP_STACK          (CONFIG_LWIP_TCPIP_TASK_STACK_SIZE + TASK_EXTRA_STACK_SIZE)
#define ESP_TASK_MAIN_PRIO            (ESP_TASK_PRIO_MIN + 1)
#define ESP_TASK_MAIN_STACK           (CONFIG_ESP_MAIN_TASK_STACK_SIZE + TASK_EXTRA_STACK_SIZE)
#define ESP_TASK_MAIN_CORE            CONFIG_ESP_MAIN_TASK_AFFINITY

#endif
