const std = @import("std");

pub fn build(b: *std.build.Builder) !void {
    const target = b.standardTargetOptions(.{});
    const mode = b.standardReleaseOptions();

    const result = try std.ChildProcess.exec(.{
        .allocator = b.allocator,
        .argv = &[_][]const u8{ "xcrun", "-show-sdk-path" },
    });
    const sysroot = result.stdout;
    b.sysroot = sysroot[0 .. sysroot.len - 1];

    const exe = b.addExecutableSource("tinc", null);

    var dir = try std.fs.cwd().openDir("src", .{ .iterate = true });
    defer dir.close();
    var walker = try dir.walk(b.allocator);
    defer walker.deinit();
    const exts = .{ ".c", ".cpp", ".cxx" };
    while (try walker.next()) |f| {
        var src = std.ArrayList(u8).init(b.allocator);
        defer src.deinit();
        inline for (exts) |ext| {
            if (std.mem.eql(u8, std.fs.path.extension(f.path), ext)) {
                try src.appendSlice("src/");
                try src.appendSlice(f.path);
                exe.addCSourceFile(
                    src.items,
                    &[_][]const u8{ "-Wall", "-std=c89", "-Werror" },
                );
            }
        }
    }
    exe.linkLibC();
    exe.addSystemIncludePath(sysroot[0 .. sysroot.len - 1]);
    exe.setTarget(target);
    exe.setBuildMode(mode);
    exe.install();
}
