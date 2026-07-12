#include "acpi.h"

void acpi_module_report(BOOTLOADER_CONTEXT *context) {
    if (context == NULL) {
        return;
    }
    Print(L"ACPI module ready.\n\r");
}
