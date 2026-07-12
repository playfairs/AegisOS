ROOT := ..
BUILD_DIR := ../build/bootloader
TARGET := ../BOOTX64.EFI
SOURCES := \
	src/main.c \
	src/boot.c \
	src/console.c \
	src/logging.c \
	src/memory.c \
	src/filesystem.c \
	src/graphics.c \
	src/elf_loader.c \
	src/acpi.c \
	src/config.c \
	src/efilib.c
OBJECTS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
CC ?= $(shell if command -v ld.lld >/dev/null 2>&1 || command -v lld >/dev/null 2>&1; then command -v clang 2>/dev/null || echo cc; elif command -v nix >/dev/null 2>&1; then echo 'nix shell nixpkgs#clang nixpkgs#lld --command clang'; else command -v clang 2>/dev/null || echo cc; fi)
CFLAGS ?= -O2 -g
CPPFLAGS += -Iinclude
COMMON_CFLAGS := -Wall -Wextra -target x86_64-unknown-uefi -ffreestanding -fno-builtin -fno-stack-protector -fshort-wchar -m64 -c
LDFLAGS := -target x86_64-unknown-uefi -fuse-ld=lld -nostdlib -Wl,-subsystem:efi_application -Wl,-entry:efi_main

.PHONY: all clean

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(COMMON_CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
