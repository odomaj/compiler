#ifndef COMPILER_SCANNER_SCANNER_H
#define COMPILER_SCANNER_SCANNER_H

#include "utils.h"
#include <stdint.h>
#include <stddef.h>

uint8_t scan_file(const char *src_file_path, token_list_t *dest);
token_t *token_buff(char *buff, size_t *index, uint8_t *prev_type);

#endif
