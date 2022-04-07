#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

typedef struct {
    enum {
        start_state,
        ident_state,
        string_lit_state,
        wide_string_lit_state,
        number_state,
        star_state,
        eq_state,
        hash_state,
        period_state,
        plus_state,
        minus_state,
        lt_state,
        gt_state,
        and_state,
        div_state,
        percent_state,
        bang_state,
        xor_state,
        or_state,
        shiftl_state,
        shiftr_state,
        comment_state
    } state;
    string *src;
    unsigned int curr;  /* start of the in progress scan */
    unsigned int index; /* current index of the scan */
    unsigned int line;
} scanner;
scanner scanner_new(string *src);
pp_token scanner_next(scanner *s);
pp_token scanner_skip_ws(scanner *s);

#endif
