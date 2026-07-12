#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <efi.h>
#include <efilib.h>

typedef struct {
    EFI_HANDLE image_handle;
    EFI_SYSTEM_TABLE *system_table;
} BOOTLOADER_CONTEXT;

EFI_STATUS bootloader_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table);

#endif
