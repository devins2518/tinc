#include "token.h"

error error_new(int start, int end, const char *msg) {
    error e;
    e.span_start = start;
    e.span_end = end;
    e.msg = msg;
    return e;
}
