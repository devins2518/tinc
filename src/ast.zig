const std = @import("std");
const Allocator = std.mem.Allocator;
const Token = @import("token.zig").Token;

pub const Ast = struct {
    const Self = @This();

    tokens: std.ArrayList(Token),

    pub fn init(alloc: *Allocator) Self {
        return Self{ .tokens = std.ArrayList(Token).init(alloc.*) };
    }

    pub fn parse(self: *Self, source: []const u8) !void {
        _ = self;
        _ = source;
        @panic("unimplemented");
    }

    pub fn deinit(self: Self) void {
        self.tokens.deinit();
    }
};

test "parse into ast" {
    var alloc = std.heap.ArenaAllocator.init(std.heap.c_allocator);
    defer alloc.deinit();

    const source =
        \\int main() {
        \\  return 0;
        \\}
    ;
    var ast = Ast.init(&alloc.allocator());
    defer ast.deinit();
    try ast.parse(source);
}

test "static" {
    std.testing.refAllDecls(@This());
}
