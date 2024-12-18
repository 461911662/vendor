
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
endef
