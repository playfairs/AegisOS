#include "config.h"

void config_module_report(BOOTLOADER_CONTEXT *context) {
    if (context == NULL) {
        return;
    }
    Print(L"Configuration module ready.\n\r");
}
