#include "cpm22/bdos.hpp"
#include "cpm22/disk.hpp"
#include <filesystem>
#include <iostream>
#include <string>

int main() {
    const auto root = std::filesystem::temp_directory_path() / "eniac_cpm22_test_disk";
    std::error_code ec;
    std::filesystem::remove_all(root, ec);
    cpm22::Disk disk(root);
    cpm22::Bdos bdos(disk);
    std::string error;
    int failures = 0;
    const auto check = [&failures](bool condition, const char* message) {
        if (!condition) { std::cerr << "FAIL: " << message << '\n'; ++failures; }
    };
    check(cpm22::Disk::normalize_name("hello.txt").value_or("") == "HELLO.TXT", "8.3 name normalizes");
    check(!cpm22::Disk::normalize_name("../escape.txt"), "path traversal rejected");
    check(!cpm22::Disk::normalize_name("TOO-LONG-NAME.TXT"), "overlong basename rejected");
    check(bdos.write_file("HELLO.TXT", "hello world\n", error), "write file");
    const auto read = bdos.read_file("hello.txt", error);
    check(read && *read == "hello world\n", "case-insensitive read");
    check(bdos.copy_file("HELLO.TXT", "COPY.TXT", error), "copy file");
    check(bdos.rename_file("COPY.TXT", "RENAMED.TXT", error), "rename file");
    check(bdos.read_file("RENAMED.TXT", error).has_value(), "renamed file exists");
    check(bdos.set_user(3, error), "select user area");
    check(!bdos.read_file("HELLO.TXT", error), "user areas isolated");
    check(bdos.set_user(0, error), "return to user zero");
    check(bdos.delete_file("HELLO.TXT", error), "delete file");
    check(!bdos.read_file("HELLO.TXT", error), "deleted file absent");
    check(bdos.set_drive('B', error), "select drive B");
    check(disk.drive() == 'B', "current drive updates");
    std::filesystem::remove_all(root, ec);
    if (failures) return 1;
    std::cout << "All CP/M-style disk tests passed.\n";
    return 0;
}
