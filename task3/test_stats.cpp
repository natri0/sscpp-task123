#include <gtest/gtest.h>

#include "FileStats.h"
#include "gets_string.h"

struct FileStatsTest : testing::Test {
    FileStats stats;

    void fill_stats(char *str) {
        stats = { std::filesystem::path {}, true, 0, 0, 0, 0 };
        fill_stats_with_fn(stats, reinterpret_cast<GetLineFn>(get_line_from_string), reinterpret_cast<IsEofFn>(string_ptr_is_eof), &str);
    }
};

TEST(GetsStringTest, gets_string_ReturnsUntilEndOfLine) {
    char *multiline_string = strdup("This is a\ntest string");

    char buffer[100];
    get_line_from_string(buffer, 100, &multiline_string);
    ASSERT_EQ(0, strcmp(buffer, "This is a\n"));
}

TEST_F(FileStatsTest, CountsOneEmptyLineCorrectly) {
    fill_stats(strdup(""));
    ASSERT_EQ(1, stats.total_lines);
    ASSERT_EQ(1, stats.blank_lines);
}

TEST_F(FileStatsTest, CountsOneSingleLineCommentLineCorrectly) {
    fill_stats(strdup("// test\n"));
    ASSERT_EQ(1, stats.comment_lines);
}

TEST_F(FileStatsTest, CountsOneCodeLineCorrectly) {
    fill_stats(strdup("std::cout << 'a';\n"));
    ASSERT_EQ(1, stats.code_lines);
}

TEST_F(FileStatsTest, CountsOneBlockCommentLineCorrectly) {
    fill_stats(strdup("/* test */\n"));
    ASSERT_EQ(1, stats.comment_lines);
}

TEST_F(FileStatsTest, CountsMultipleLinesCorrectly) {
    fill_stats(strdup("// comment line\n"
                       "/* block\n"
                       " * comment\n"
                       " line */\n"
                       "statement;\n"
                       "\n"));

    EXPECT_EQ(4, stats.comment_lines);
    EXPECT_EQ(1, stats.code_lines);
    EXPECT_EQ(1, stats.blank_lines);
}

TEST_F(FileStatsTest, HandlesQuotesNearCommentCorrectly) {
    fill_stats(strdup("\"// test\n"));
    EXPECT_EQ(0, stats.comment_lines);

    fill_stats(strdup("\"\"// test\n"));
    EXPECT_EQ(1, stats.comment_lines);

    fill_stats(strdup("\"\\\"\"// test\n")); // "\""// test
    EXPECT_EQ(1, stats.comment_lines);

    fill_stats(strdup("'\"'// test\n"));
    EXPECT_EQ(1, stats.comment_lines);
}
