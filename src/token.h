#ifndef TOKEN_H
#define TOKEN_H

#include "string.h"

typedef enum {
    auto_kw,
    break_kw,
    case_kw,
    char_kw,
    const_kw,
    continue_kw,
    default_kw,
    do_kw,
    double_kw,
    else_kw,
    enum_kw,
    extern_kw,
    float_kw,
    for_kw,
    goto_kw,
    if_kw,
    int_kw,
    long_kw,
    register_kw,
    return_kw,
    short_kw,
    signed_kw,
    sizeof_kw,
    static_kw,
    struct_kw,
    switch_kw,
    typedef_kw,
    union_kw,
    unsigned_kw,
    void_kw,
    volatile_kw,
    while_kw
} keyword;

typedef string ident;

typedef enum { float_const, int_const, enum_const, char_const } constant;

typedef string string_lit;

typedef enum {
    lbracket_op,  /* [ */
    rbracket_op,  /* ] */
    lparen_op,    /* ( */
    rparen_op,    /* ) */
    period_op,    /* . */
    arrow_op,     /* -> */
    dblplus_op,   /* ++ */
    dblminus_op,  /* -- */
    logand_op,    /* & */
    star_op,      /* * */
    plus_op,      /* + */
    minus_op,     /* - */
    approx_op,    /* ~ */
    bang_op,      /* ! */
    sizeof_op,    /* sizeof */
    div_op,       /* / */
    percent_op,   /* % */
    shiftl_op,    /* << */
    shiftr_op,    /* >> */
    lt_op,        /* < */
    gt_op,        /* > */
    lteq_op,      /* <= */
    gteq_op,      /* >= */
    eqeq_op,      /* == */
    bangeq_op,    /* != */
    logxor_op,    /* ^ */
    logor_op,     /* | */
    dbland_op,    /* && */
    dblor_op,     /* || */
    ternaryq_op,  /* ? */
    ternaryc_op,  /* : */
    eq_op,        /* = */
    stareq_op,    /* *= */
    diveq_op,     /* /= */
    percenteq_op, /* %= */
    pluseq_op,    /* += */
    minuseq_op,   /* -= */
    shiftleq_op,  /* <<= */
    shiftreq_op,  /* >>= */
    andeq_op,     /* &= */
    xoreq_op,     /* ^= */
    oreq_op,      /* |= */
    comma_op,     /* , */
    hash_op,      /* # */
    dblhash_op    /* ## */
} op;

typedef enum {
    lbracket_punct,  /* [ */
    rbracket_punct,  /* ] */
    lparen_punct,    /* ( */
    rparen_punct,    /* ) */
    lbrace_punct,    /* { */
    rbrace_punct,    /* } */
    star_punct,      /* * */
    comma_punct,     /* , */
    colon_punct,     /* : */
    eq_punct,        /* = */
    semicolon_punct, /* ; */
    ellipsis_punct,  /* ... */
    hash_punct       /* # */
} punct;

typedef union {
    keyword keyword;
    ident ident;
    constant constant;
    string_lit string_lit;
    op op;
    punct punct;
} lexing_token;

typedef enum {
    lbracket_multi, /* [ */
    rbracket_multi, /* ] */
    lparen_multi,   /* ( */
    rparen_multi,   /* ) */
    star_multi,     /* * */
    comma_multi,    /* , */
    eq_multi,       /* = */
    colon_multi     /* : */
} multi;

typedef struct {
    int span_start;
    int span_end;
    char *msg;
} error;

typedef string pp_number;

typedef string char_cons;

typedef string header_name;

typedef enum {
    space,  /*    */
    newline /* \n */
} whitespace;

typedef struct {
    union {
        header_name header_name_p;
        ident ident_p;
        pp_number pp_number_p;
        char_cons char_cons_p;
        string_lit string_lit_p;
        op op_p;
        punct punct_p;
        multi multi_p;
        error error_p;
        whitespace whitespace_p;
    } p;
    enum {
        header_name_e,
        ident_e,
        pp_number_e,
        char_const_e,
        string_lit_e,
        op_e,
        punct_e,
        multi_e,
        error_e,
        whitespace_e
    } e;
} pp_token;
bool pp_token_eq(pp_token *a, pp_token *b);
string print_pp_token(pp_token *t);

pp_token pp_header_name(header_name h);
pp_token pp_ident(ident i);
pp_token pp_pp_number(pp_number p);
pp_token pp_char_cons(char_cons c);
pp_token pp_string_lit(string_lit s);
pp_token pp_op(op o);
pp_token pp_punct(punct p);
pp_token pp_multi(multi m);
pp_token pp_error(int start, int end, char *msg);
pp_token pp_whitespace(whitespace w);

#endif
