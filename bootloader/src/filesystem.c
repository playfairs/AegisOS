#include "filesystem.h"

void filesystem_module_report(BOOTLOADER_CONTEXT *context) {
    if (context == NULL) {
        return;
    }
    Print(L"Filesystem module ready.\n\r");
}
