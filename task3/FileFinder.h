#pragma once

#include <unordered_set>
#include <filesystem>

class FileFinder {
public:

    std::filesystem::path basedir;
    std::unordered_set<std::string> extensions = { ".c", ".cpp", ".h", ".hpp" };

    const std::filesystem::path &operator*();
    const std::filesystem::path *operator->();
    FileFinder &operator++();

    // enable range-based for
    FileFinder begin();
    FileFinder end();

    bool operator!=(const FileFinder &other) const;
private:
    std::filesystem::recursive_directory_iterator iter;
};
