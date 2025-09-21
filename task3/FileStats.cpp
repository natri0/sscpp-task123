#include "FileStats.h"

#include <cstdio>

constexpr unsigned int BUFFER_SIZE = 1024;

FileStats get_file_stats(const std::filesystem::path &path) {
    if (!is_regular_file(path)) return FileStats::invalid(path);
    FileStats stats = FileStats::valid(path);

    FILE *fp = fopen(path.string().c_str(), "r");
    if (!fp) return FileStats::invalid(path);

    char buffer[BUFFER_SIZE + 1];
    buffer[BUFFER_SIZE] = '\0';

    /*
     * `total_lines`: ez, count of '\n' + 1
     * `blank_lines`: if (this char == '\n' && prev char == '\n') count++
     * `comment_lines`:
     *     if (chars[start of line ... end of line] includes "//") count++
     *     if (start of "//" != start of line) code_lines++
     * `code_lines`: if (not comment && not blank) code_lines++
     */

    while (!feof(fp)) {
        size_t actual_size = fread(buffer, 1, BUFFER_SIZE, fp);
        buffer[actual_size] = '\0';

        for (size_t i = 0; i < actual_size; i++) if (buffer[i] == '\n') stats.total_lines++;
    }

    fclose(fp);
    return stats;
}
