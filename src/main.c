#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc > 1) {
        parse_file(argv[1]);
        return EXIT_FAILURE;
    } else
        printf("Please specify file\n");
}
