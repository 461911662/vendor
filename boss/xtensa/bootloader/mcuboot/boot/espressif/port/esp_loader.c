/*
 * SPDX-FileCopyrightText: 2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include <bootutil/bootutil_log.h>
#include <bootutil/fault_injection_hardening.h>

#include "bootloader_memory_utils.h"
#include "bootloader_flash_priv.h"
#include "esp_flash_encrypt.h"

#include "rom/uart.h"
#include "rom/cache.h"

#include "hal/mmu_hal.h"
#include "hal/cache_ll.h"

#include "esp_mcuboot_image.h"
#include "esp_loader.h"
#include "flash_map_backend/flash_map_backend.h"

#ifdef CONFIG_ESP_MULTI_PROCESSOR_BOOT
#include "app_cpu_start.h"
#endif

static int load_segment(const struct flash_area *fap, uint32_t data_addr, uint32_t data_len, uint32_t load_addr)
{
    const uint32_t *data = (const uint32_t *)bootloader_mmap((fap->fa_off + data_addr), data_len);
    if (!data) {
        BOOT_LOG_ERR("%s: Bootloader mmap failed", __func__);
        return -1;
    }
    memcpy((void *)load_addr, data, data_len);
    bootloader_munmap(data);
    return 0;
}

static void load_common_image(const struct flash_area *fap, unsigned int hdr_offset, unsigned int *entry_addr)
{
    const uint32_t *data = (const uint32_t *)bootloader_mmap((fap->fa_off + hdr_offset), sizeof(esp_image_load_header_t));
    esp_image_load_header_t load_header = {0};
    memcpy((void *)&load_header, data, sizeof(esp_image_load_header_t));
    bootloader_munmap(data);

    if (load_header.header_magic != ESP_LOAD_HEADER_MAGIC) {
        BOOT_LOG_ERR("Load header magic verification failed. Aborting");
        return;
    }

    if (!esp_ptr_in_iram((void *)load_header.iram_dest_addr) || !esp_ptr_in_iram((void *)(load_header.iram_dest_addr + load_header.iram_size))) {
        BOOT_LOG_ERR("IRAM region in load header is not valid. Aborting");
        FIH_PANIC;
    }

    if (!esp_ptr_in_dram((void *)load_header.dram_dest_addr) || !esp_ptr_in_dram((void *)(load_header.dram_dest_addr + load_header.dram_size))) {
        BOOT_LOG_ERR("DRAM region in load header is not valid. Aborting");
        FIH_PANIC;
    }

    if (!esp_ptr_in_iram((void *)load_header.entry_addr)) {
        BOOT_LOG_ERR("Application entry point (0x%x) is not in IRAM. Aborting", load_header.entry_addr);
        FIH_PANIC;
    }

    BOOT_LOG_INF("DRAM segment: start=0x%x, size=0x%x, vaddr=0x%x", fap->fa_off + load_header.dram_flash_offset, load_header.dram_size, load_header.dram_dest_addr);
    load_segment(fap, load_header.dram_flash_offset, load_header.dram_size, load_header.dram_dest_addr);

    BOOT_LOG_INF("IRAM segment: start=0x%x, size=0x%x, vaddr=0x%x", fap->fa_off + load_header.iram_flash_offset, load_header.iram_size, load_header.iram_dest_addr);
    load_segment(fap, load_header.iram_flash_offset, load_header.iram_size, load_header.iram_dest_addr);

    BOOT_LOG_INF("start=0x%x", load_header.entry_addr);
    uart_tx_wait_idle(0);

    assert(entry_addr != NULL);
    *entry_addr = load_header.entry_addr;
}

static void load_boss_image(const struct flash_area *fap, unsigned int hdr_offset, unsigned int *entry_addr)
{
    const uint32_t boss_off = fap->fa_off + hdr_offset;
    const uint32_t *data = (const uint32_t *)bootloader_mmap(boss_off, sizeof(esp_boss_image_load_header_t));
    esp_boss_image_load_header_t load_header = {0};
    memcpy((void *)&load_header, data, sizeof(esp_boss_image_load_header_t));
    bootloader_munmap(data);

    if (load_header.magic != ESP_BOSS_LOAD_HEADER_MAGIC) {
        BOOT_LOG_ERR("Load header magic verification failed. Aborting(0x%x)", load_header.magic);
        FIH_PANIC;
    }

    /* copy data to DRAM */
    for (int count = 0; count < load_header.segment_count; ++count)
    {
        esp_boss_seg_info_t seg_info = {0};
        uint32_t off = boss_off + sizeof(esp_boss_image_load_header_t) + count * sizeof(esp_boss_seg_info_t);
        const uint32_t *seg_data = (const uint32_t *)bootloader_mmap(off, sizeof(esp_boss_seg_info_t));
        memcpy((void *)&seg_info, seg_data, sizeof(esp_boss_seg_info_t));
        bootloader_munmap(seg_data);

        if (!esp_ptr_in_iram((void *)seg_info.p_vaddr) && !esp_ptr_in_dram((void *)seg_info.p_vaddr)) {
            continue;
        }

        if (esp_ptr_in_iram((void *)seg_info.p_vaddr) && !esp_ptr_in_iram((void *)(seg_info.p_vaddr + seg_info.p_filesz))) {
            BOOT_LOG_ERR("IRAM region in load header is not valid. Aborting");
            FIH_PANIC;
        }

        if (esp_ptr_in_dram((void *)seg_info.p_vaddr) && !esp_ptr_in_dram((void *)(seg_info.p_vaddr + seg_info.p_filesz))) {
            BOOT_LOG_ERR("DRAM region in load header is not valid. Aborting");
            FIH_PANIC;
        }

        BOOT_LOG_INF("RAM segment: start=0x%x, size=0x%x, vaddr=0x%x", seg_info.offset, seg_info.p_filesz, seg_info.p_vaddr);
        off =  boss_off + seg_info.offset;
        load_segment(fap, off - fap->fa_off, seg_info.p_filesz, seg_info.p_vaddr);
        if (seg_info.p_vaddr != 0x40080000 && seg_info.p_vaddr != 0x40090000)
        {
            uint32_t start_addr = seg_info.p_vaddr;
            uint32_t end_addr = seg_info.p_vaddr + 0x100;
            for(; start_addr < end_addr; start_addr += 0x10)
            {
                ets_printf("%02x%02x", *((uint8_t *)(start_addr+0)), *((uint8_t *)(start_addr+1)));
                ets_printf(" %02x%02x", *((uint8_t *)(start_addr+2)), *((uint8_t *)(start_addr+3)));
                ets_printf(" %02x%02x", *((uint8_t *)(start_addr+4)), *((uint8_t *)(start_addr+5)));
                ets_printf(" %02x%02x", *((uint8_t *)(start_addr+6)), *((uint8_t *)(start_addr+7)));
                ets_printf(" %02x%02x", *((uint8_t *)(start_addr+8)), *((uint8_t *)(start_addr+9)));
                ets_printf(" %02x%02x", *((uint8_t *)(start_addr+10)), *((uint8_t *)(start_addr+11)));
                ets_printf(" %02x%02x", *((uint8_t *)(start_addr+12)), *((uint8_t *)(start_addr+13)));
                ets_printf(" %02x%02x\n", *((uint8_t *)(start_addr+14)), *((uint8_t *)(start_addr+15)));
            }
        }
    }

    /* map rom data */
    uint32_t drom_page_count = 0;
    uint32_t irom_page_count = 0;
    uint32_t drom_start_aligned = 0;
    uint32_t irom_start_aligned = 0;
    uint32_t drom_off_aligned = 0;
    uint32_t irom_off_aligned = 0;
    uint32_t drom_size = 0;
    uint32_t irom_size = 0;
    for (int count = 0; count < load_header.segment_count; ++count)
    {
        esp_boss_seg_info_t seg_info = {0};
        uint32_t off = boss_off + sizeof(esp_boss_image_load_header_t) + count * sizeof(esp_boss_seg_info_t);
        const uint32_t *seg_data = (const uint32_t *)bootloader_mmap(off, sizeof(esp_boss_seg_info_t));
        memcpy((void *)&seg_info, seg_data, sizeof(esp_boss_seg_info_t));
        bootloader_munmap(seg_data);

        if (esp_ptr_in_iram((void *)seg_info.p_vaddr) || esp_ptr_in_dram((void *)seg_info.p_vaddr)) {
            continue;
        }

        BOOT_LOG_INF("ROM segment: start=0x%x, size=0x%x, vaddr=0x%x", seg_info.offset, seg_info.p_filesz, seg_info.p_vaddr);

        if (seg_info.p_vaddr >= SOC_DROM_LOW && seg_info.p_vaddr < SOC_DROM_HIGH) {
            drom_start_aligned = seg_info.p_vaddr & MMU_FLASH_MASK;
            drom_page_count = (seg_info.p_filesz + SPI_FLASH_MMU_PAGE_SIZE - 1) /
                              SPI_FLASH_MMU_PAGE_SIZE;
            drom_off_aligned = (boss_off + seg_info.offset) & MMU_FLASH_MASK;
            drom_size = seg_info.p_filesz;
        } else if (seg_info.p_vaddr >= SOC_IROM_LOW && seg_info.p_vaddr < SOC_IROM_HIGH) {
            irom_start_aligned = seg_info.p_vaddr & MMU_FLASH_MASK;
            irom_page_count = (seg_info.p_filesz + SPI_FLASH_MMU_PAGE_SIZE - 1) /
                              SPI_FLASH_MMU_PAGE_SIZE;
            irom_off_aligned = (boss_off + seg_info.offset) & MMU_FLASH_MASK;
            irom_size = seg_info.p_filesz;
        }
    }

    /* Map flash memory to RAM */
    int ret = 0;
    cache_bus_mask_t bus_mask = 0;
    if (drom_size != 0 || irom_size != 0) {

        /* disable all external flash cache */
        Cache_Read_Disable(0);
        Cache_Flush(0);

        /* Clear the MMU entries that are already set up,
        * so the new app only has the mappings it creates.
        */
        mmu_hal_unmap_all();

        /* map drom */
        ret = cache_flash_mmu_set(0, 0, drom_start_aligned,
                                    drom_off_aligned, 64,
                                    (int)drom_page_count);
        /* ------------------Enable corresponding buses--------------------- */
        bus_mask = cache_ll_l1_get_bus(0, drom_start_aligned, drom_size);
        cache_ll_l1_enable_bus(0, bus_mask);
        BOOT_LOG_INF("DROM MAP: ret=%d, drom_start_aligned=0x%x, drom_page_count=%d(%d), offset:0x%x",
            ret, drom_start_aligned, drom_page_count, drom_size, drom_off_aligned);

        /* map irom */
        ret = cache_flash_mmu_set(0, 0, irom_start_aligned,
                                    irom_off_aligned, 64,
                                    (int)irom_page_count);
        /* ------------------Enable corresponding buses--------------------- */
        bus_mask = cache_ll_l1_get_bus(0, irom_start_aligned, irom_size);
        cache_ll_l1_enable_bus(0, bus_mask);
        BOOT_LOG_INF("IROM MAP: ret=%d, irom_start_aligned=0x%x, irom_page_count=%d(%d), offset:0x%x",
            ret, irom_start_aligned, irom_page_count, irom_size, irom_off_aligned);

        //-------------enable cache--------------
        Cache_Read_Enable(0);
    }

    BOOT_LOG_INF("start=0x%x", load_header.entry_point);
    uart_tx_wait_idle(0);

