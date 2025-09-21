#include "FileStats.h"

#include <cstdio>

constexpr unsigned int BUFFER_SIZE = 1024;

FileStats get_file_stats(const std::filesystem::path &path) {
    if (!is_regular_file(path)) return FileStats::invalid(path);
    FileStats stats = FileStats::valid(path);

    FILE *fp = fopen(path.string().c_str(), "r");
    if (!fp) return FileStats::invalid(path);

    char buffer[BUFFER_SIZE];

    /*
     * NEW_LINE: the last line has ended in the previous fgets call, this is a new one
     * BLANK: this is the continuation of the previous fgets call (not a new line), all content since the last NEW_LINE was whitespace
     * COMMENT_SINGLE_LINE: this is not a new line, some previous fgets call gave us a '//' => all content after it is comment
     * NORMAL: this is a continuation of a normal line (i.e. not blank or comment), haven't seen a \n yet
     */

    enum {
        NEW_LINE,
        BLANK,
        COMMENT_SINGLE_LINE,
        NORMAL,
    } next_line_status = NEW_LINE;
    while (!feof(fp)) {
        fgets(buffer, BUFFER_SIZE, fp);
        size_t len = strlen(buffer);

        bool is_blank = true;
        for (size_t i = 0; is_blank && i < len; i++) {
            if (!isspace(buffer[i])) is_blank = false;
        }

        if (next_line_status == BLANK && !is_blank)
            next_line_status = NORMAL;
        else if (next_line_status == NORMAL || next_line_status == NEW_LINE) {
            next_line_status = NORMAL;
            if (is_blank) next_line_status = BLANK;
            if (char *comment_start = strstr(buffer, "//")) {
                // check if there's an opening quote before the //
                int quotes_count = 0;
                for (char *cur = comment_start; cur >= buffer; cur--)
                    if (*cur == '"') quotes_count++;

                // if the quotes count is even, all the quotes are matched with another one => this *is* a comment
                // if the quotes count is odd, there's probably an opening quote before the "comment" so it isn't a comment after all
                if (quotes_count % 2 == 0) next_line_status = COMMENT_SINGLE_LINE;
            }
        }

        if (strchr(buffer, '\n')) {
            if (next_line_status == BLANK)
                stats.blank_lines++;
            if (next_line_status == COMMENT_SINGLE_LINE)
                stats.comment_lines++;
            if (next_line_status == NORMAL)
                stats.code_lines++;
            stats.total_lines++;

            next_line_status = NEW_LINE;
        }
    }

    fclose(fp);
    return stats;
}
