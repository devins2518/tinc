#include "lexer.h"
#include "scanner.h"
#include <stdio.h>

void parse_file(char *path) {
    int length;
    token *tokens = scan_file(path, &length);
    printf("unimplemented\n");
}