#if 0
    uint32_t start_addr = 0x3f400020;
    uint32_t end_addr = 0x3f400000 + 0x100;
    for(; start_addr < end_addr; start_addr += 0x10)
    {
        ets_printf("%02x%02x", *((uint8_t *)(start_addr+0)), *((uint8_t *)(start_addr+1)));
        ets_printf(" %02x%02x", *((uint8_t *)(start_addr+2)), *((uint8_t *)(start_addr+3)));
        ets_printf(" %02x%02x", *((uint8_t *)(start_addr+4)), *((uint8_t *)(start_addr+5)));
        ets_printf(" %02x%02x", *((uint8_t *)(start_addr+6)), *((uint8_t *)(start_addr+7)));
        ets_printf(" %02x%02x", *((uint8_t *)(start_addr+8)), *((uint8_t *)(start_addr+9)));
        ets_printf(" %02x%02x", *((uint8_t *)(start_addr+10)), *((uint8_t *)(start_addr+11)));
        ets_printf(" %02x%02x", *((uint8_t *)(start_addr+12)), *((uint8_t *)(start_addr+13)));
        ets_printf(" %02x%02x\n", *((uint8_t *)(start_addr+14)), *((uint8_t *)(start_addr+15)));
    }
#endif

    assert(entry_addr != NULL);
    *entry_addr = load_header.entry_point;
}

