#include "FileStats.h"

#include <cstdio>

constexpr unsigned int BUFFER_SIZE = 1024;

static int get_quotes_count(const char *start, const char *end) {
    int quotes_count = 0;
    for (const char *cur = end; cur >= start; cur--)
        if (*cur == '"') {
            bool is_literal_start_or_end = true;
            if (cur > start && cur[-1] == '\\') is_literal_start_or_end = false;
            if (cur > start && cur[-1] == '\'' && cur[1] == '\'') is_literal_start_or_end = false;

            if (is_literal_start_or_end) quotes_count++;
        }
    return quotes_count;
}

FileStats get_file_stats(const std::filesystem::path &path) {
    if (!is_regular_file(path)) return FileStats::invalid(path);
    FileStats stats = FileStats::valid(path);

    FILE *fp = fopen(path.string().c_str(), "r");
    if (!fp) return FileStats::invalid(path);

    fill_stats_with_fn(stats, reinterpret_cast<GetLineFn>(getline), reinterpret_cast<IsEofFn>(feof), fp);

    fclose(fp);
    return stats;
}

void fill_stats_with_fn(FileStats &stats, GetLineFn getline, IsEofFn feof, void *fp) {
    char *buffer = nullptr;
    size_t buffer_size;

    /*
     * NEW_LINE: the last line has ended in the previous fgets call, this is a new one
     * BLANK: this is the continuation of the previous fgets call (not a new line), all content since the last NEW_LINE was whitespace
     * COMMENT_SINGLE_LINE: this is not a new line, some previous fgets call gave us a '//' => all content after it is comment
     * NORMAL: this is a continuation of a normal line (i.e. not blank or comment), haven't seen a \n yet
     * NORMAL_AFTER_COMMENT: quick hack to not count NORMAL lines after COMMENT_BLOCK twice
     */

    enum {
        NEW_LINE,
        BLANK,
        COMMENT_SINGLE_LINE,
        COMMENT_BLOCK,
        NORMAL,
        NORMAL_AFTER_BLOCK_COMMENT,
    } next_line_status = NEW_LINE;
    while (!feof(fp)) {
        getline(&buffer, &buffer_size, fp);
        size_t len = strlen(buffer);

        bool is_blank = true;
        for (size_t i = 0; is_blank && i < len; i++) {
            if (!isspace(buffer[i])) is_blank = false;
        }

        if (next_line_status == NORMAL || next_line_status == NEW_LINE) {
            next_line_status = NORMAL;
            if (is_blank) next_line_status = BLANK;
            if (char *comment_start = strstr(buffer, "//")) {
                // check if there's an opening quote before the //:
                // if the quotes count is even, all the quotes are matched with another one => this *is* a comment
                // if the quotes count is odd, there's probably an opening quote before the "comment" so it isn't a comment after all
                if (get_quotes_count(buffer, comment_start) % 2 == 0) next_line_status = COMMENT_SINGLE_LINE;
            }
            if (char *comment_start = strstr(buffer, "/*")) {
                if (get_quotes_count(buffer, comment_start) % 2 == 0) next_line_status = COMMENT_BLOCK;
            }
        }

        if (next_line_status == COMMENT_BLOCK && strstr(buffer, "*/")) {
            stats.comment_lines++; // increment it here so that the */ line does get counted
            next_line_status = NORMAL_AFTER_BLOCK_COMMENT;
        }

        if (strchr(buffer, '\n')) {
            if (next_line_status == BLANK)
                stats.blank_lines++;
            if (next_line_status == COMMENT_SINGLE_LINE || next_line_status == COMMENT_BLOCK)
                stats.comment_lines++;
            if (next_line_status == NORMAL)
                stats.code_lines++;
            stats.total_lines++;

            if (next_line_status != COMMENT_BLOCK)
                next_line_status = NEW_LINE;
        }
    }

    free(buffer);
    if (stats.total_lines == 0) {
        stats.blank_lines = stats.total_lines = 1;
    }
}
