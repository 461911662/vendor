SECURE_BOOT_KEY_DEF_PATH := $(TOPDIR)$(DELIM)vendor$(DELIM)boss$(DELIM)boards$(DELIM)xtensa$(DELIM)esp32s3$(DELIM)tools$(DELIM)secure_boot_sign_key

ifeq ($(CONFIG_ESP32S3_APP_FORMAT_MCUBOOT),y)
# bootloader cfg
	BL_OFFSET       := 0x0000
	ifeq ($(CONFIG_ESP32S3_SECURE_BOOT),y)
		BOOTLOADER 	:= mcuboot-esp32s3.signed.bin
	else
		BOOTLOADER  := mcuboot-esp32s3.bin
	endif
	FLASH_BL        := $(BL_OFFSET) $(BOOTLOADER)
	ESPTOOL_BINS    := $(FLASH_BL)

# app cfg
	ifeq ($(CONFIG_ESP32S3_ESPTOOL_TARGET_PRIMARY),y)
		VERIFIED          := --confirm
		APP_OFFSET        := $(CONFIG_ESP32S3_OTA_PRIMARY_SLOT_OFFSET)
	else ifeq ($(CONFIG_ESP32S3_ESPTOOL_TARGET_SECONDARY),y)
		VERIFIED          :=
		APP_OFFSET        := $(CONFIG_ESP32S3_OTA_SECONDARY_SLOT_OFFSET)
	endif
	APP_IMAGE             := nuttx.bin
	FLASH_APP             := $(APP_OFFSET) $(APP_IMAGE)
	IMGTOOL_ALIGN_ARGS    := --align 4
	ifeq ($(CONFIG_ESP32S3_SECURE_BOOT),y)
		IMGTOOL_SIGN_ARGS := -k $(SECURE_BOOT_KEY_DEF_PATH)$(DELIM)$(subst ",,$(CONFIG_ESP32S3_SECURE_BOOT_APP_SIGNING_KEY))
	else
		IMGTOOL_SIGN_ARGS :=
	endif
	IMGTOOL_SIGN_ARGS  += --pad $(VERIFIED) $(IMGTOOL_ALIGN_ARGS) -v 0 -s auto \
		-H $(CONFIG_ESP32S3_APP_MCUBOOT_HEADER_SIZE) --pad-header \
		-S $(CONFIG_ESP32S3_OTA_SLOT_SIZE)
endif

ESPTOOL_BINS += $(FLASH_APP)

ifeq ($(CONFIG_ESP32S3_SECURE_BOOT),y)
ESPTOOL_FLASH_OPTS := -fs keep -fm keep -ff keep
endif

# PREBUILD -- Perform pre build operations
ifeq ($(CONFIG_BUILD_PROTECTED),y)
define PREBUILD
	$(Q) echo "CONFIG_NUTTX_USERSPACE=$(shell printf "%#x\n" $$(( 0x3c000030 + $(CONFIG_ESP32S3_KERNEL_IMAGE_SIZE) )))" > $(1)/.config.tmp
	$(Q) kconfig-merge -m $(1)/.config $(1)/.config.tmp
	$(Q)rm -f $(1)/.config.tmp
endef
else
define PREBUILD
	$(Q) echo "PREBUILD"
endef
endif

# POSTBUILD -- Perform post build operations
define POSTBUILD
	$(Q) echo "POSTBUILD"
	$(call MKIMAGE)
	$(if $(CONFIG_ESP32S3_MERGE_BINS),$(call MERGEBIN))
endef

