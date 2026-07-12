#include "console.h"

void console_clear(BOOTLOADER_CONTEXT *context) {
    if (context == NULL || context->system_table == NULL || context->system_table->ConOut == NULL) {
        return;
    }
    context->system_table->ConOut->ClearScreen(context->system_table->ConOut);
}

void console_write(BOOTLOADER_CONTEXT *context, const CHAR16 *text) {
    if (context == NULL || context->system_table == NULL || context->system_table->ConOut == NULL) {
        return;
    }
    context->system_table->ConOut->OutputString(context->system_table->ConOut, (CHAR16 *)text);
}

void console_wait_for_key(BOOTLOADER_CONTEXT *context) {
    EFI_INPUT_KEY key;
    EFI_STATUS status;

    if (context == NULL || context->system_table == NULL || context->system_table->ConIn == NULL) {
        return;
    }

    do {
        status = context->system_table->ConIn->ReadKeyStroke(context->system_table->ConIn, &key);
    } while (status == EFI_NOT_READY);
}
