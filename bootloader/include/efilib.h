#ifndef EFILIB_H
#define EFILIB_H

#include "efi.h"
#include <stdarg.h>

void InitializeLib(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table);
void Print(const CHAR16 *fmt, ...);
void AsciiPrint(const char *fmt, ...);

#endif
