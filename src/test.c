#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

#define FILE_PATH_SIZE 256

int main(int argc, char **argv)
{
    if (argc < 1)
    {
        printf("No Test Cases Given\n");
    }

    char file_path[FILE_PATH_SIZE];
    strcpy(file_path, argv[0]);
    size_t init_path_len = strlen(argv[0]);

    char *file = "t1-1a.p";
    strcat(file_path, file);
    int result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "t1-1b.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "t1-2.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "t1-3.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "t1-4.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "t1-5.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "t2-2.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "t2-3.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "t3-3.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "t3-4.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "t4-1.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "t5-2.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "t5-3.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "t5-4.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "t6-1.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "t6-2.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));

    file = "test-semantic.p";
    strcat(file_path, file);
    result = parse(file_path);
    memset(file_path + init_path_len, 0, strlen(file));
}
