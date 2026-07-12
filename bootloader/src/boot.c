#include "bootloader.h"
#include "console.h"
#include "logging.h"
#include "memory.h"
#include "filesystem.h"
#include "graphics.h"
#include "elf_loader.h"
#include "acpi.h"
#include "config.h"

EFI_STATUS bootloader_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table) {
    BOOTLOADER_CONTEXT context;
    EFI_STATUS status;

    context.image_handle = image_handle;
    context.system_table = system_table;
    InitializeLib(image_handle, system_table);

    console_clear(&context);
    logging_banner(&context);
    logging_firmware_info(&context);
    memory_module_report(&context);
    filesystem_module_report(&context);
    graphics_module_report(&context);
    elf_loader_module_report(&context);
    acpi_module_report(&context);
    config_module_report(&context);
    console_wait_for_key(&context);

    status = EFI_SUCCESS;
    return status;
}
