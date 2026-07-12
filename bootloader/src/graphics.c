#include "graphics.h"

void graphics_module_report(BOOTLOADER_CONTEXT *context) {
    if (context == NULL) {
        return;
    }
    Print(L"Graphics module ready.\n\r");
}
