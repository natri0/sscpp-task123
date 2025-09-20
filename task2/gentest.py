from generate import types, signed_unsigned_types

AT = 'AnyType'
AT_H = 'anytype.h'
FIXTURE = AT + 'Test'

if __name__ == '__main__':
    print(f'#include <gtest/gtest.h>\n'
          f'#include "{AT_H}"\n'
          f'\n'
          f'struct {FIXTURE} : testing::Test {{\n'
          f'    {AT} var;\n'
          f'}};\n')

    print(f'TEST_F({FIXTURE}, newValue_IsNothing) {{\n'
          f'    ASSERT_EQ({AT}::NOTHING, var.get_type());\n'
          f'    ASSERT_EQ(false, var.has_value());\n'
          f'}}\n'
          f'\n'
          f'TEST_F({FIXTURE}, destroy_SetsToNothing) {{\n'
          f'    var = 1;\n'
          f'    var.destroy();\n'
          f'    ASSERT_EQ({AT}::NOTHING, var.get_type());\n'
          f'    ASSERT_EQ(false, var.has_value());\n'
          f'}}\n'
          f'TEST_F({FIXTURE}, swapWithOther_SwapsCorrectly) {{\n'
          f'    {AT} other = (int) 1;\n'
          f'    var = (int) 2;\n'
          f'    var.swap_with(other);\n'
          f'    ASSERT_EQ(1, (int) var);\n'
          f'    ASSERT_EQ(2, (int) other);\n'
          f'}}\n')

    for (i, ty) in enumerate(types):
        underscored = ty.replace(' ', '_')
        pascal_case = ty.title().replace(' ', '').replace('_', '')
        enum_name = underscored.upper()

        prev = types[i-1]
        underscored_prev = prev.replace(' ', '_')
        pascal_case_prev = prev.title().replace(' ', '').replace('_', '')
        enum_name_prev = underscored_prev.upper()

        print(f'TEST_F({FIXTURE}, assign_{pascal_case}) {{\n'
              f'    var = ({ty}) 1;\n'
              f'    ASSERT_EQ({AT}::{enum_name}, var.get_type());\n'
              f'    ASSERT_EQ(true, var.has_value());\n'
              f'    ASSERT_EQ(({ty}) 1, ({ty}) var);\n'
              f'}}\n'
              f'TEST_F({FIXTURE}, assignToOtherWith_{pascal_case}) {{\n'
              f'    AnyType other = ({ty}) 1;\n'
              f'    var = other;\n'
              f'    ASSERT_EQ({AT}::{enum_name}, var.get_type());\n'
              f'    ASSERT_EQ(true, var.has_value());\n'
              f'    ASSERT_EQ(({ty}) 1, ({ty}) var);\n'
              f'}}\n'
              f'TEST_F({FIXTURE}, badCastThrown_tryCast_{pascal_case}_to_{pascal_case_prev}) {{\n'
              f'    var = ({ty}) 1;\n'
              f'    ASSERT_THROW({{\n'
              f'        {prev} value = var;\n'
              f'    }}, BadCast);\n'
              f'}}\n')
