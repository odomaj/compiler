#ifndef COMPILER_PARSER_SCANNER_H
#define COMPILER_PARSER_SCANNER_H

#include "utils.h"
#include <stdint.h>
#include <stddef.h>

#define DEFAULT_BUFFER_SIZE 32

uint8_t open_scanner(const char *filepath);
void close_scanner(void);

uint8_t next_token(token_t *dest);
uint8_t token_type(char c, uint8_t previous_type);
uint8_t double_token(void);
uint8_t first_token(token_t *dest);

void load_op(token_t *dest);
void load_num(token_t *dest);

uint8_t resize_buffer(void);

#endif
