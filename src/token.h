#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    auto_kw,
    double_kw,
    int_kw,
    struct_kw,
    break_kw,
    else_kw,
    long_kw,
    switch_kw,
    case_kw,
    enum_kw,
    register_kw,
    typedef_kw,
    char_kw,
    extern_kw,
    return_kw,
    union_kw,
    const_kw,
    float_kw,
    short_kw,
    unsigned_kw,
    continue_kw,
    for_kw,
    signed_kw,
    void_kw,
    default_kw,
    goto_kw,
    sizeof_kw,
    volatile_kw,
    do_kw,
    if_kw,
    static_kw,
    while_kw
} keyword;

typedef struct {
    char *name;
    int size;
} ident;

typedef enum { float_const, int_const, enum_const, char_const } constant;

typedef struct {
    char *start;
    int size;
} string_lit;

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
    ternaryc_op     /* : */
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
} token;

#endif
