#include "efilib.h"

static EFI_SYSTEM_TABLE *gSystemTable;

void InitializeLib(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table) {
    (void)image_handle;
    gSystemTable = system_table;
}

static void output_char16_string(const CHAR16 *s) {
    if (gSystemTable == NULL || gSystemTable->ConOut == NULL || s == NULL) return;
    gSystemTable->ConOut->OutputString(gSystemTable->ConOut, (CHAR16 *)s);
}

static void output_ascii_string(const char *s) {
    if (gSystemTable == NULL || gSystemTable->ConOut == NULL || s == NULL) return;
    CHAR16 buf[256];
    unsigned i = 0;
    for (; *s && i + 1 < sizeof(buf)/sizeof(buf[0]); s++, i++) {
        buf[i] = (CHAR16)(unsigned char)(*s);
    }
    buf[i] = 0;
    gSystemTable->ConOut->OutputString(gSystemTable->ConOut, buf);
}

void Print(const CHAR16 *fmt, ...) {
    output_char16_string(fmt);
}

void AsciiPrint(const char *fmt, ...) {
    if (fmt == NULL) return;
    CHAR16 out[512];
    unsigned outi = 0;
    va_list ap;
    va_start(ap, fmt);
    for (const char *p = fmt; *p && outi + 3 < sizeof(out)/sizeof(out[0]); p++) {
        if (*p == '%' && *(p+1) != '\0') {
            p++;
            if (*p == 'a') {
                const char *s = va_arg(ap, const char *);
                if (s) {
                    for (; *s && outi + 1 < sizeof(out)/sizeof(out[0]); s++) {
                        out[outi++] = (CHAR16)(unsigned char)(*s);
                    }
                }
            } else if (*p == 'u') {
                unsigned val = va_arg(ap, unsigned);
                char digits[32];
                int di = 0;
                if (val == 0) digits[di++] = '0';
                while (val > 0 && di + 1 < (int)sizeof(digits)) {
                    digits[di++] = '0' + (val % 10);
                    val /= 10;
                }
                while (di > 0 && outi + 1 < sizeof(out)/sizeof(out[0])) {
                    out[outi++] = (CHAR16)digits[--di];
                }
            } else if (*p == '0' && *(p+1) == '2' && *(p+2) == 'u') {
                p += 2;
                unsigned val = va_arg(ap, unsigned);
                unsigned d1 = (val / 10) % 10;
                unsigned d0 = val % 10;
                out[outi++] = (CHAR16)('0' + d1);
                out[outi++] = (CHAR16)('0' + d0);
            } else {
                out[outi++] = (CHAR16)'%';
                out[outi++] = (CHAR16)*p;
            }
        } else {
            out[outi++] = (CHAR16)(unsigned char)(*p);
        }
    }
    out[outi] = 0;
    va_end(ap);
    output_char16_string(out);
}
