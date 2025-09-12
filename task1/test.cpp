#include <gtest/gtest.h>
#include "stringlist.h"

TEST(StringList, new_ReturnsNotNull) {
    auto list = SL_new();
    ASSERT_NE(nullptr, list) << "SL_new returned nullptr";
}

TEST(StringList, new_ReturnsEmptyList) {
    auto list = SL_new();
    ASSERT_EQ(0, SL_length(list)) << "SL_new returned non-empty list";
}

TEST(StringList, add_AddsItem) {
    const char *str = "Hello World";

    auto list = SL_new();
    SL_add(&list, str);

    ASSERT_EQ(1, SL_length(list)) << "SL_add did not add item to list";
    ASSERT_EQ(0, strcmp(list[0], str)) << "SL_add added wrong item: '" << list[0] << "'";
}

TEST(StringList, remove_RemovesItem) {
    const char *str = "Hello World";

    auto list = SL_new();
    SL_add(&list, str);

    SL_remove(&list, str);
    ASSERT_EQ(0, SL_length(list)) << "SL_remove did not remove item from list";
}

TEST(StringList, remove_DoesNotRemoveIfNoMatchingItem) {
    const char *str = "Hello World";
    const char *str2 = "not Hello World";

    auto list = SL_new();
    SL_add(&list, str);

    SL_remove(&list, str2);
    ASSERT_EQ(1, SL_length(list)) << "SL_remove removed wrong item";
}

TEST(StringList, remove_OnlyRemovesMatchingItems) {
    const char *str = "Hello World";
    const char *str2 = "not Hello World";

    auto list = SL_new();
    SL_add(&list, str);
    SL_add(&list, str2);
    SL_add(&list, str);

    SL_remove(&list, str);
    ASSERT_EQ(1, SL_length(list)) << "SL_remove removed wrong item(s)";
}

TEST(StringList, length_ReturnsCorrectLength) {
    const char *str = "Hello World";

    auto list = SL_new();
    ASSERT_EQ(0, SL_length(list)) << "SL_length doesn't think the list is empty";

    SL_add(&list, str);
    ASSERT_EQ(1, SL_length(list)) << "SL_length did not return correct length";
}

TEST(StringList, count_ReturnsCorrectCount) {
    const char *str = "Hello World";
    const char *str2 = "not Hello World";

    auto list = SL_new();
    ASSERT_EQ(0, SL_count(list, str)) << "SL_count found Hello World in an empty list";

    SL_add(&list, str);
    ASSERT_EQ(1, SL_count(list, str)) << "SL_count either did not find or found multiple of Hello World in the list";
    ASSERT_EQ(0, SL_count(list, str2)) << "SL_count found not Hello World in a list that only has Hello World";

    SL_add(&list, str2);
    ASSERT_EQ(1, SL_count(list, str2));

    SL_add(&list, str2);
    ASSERT_EQ(2, SL_count(list, str2));
}

TEST(StringList, first_index_of_ReturnsMinus1IfNotFound) {
    auto list = SL_new();
    ASSERT_EQ(-1, SL_first_index_of(list, "Hello World")) << "SL_first_index_of found Hello World in an empty list";
}

TEST(StringList, first_index_of_ReturnsCorrectIndex) {
    const char *str = "Hello World";

    auto list = SL_new();
    SL_add(&list, str);

    ASSERT_EQ(0, SL_first_index_of(list, str)) << "SL_first_index_of did not find Hello World in a list that has it?";

    SL_add(&list, str);
    ASSERT_EQ(0, SL_first_index_of(list, str)) << "SL_first_index_of is supposed to return the _first_ index of this string :/";
}
