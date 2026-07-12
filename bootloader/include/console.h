#ifndef CONSOLE_H
#define CONSOLE_H

#include "bootloader.h"

void console_clear(BOOTLOADER_CONTEXT *context);
void console_write(BOOTLOADER_CONTEXT *context, const CHAR16 *text);
void console_wait_for_key(BOOTLOADER_CONTEXT *context);

#endif
