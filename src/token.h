#ifndef TOKEN_H
#define TOKEN_H

#include "utils.h"

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
    lbracket_op,    /* [ */
    rbracket_op,    /* ] */
    lparen_op,      /* ( */
    rparen_op,      /* ) */
    period_op,      /* . */
    arrow_op,       /* -> */
    doubleplus_op,  /* ++ */
    doubleminus_op, /* -- */
    logand_op,      /* & */
    star_op,        /* * */
    plus_op,        /* + */
    minus_op,       /* - */
    approx_op,      /* ~ */
    bang_op,        /* ! */
    sizeof_op,      /* sizeof */
    fwslash_op,     /* / */
    percent_op,     /* % */
    shiftl_op,      /* << */
    shiftr_op,      /* >> */
    lt_op,          /* < */
    gt_op,          /* > */
    lteq_op,        /* <= */
    gteq_op,        /* >= */
    eqeq_op,        /* == */
    bangeq_op,      /* != */
    logxor_op,      /* ^ */
    logor_op,       /* | */
    doubleand_op,   /* && */
    doubleor_op,    /* || */
    ternaryq_op,    /* ? */
    ternaryc_op,    /* : */
    eq_op,          /* = */
    stareq_op,      /* *= */
    diveq_op,       /* /= */
    percenteq_op,   /* %= */
    pluseq_op,      /* += */
    minuseq_op,     /* -= */
    shiftleq_op,    /* <<= */
    shiftreq_op,    /* >>= */
    andeq_op,       /* &= */
    xoreq_op,       /* ^= */
    oreq_op,        /* |= */
    comma_op,       /* , */
    hash_op,        /* # */
    dblhash_op      /* ## */
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
    colon_multi,    /* : */
    eq_multi,       /* = */
    hash_multi,     /* # */
    period_multi,   /* . */
    and_multi,      /* & */
    lt_multi,       /* < */
    gt_multi,       /* > */
    plus_multi,     /* + */
    minus_multi,    /* - */
    bang_multi,     /* ! */
    div_multi,      /* / */
    percent_multi,  /* % */
    xor_multi,      /* ^ */
    or_multi        /* | */
} multi;

typedef struct {
    int span_start;
    int span_end;
    const char *msg;
} error;

typedef union {
    keyword keyword;
    ident ident;
    constant constant;
    string_lit string_lit;
    op op;
    punct punct;
    multi multi;
    error error;
    int space;
} scanning_token;

error error_new(int start, int end, const char *msg);

#endif
