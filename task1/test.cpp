#include <gtest/gtest.h>
#include "stringlist.h"

struct SLTest : testing::Test {
    SLTest() {
        list = SL_new();
    }

    ~SLTest() override {
        SL_free(list);
    }

    StringList list;
    const char *str = "Hello World";
    const char *str2 = "not Hello World";
};

TEST_F(SLTest, new_ReturnsNotNull) {
    ASSERT_NE(nullptr, list) << "SL_new returned nullptr";
}

TEST_F(SLTest, new_ReturnsEmptyList) {
    ASSERT_EQ(0, SL_length(list)) << "SL_new returned non-empty list";
}

TEST_F(SLTest, add_AddsItem) {
    SL_add(&list, str);

    ASSERT_EQ(1, SL_length(list)) << "SL_add did not add item to list";
    ASSERT_EQ(0, strcmp(list[0], str)) << "SL_add added wrong item: '" << list[0] << "'";
}

TEST_F(SLTest, remove_RemovesItem) {
    SL_add(&list, str);

    SL_remove(&list, str);
    ASSERT_EQ(0, SL_length(list)) << "SL_remove did not remove item from list";
}

TEST_F(SLTest, remove_DoesNotRemoveIfNoMatchingItem) {
    SL_add(&list, str);

    SL_remove(&list, str2);
    ASSERT_EQ(1, SL_length(list)) << "SL_remove removed wrong item";
}

TEST_F(SLTest, remove_OnlyRemovesMatchingItems) {
    SL_add(&list, str);
    SL_add(&list, str2);
    SL_add(&list, str);

    SL_remove(&list, str);
    ASSERT_EQ(1, SL_length(list)) << "SL_remove removed wrong item(s)";
}

TEST_F(SLTest, length_ReturnsCorrectLength) {
    ASSERT_EQ(0, SL_length(list)) << "SL_length doesn't think the list is empty";

    SL_add(&list, str);
    ASSERT_EQ(1, SL_length(list)) << "SL_length did not return correct length";
}

TEST_F(SLTest, count_ReturnsCorrectCount) {
    ASSERT_EQ(0, SL_count(list, str)) << "SL_count found Hello World in an empty list";

    SL_add(&list, str);
    ASSERT_EQ(1, SL_count(list, str)) << "SL_count either did not find or found multiple of Hello World in the list";
    ASSERT_EQ(0, SL_count(list, str2)) << "SL_count found not Hello World in a list that only has Hello World";

    SL_add(&list, str2);
    ASSERT_EQ(1, SL_count(list, str2));

    SL_add(&list, str2);
    ASSERT_EQ(2, SL_count(list, str2));
}

TEST_F(SLTest, first_index_of_ReturnsMinus1IfNotFound) {
    ASSERT_EQ(-1, SL_first_index_of(list, "Hello World")) << "SL_first_index_of found Hello World in an empty list";
}

TEST_F(SLTest, first_index_of_ReturnsCorrectIndex) {
    SL_add(&list, str);

    ASSERT_EQ(0, SL_first_index_of(list, str)) << "SL_first_index_of did not find Hello World in a list that has it?";

    SL_add(&list, str);
    ASSERT_EQ(0, SL_first_index_of(list, str)) << "SL_first_index_of is supposed to return the _first_ index of this string :/";
}

TEST_F(SLTest, sort_WorksCorrectly) {
    SL_add(&list, str2);
    SL_add(&list, str);
    SL_sort(list);

    ASSERT_EQ(0, strcmp(str, list[0])) << "Sorting did not work as expected";
}

TEST_F(SLTest, remove_duplicates_DoesNothingIfOneElement) {
    SL_add(&list, str);
    SL_remove_duplicates(&list);

    ASSERT_EQ(1, SL_length(list)) << "SL_remove_duplicates removed the only element";
}

TEST_F(SLTest, remove_duplicates_DoesNotRemoveFirstOccurence) {
    SL_add(&list, str);
    SL_add(&list, str);
    SL_remove_duplicates(&list);

    ASSERT_EQ(1, SL_length(list)) << "SL_remove_duplicates removed both occurrences of a repeating element";
}

TEST_F(SLTest, remove_duplicates_DoesNotRemoveUniqueElements) {
    SL_add(&list, str);
    SL_add(&list, str);
    SL_add(&list, str2);
    SL_remove_duplicates(&list);

    ASSERT_EQ(2, SL_length(list));
    ASSERT_EQ(0, strcmp(str2, list[1])) << "SL_remove_duplicates removed unique element";
}
