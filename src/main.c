#include <stdio.h>

#include "parser.h"
#include "scope.h"

int main(int argc, char **argv)
{
    fprintf(stderr, "%s\n ", argv[1]);
    parse(argv[1]);
    return 0;
}
