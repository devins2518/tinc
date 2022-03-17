#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc > 1) {
        compile_file(argv[1]);
        return EXIT_FAILURE;
    } else
        printf("Please specify file\n");
}
