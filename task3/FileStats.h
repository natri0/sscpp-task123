#pragma once

#include <filesystem>

struct FileStats {
    std::filesystem::path path;
    bool is_valid;

    int total_lines;
    int blank_lines;
    int comment_lines;
    int code_lines;

    operator bool() const { return is_valid; }

    static FileStats valid(const std::filesystem::path &path) {
        return { path, true, 0, 0, 0, 0 };
    }

    static FileStats invalid(const std::filesystem::path &path) {
        return { path, false };
    }
};

using GetLineFn = char *(*)(char *buffer, int buffer_size, void *stream);
using IsEofFn = bool(*)(void *stream);

FileStats get_file_stats(const std::filesystem::path& path);
void fill_stats_with_fn(FileStats &stats, GetLineFn fgets, IsEofFn feof, void *fp);