void esp_app_image_load(int image_index, int slot, unsigned int hdr_offset, unsigned int *entry_addr)
{
    const struct flash_area *fap;
    int area_id;
    int rc;

    area_id = flash_area_id_from_multi_image_slot(image_index, slot);
    rc = flash_area_open(area_id, &fap);
    if (rc != 0) {
        BOOT_LOG_ERR("%s: flash_area_open failed with %d", __func__, rc);
    }

    BOOT_LOG_INF("Loading image %d - slot %d from flash, area id: %d", image_index, slot, area_id);
    load_common_image(fap, hdr_offset, entry_addr);
    if (*entry_addr != 0xFFFFFFFF) {
        return;
    }

    load_boss_image(fap, hdr_offset, entry_addr);
}

void start_cpu0_image(int image_index, int slot, unsigned int hdr_offset)
{
    unsigned int entry_addr = 0xFFFFFFFF;
    esp_app_image_load(image_index, slot, hdr_offset, &entry_addr);
    ((void (*)(void))entry_addr)(); /* Call to application entry address should not return */
    FIH_PANIC; /* It should not get here */
}

#ifdef CONFIG_ESP_MULTI_PROCESSOR_BOOT
void start_cpu1_image(int image_index, int slot, unsigned int hdr_offset)
{
    unsigned int entry_addr;
    esp_app_image_load(image_index, slot, hdr_offset, &entry_addr);
    appcpu_start(entry_addr);
}
#endif
