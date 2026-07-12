ROOT := .
BOOTLOADER_DIR := bootloader
BOOTLOADER_IMAGE := $(ROOT)/BOOTX64.EFI
EFI_IMAGE := $(ROOT)/build/efi.img
OVMF_CODE ?= /usr/share/OVMF/OVMF_CODE.fd
OVMF_VARS ?= /usr/share/OVMF/OVMF_VARS.fd
QEMU ?= $(if $(strip $(QEMU_SYSTEM_X86_64)),$(QEMU_SYSTEM_X86_64),qemu-system-x86_64)
MKFS_FAT ?= mkfs.fat
MTOOLS_BIN ?= $(if $(strip $(MTOOLS)),$(MTOOLS),/usr/bin)

.PHONY: all build run clean

all: build

build:
	$(MAKE) -C $(BOOTLOADER_DIR) all
	mkdir -p $(ROOT)/build
	@if command -v $(MKFS_FAT) >/dev/null 2>&1 && command -v $(MTOOLS_BIN)/mcopy >/dev/null 2>&1; then \
		$(MKFS_FAT) -F32 -n AEGIS $(EFI_IMAGE) >/dev/null 2>&1 || true; \
		mkdir -p $(ROOT)/build/esp; \
		$(MTOOLS_BIN)/mmd -i $(EFI_IMAGE) ::/EFI >/dev/null 2>&1 || true; \
		$(MTOOLS_BIN)/mmd -i $(EFI_IMAGE) ::/EFI/BOOT >/dev/null 2>&1 || true; \
		$(MTOOLS_BIN)/mcopy -i $(EFI_IMAGE) $(BOOTLOADER_IMAGE) ::/EFI/BOOT/BOOTX64.EFI >/dev/null 2>&1 || true; \
	else \
		echo "Skipping EFI image packaging: mkfs.fat/mcopy unavailable in this environment."; \
	fi

run: build
	$(QEMU) -m 256 -cpu qemu64 -drive if=pflash,format=raw,readonly=on,file=$(OVMF_CODE) -drive if=pflash,format=raw,file=$(OVMF_VARS) -drive if=ide,format=raw,file=$(EFI_IMAGE) -serial stdio -display none -no-reboot -no-shutdown

clean:
	$(MAKE) -C $(BOOTLOADER_DIR) clean
	rm -f $(BOOTLOADER_IMAGE) $(EFI_IMAGE)
	rm -rf $(ROOT)/build/esp
