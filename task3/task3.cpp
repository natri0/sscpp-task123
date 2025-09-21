#include <filesystem>
#include <iostream>
#include <format>
#include <unordered_set>

#include "FileFinder.h"
#include "FileStats.h"

namespace fs = std::filesystem;

/**
 * <code>assert</code> but with embedded std::format, i.e. <code>expect(cond, "oops: {}", "blah")</code>
 */
template<class... FmtArgs>
static void expect(bool condition, std::format_string<FmtArgs...> fmt, FmtArgs&&... fmt_args) {
    if (condition) return;
    std::cerr << std::vformat(fmt.get(), std::make_format_args(fmt_args...)) << std::endl;
    exit(1);
}

int main(int argc, char const *argv[]) {
    expect(argc == 2, "usage: {} <project-root>", argv[0]);

    fs::path project_root = argv[1];
    expect(is_directory(project_root), "project-root (given: {}) must be a directory", project_root.string());

    FileFinder files;
    files.basedir = project_root;

    FileStats all_files;

    for (auto path : files) {
        std::cout << "found path: " << path << std::endl;

        auto stats = get_file_stats(path);
        std::cout << "lines: " << stats.total_lines << std::endl;
        all_files.total_lines += stats.total_lines;
    }

    std::cout << "total lines for all files: " << all_files.total_lines << std::endl;
}
