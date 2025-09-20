signed_unsigned_types = ['char', 'int', 'short', 'long', 'long long']
types = ['bool', 'wchar_t', 'char16_t', 'char32_t', 'float', 'double']

__all__ = ['signed_unsigned_types', 'types']

for ty in signed_unsigned_types:
    types.append(ty)
    types.append('unsigned ' + ty)

if __name__ == '__main__':
    print('#pragma once\n'
          '\n'
          'class AnyType {\n'
          'public:\n'
          '    AnyType() : type(NOTHING) {}\n')

    for ty in types:
        underscored = ty.replace(' ', '_')
        enum_name = underscored.upper()
        print(f'    AnyType({ty} x) : type({enum_name}), as_{underscored}(x) {{}}')

    print('\n'
          '    AnyType(const AnyType &other) : type(other.type) {\n'
          '        switch (type) {')

    for ty in types:
        underscored = ty.replace(' ', '_')
        enum_name = underscored.upper()
        print(f'            case {enum_name}: as_{underscored} = other.as_{underscored}; break;')

    print('        }\n'
          '    }\n'
          '\n'
          '    void destroy() {\n'
          '        type = NOTHING;\n'
          '    }\n'
          '    bool has_value() {\n'
          '        return type != NOTHING;\n'
          '    }\n'
          '\n'
          '    Type get_type() {\n'
          '        return type;\n'
          '    }\n'
          '\n'
          '    void swap_with(AnyType &other) {\n'
          '        AnyType temp = *this;\n'
          '        *this = other;\n'
          '        other = temp;\n'
          '    }\n')

    for ty in types:
        underscored = ty.replace(' ', '_')
        enum_name = underscored.upper()
        print(f'    operator {ty}() {{\n'
              f'        if (type != {enum_name}) {{\n'
              f'            throw std::bad_cast();\n'
              f'        }}\n'
              f'        return as_{underscored};\n'
              f'    }}\n')

    print('    enum Type {\n'
          '        NOTHING,')

    for ty in types:
        underscored = ty.replace(' ', '_')
        enum_name = underscored.upper()
        print('        ' + enum_name + ',')

    print('    };\n'
          'private:\n'
          '    Type type;\n'
          '    union {')

    for ty in types:
        underscored = ty.replace(' ', '_')
        enum_name = underscored.upper()
        print(f'        {ty} as_{underscored};')

    print('    };\n'
          '};')
