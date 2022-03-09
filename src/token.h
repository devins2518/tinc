#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    auto_,
    double_,
    int_,
    struct_,
    break_,
    else_,
    long_,
    switch_,
    case_,
    enum_,
    register_,
    typedef_,
    char_,
    extern_,
    return_,
    union_,
    const_,
    float_,
    short_,
    unsigned_,
    continue_,
    for_,
    signed_,
    void_,
    default_,
    goto_,
    sizeof_,
    volatile_,
    do_,
    if_,
    static_,
    while_,
} keyword;

typedef struct {
    char *name;
    int size;
} ident;

typedef union {
    keyword keyword;
    ident ident;
    int constant;
    int string_lit;
    int operator;
    int punct;
    int header_name;
} token;

#endif
