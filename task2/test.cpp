#include <gtest/gtest.h>
#include "anytype.h"

struct AnyTypeTest : testing::Test {
    AnyType var;
};

TEST_F(AnyTypeTest, newValue_IsNothing) {
    ASSERT_EQ(AnyType::NOTHING, var.get_type());
    ASSERT_EQ(false, var.has_value());
}

TEST_F(AnyTypeTest, destroy_SetsToNothing) {
    var = 1;
    var.destroy();
    ASSERT_EQ(AnyType::NOTHING, var.get_type());
    ASSERT_EQ(false, var.has_value());
}
TEST_F(AnyTypeTest, swapWithOther_SwapsCorrectly) {
    AnyType other = (int) 1;
    var = (int) 2;
    var.swap_with(other);
    ASSERT_EQ(1, (int) var);
    ASSERT_EQ(2, (int) other);
}

TEST_F(AnyTypeTest, assign_Bool) {
    var = (bool) 1;
    ASSERT_EQ(AnyType::BOOL, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((bool) 1, (bool) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_Bool) {
    AnyType other = (bool) 1;
    var = other;
    ASSERT_EQ(AnyType::BOOL, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((bool) 1, (bool) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_Bool_to_UnsignedLongLong) {
    var = (bool) 1;
    ASSERT_THROW({
        unsigned long long value = var;
    }, BadCast);
}

TEST_F(AnyTypeTest, assign_WcharT) {
    var = (wchar_t) 1;
    ASSERT_EQ(AnyType::WCHAR_T, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((wchar_t) 1, (wchar_t) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_WcharT) {
    AnyType other = (wchar_t) 1;
    var = other;
    ASSERT_EQ(AnyType::WCHAR_T, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((wchar_t) 1, (wchar_t) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_WcharT_to_Bool) {
    var = (wchar_t) 1;
    ASSERT_THROW({
        bool value = var;
    }, BadCast);
}

TEST_F(AnyTypeTest, assign_Char16T) {
    var = (char16_t) 1;
    ASSERT_EQ(AnyType::CHAR16_T, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((char16_t) 1, (char16_t) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_Char16T) {
    AnyType other = (char16_t) 1;
    var = other;
    ASSERT_EQ(AnyType::CHAR16_T, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((char16_t) 1, (char16_t) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_Char16T_to_WcharT) {
    var = (char16_t) 1;
    ASSERT_THROW({
        wchar_t value = var;
    }, BadCast);
}

TEST_F(AnyTypeTest, assign_Char32T) {
    var = (char32_t) 1;
    ASSERT_EQ(AnyType::CHAR32_T, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((char32_t) 1, (char32_t) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_Char32T) {
    AnyType other = (char32_t) 1;
    var = other;
    ASSERT_EQ(AnyType::CHAR32_T, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((char32_t) 1, (char32_t) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_Char32T_to_Char16T) {
    var = (char32_t) 1;
    ASSERT_THROW({
        char16_t value = var;
    }, BadCast);
}

TEST_F(AnyTypeTest, assign_Float) {
    var = (float) 1;
    ASSERT_EQ(AnyType::FLOAT, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((float) 1, (float) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_Float) {
    AnyType other = (float) 1;
    var = other;
    ASSERT_EQ(AnyType::FLOAT, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((float) 1, (float) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_Float_to_Char32T) {
    var = (float) 1;
    ASSERT_THROW({
        char32_t value = var;
    }, BadCast);
}

TEST_F(AnyTypeTest, assign_Double) {
    var = (double) 1;
    ASSERT_EQ(AnyType::DOUBLE, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((double) 1, (double) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_Double) {
    AnyType other = (double) 1;
    var = other;
    ASSERT_EQ(AnyType::DOUBLE, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((double) 1, (double) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_Double_to_Float) {
    var = (double) 1;
    ASSERT_THROW({
        float value = var;
    }, BadCast);
}

TEST_F(AnyTypeTest, assign_Char) {
    var = (char) 1;
    ASSERT_EQ(AnyType::CHAR, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((char) 1, (char) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_Char) {
    AnyType other = (char) 1;
    var = other;
    ASSERT_EQ(AnyType::CHAR, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((char) 1, (char) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_Char_to_Double) {
    var = (char) 1;
    ASSERT_THROW({
        double value = var;
    }, BadCast);
}

TEST_F(AnyTypeTest, assign_UnsignedChar) {
    var = (unsigned char) 1;
    ASSERT_EQ(AnyType::UNSIGNED_CHAR, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((unsigned char) 1, (unsigned char) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_UnsignedChar) {
    AnyType other = (unsigned char) 1;
    var = other;
    ASSERT_EQ(AnyType::UNSIGNED_CHAR, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((unsigned char) 1, (unsigned char) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_UnsignedChar_to_Char) {
    var = (unsigned char) 1;
    ASSERT_THROW({
        char value = var;
    }, BadCast);
}

TEST_F(AnyTypeTest, assign_Int) {
    var = (int) 1;
    ASSERT_EQ(AnyType::INT, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((int) 1, (int) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_Int) {
    AnyType other = (int) 1;
    var = other;
    ASSERT_EQ(AnyType::INT, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((int) 1, (int) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_Int_to_UnsignedChar) {
    var = (int) 1;
    ASSERT_THROW({
        unsigned char value = var;
    }, BadCast);
}

TEST_F(AnyTypeTest, assign_UnsignedInt) {
    var = (unsigned int) 1;
    ASSERT_EQ(AnyType::UNSIGNED_INT, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((unsigned int) 1, (unsigned int) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_UnsignedInt) {
    AnyType other = (unsigned int) 1;
    var = other;
    ASSERT_EQ(AnyType::UNSIGNED_INT, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((unsigned int) 1, (unsigned int) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_UnsignedInt_to_Int) {
    var = (unsigned int) 1;
    ASSERT_THROW({
        int value = var;
    }, BadCast);
}

TEST_F(AnyTypeTest, assign_Short) {
    var = (short) 1;
    ASSERT_EQ(AnyType::SHORT, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((short) 1, (short) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_Short) {
    AnyType other = (short) 1;
    var = other;
    ASSERT_EQ(AnyType::SHORT, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((short) 1, (short) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_Short_to_UnsignedInt) {
    var = (short) 1;
    ASSERT_THROW({
        unsigned int value = var;
    }, BadCast);
}

TEST_F(AnyTypeTest, assign_UnsignedShort) {
    var = (unsigned short) 1;
    ASSERT_EQ(AnyType::UNSIGNED_SHORT, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((unsigned short) 1, (unsigned short) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_UnsignedShort) {
    AnyType other = (unsigned short) 1;
    var = other;
    ASSERT_EQ(AnyType::UNSIGNED_SHORT, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((unsigned short) 1, (unsigned short) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_UnsignedShort_to_Short) {
    var = (unsigned short) 1;
    ASSERT_THROW({
        short value = var;
    }, BadCast);
}

TEST_F(AnyTypeTest, assign_Long) {
    var = (long) 1;
    ASSERT_EQ(AnyType::LONG, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((long) 1, (long) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_Long) {
    AnyType other = (long) 1;
    var = other;
    ASSERT_EQ(AnyType::LONG, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((long) 1, (long) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_Long_to_UnsignedShort) {
    var = (long) 1;
    ASSERT_THROW({
        unsigned short value = var;
    }, BadCast);
}

TEST_F(AnyTypeTest, assign_UnsignedLong) {
    var = (unsigned long) 1;
    ASSERT_EQ(AnyType::UNSIGNED_LONG, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((unsigned long) 1, (unsigned long) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_UnsignedLong) {
    AnyType other = (unsigned long) 1;
    var = other;
    ASSERT_EQ(AnyType::UNSIGNED_LONG, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((unsigned long) 1, (unsigned long) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_UnsignedLong_to_Long) {
    var = (unsigned long) 1;
    ASSERT_THROW({
        long value = var;
    }, BadCast);
}

TEST_F(AnyTypeTest, assign_LongLong) {
    var = (long long) 1;
    ASSERT_EQ(AnyType::LONG_LONG, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((long long) 1, (long long) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_LongLong) {
    AnyType other = (long long) 1;
    var = other;
    ASSERT_EQ(AnyType::LONG_LONG, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((long long) 1, (long long) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_LongLong_to_UnsignedLong) {
    var = (long long) 1;
    ASSERT_THROW({
        unsigned long value = var;
    }, BadCast);
}

TEST_F(AnyTypeTest, assign_UnsignedLongLong) {
    var = (unsigned long long) 1;
    ASSERT_EQ(AnyType::UNSIGNED_LONG_LONG, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((unsigned long long) 1, (unsigned long long) var);
}
TEST_F(AnyTypeTest, assignToOtherWith_UnsignedLongLong) {
    AnyType other = (unsigned long long) 1;
    var = other;
    ASSERT_EQ(AnyType::UNSIGNED_LONG_LONG, var.get_type());
    ASSERT_EQ(true, var.has_value());
    ASSERT_EQ((unsigned long long) 1, (unsigned long long) var);
}
TEST_F(AnyTypeTest, badCastThrown_tryCast_UnsignedLongLong_to_LongLong) {
    var = (unsigned long long) 1;
    ASSERT_THROW({
        long long value = var;
    }, BadCast);
}

