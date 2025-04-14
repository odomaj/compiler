#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "scope.h"
#include "parser.h"

#define FILE_PATH_SIZE 256

int test_file(const char *file, int expect_out, char *path, size_t init_path_len)
{
    fprintf(stderr, "Testing %s\n", file);
    strcat(path, file);
    syntax_tree_t *syntax_tree;
    scope_t *symbol_table;
    int result = parse(path, &syntax_tree, &symbol_table);
    (void)free_tree(syntax_tree);
    (void)free_scope(symbol_table);
    if (result == expect_out)
        fprintf(stderr, "\tPassed\n");
    else
        fprintf(stderr, "\tFailed\n");
    memset(path + init_path_len, 0, strlen(file));
    return result == expect_out;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "No Test Cases Given\n");
        exit(1);
    }

    char file_path[FILE_PATH_SIZE];
    strcpy(file_path, argv[1]);
    size_t init_path_len = strlen(argv[1]);

    int total_passed = 0;
    int total_tests = 0;

    char *file = "t1-1a.p";
    total_passed += test_file(file, 1, file_path, init_path_len);
    total_tests++;

    file = "t1-1b.p";
    total_passed += test_file(file, 1, file_path, init_path_len);
    total_tests++;

    file = "t1-2.p";
    total_passed += test_file(file, 0, file_path, init_path_len);
    total_tests++;

    file = "t1-3.p";
    total_passed += test_file(file, 0, file_path, init_path_len);
    total_tests++;

    file = "t1-4.p";
    total_passed += test_file(file, 0, file_path, init_path_len);
    total_tests++;

    file = "t1-5.p";
    total_passed += test_file(file, 1, file_path, init_path_len);
    total_tests++;

    file = "t2-2.p";
    total_passed += test_file(file, 1, file_path, init_path_len);
    total_tests++;

    file = "t2-3.p";
    total_passed += test_file(file, 1, file_path, init_path_len);
    total_tests++;

    file = "t3-2.p";
    total_passed += test_file(file, 0, file_path, init_path_len);
    total_tests++;

    file = "t3-3.p";
    total_passed += test_file(file, 0, file_path, init_path_len);
    total_tests++;

    file = "t3-4.p";
    total_passed += test_file(file, 1, file_path, init_path_len);
    total_tests++;

    file = "t4-1.p";
    total_passed += test_file(file, 1, file_path, init_path_len);
    total_tests++;

    file = "t5-2.p";
    total_passed += test_file(file, 1, file_path, init_path_len);
    total_tests++;

    file = "t5-3.p";
    total_passed += test_file(file, 1, file_path, init_path_len);
    total_tests++;

    file = "t5-4.p";
    total_passed += test_file(file, 1, file_path, init_path_len);
    total_tests++;

    file = "t6-1.p";
    total_passed += test_file(file, 1, file_path, init_path_len);
    total_tests++;

    file = "t6-2.p";
    total_passed += test_file(file, 1, file_path, init_path_len);
    total_tests++;

    fprintf(stderr, "Passed %d/%d Tests", total_passed, total_tests);
}
