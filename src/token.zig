const std = @import("std");

pub const Token = union(enum) {
    keyword: enum {
        auto,
        break_,
        case,
        char,
        const_,
        continue_,
        default,
        do,
        double,
        else_,
        enum_,
        extern_,
        float,
        for_,
        goto,
        if_,
        inline_,
        int,
        long,
        register,
        restrict,
        return_,
        short,
        signed,
        sizeof,
        static,
        struct_,
        switch_,
        typedef,
        union_,
        unsigned,
        void,
        volatile_,
        while_,
        AlignAs,
        AlignOf,
        Atomic,
        Bool,
        Complex,
        Generic,
        Imaginary,
        Noreturn,
        StaticAssert,
        ThreadLocal,
    },
    ident: struct {
        const Self = @This();
        name: []u8,

        pub fn parse_ident(source: []const u8) Self {
            _ = source;
            return @panic("unimplemented");
        }
    },
    constant: void,
    string_literal: void,
    punctuator: void,
};

pub const PPToken = enum {
    header_name,
    ident,
    pp_number,
    char_constant,
    string_literal,
    punctuator,
    non_whitespace,
};

test "static" {
    std.testing.refAllDecls(@This());
}
