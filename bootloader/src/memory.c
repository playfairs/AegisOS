#include "memory.h"

void memory_module_report(BOOTLOADER_CONTEXT *context) {
    if (context == NULL) {
        return;
    }
    Print(L"Memory manager ready.\n\r");
}
