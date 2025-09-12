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
