#include "bootloader.h"

EFI_STATUS efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table) {
    return bootloader_main(image_handle, system_table);
}

int main(void) {
    return 0;
}
