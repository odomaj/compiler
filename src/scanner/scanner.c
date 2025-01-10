#include "scanner.h"
#include <stdio.h>

uint8_t scan_file(const char *src_file_path, token_list_t *dest)
{
    FILE *file = fopen(src_file_path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "unable to open file to scan: %s\n", src_file_path);
        return 1;
    }
    int c = 0;
    // TODO: save raw characters in dest
    while ((c = fgetc(file)) != EOF)
        fprintf(stdout, "%c", c);
    fclose(file);
    return 0;
}
