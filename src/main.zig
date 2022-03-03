const std = @import("std");

pub fn main() anyerror!void {
    std.log.info("All your codebase are belong to us.", .{});
}

test "static" {
    _ = @import("token.zig");
    _ = @import("ast.zig");
    std.testing.refAllDecls(@This());
}
