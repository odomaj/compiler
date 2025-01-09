#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("expecting 2 args, input file and output file\n");
        return 1;
    }
    FILE *in = fopen(argv[1], "r");
    if (in == NULL)
    {
        printf("[ERROR] unable to open input file: %s\n", argv[1]);
        return 1;
    }
    FILE *out = fopen(argv[2], "w");
    if (out == NULL)
    {
        printf("[ERROR] unable to open output file: %s\n", argv[2]);
        return 1;
    }
    int c = 0;
    while ((c = fgetc(in)) != EOF)
        fprintf(out, "%c", c);
    fclose(in);
    fclose(out);
    return 0;
}
