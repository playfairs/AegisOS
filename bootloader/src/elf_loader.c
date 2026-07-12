#include "elf_loader.h"

void elf_loader_module_report(BOOTLOADER_CONTEXT *context) {
    if (context == NULL) {
        return;
    }
    Print(L"ELF loader module ready.\n\r");
}
