#ifndef COMPILER_SCANNER_SCANNER_H
#define COMPILER_SCANNER_SCANNER_H

#include "utils.h"
#include <stdint.h>

uint8_t scan_file(const char *src_file_path, token_list_t *dest);

#endif
