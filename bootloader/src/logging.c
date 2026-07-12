#include "logging.h"

void logging_banner(BOOTLOADER_CONTEXT *context) {
    if (context == NULL || context->system_table == NULL) {
        return;
    }
    AsciiPrint("Aegis Bootloader\n\r");
    AsciiPrint("UEFI initialized successfully.\n\r");
}

void logging_firmware_info(BOOTLOADER_CONTEXT *context) {
    UINTN major;
    UINTN minor;

    if (context == NULL || context->system_table == NULL) {
        return;
    }

    major = context->system_table->FirmwareRevision >> 16;
    minor = context->system_table->FirmwareRevision & 0xFFFF;
    AsciiPrint("Firmware Vendor: %a\n\r", context->system_table->FirmwareVendor);
    AsciiPrint("UEFI Revision: %u.%02u\n\r", major, minor);
}
