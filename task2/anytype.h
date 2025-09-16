#pragma once
#include <exception>

class BadCast : public std::exception {
};

class AnyType {
public:
    AnyType() : type(NOTHING) {}

    AnyType(bool x) : type(BOOL), as_bool(x) {}
    AnyType(wchar_t x) : type(WCHAR_T), as_wchar_t(x) {}
    AnyType(char16_t x) : type(CHAR16_T), as_char16_t(x) {}
    AnyType(char32_t x) : type(CHAR32_T), as_char32_t(x) {}
    AnyType(float x) : type(FLOAT), as_float(x) {}
    AnyType(double x) : type(DOUBLE), as_double(x) {}
    AnyType(char x) : type(CHAR), as_char(x) {}
    AnyType(unsigned char x) : type(UNSIGNED_CHAR), as_unsigned_char(x) {}
    AnyType(int x) : type(INT), as_int(x) {}
    AnyType(unsigned int x) : type(UNSIGNED_INT), as_unsigned_int(x) {}
    AnyType(short x) : type(SHORT), as_short(x) {}
    AnyType(unsigned short x) : type(UNSIGNED_SHORT), as_unsigned_short(x) {}
    AnyType(long x) : type(LONG), as_long(x) {}
    AnyType(unsigned long x) : type(UNSIGNED_LONG), as_unsigned_long(x) {}
    AnyType(long long x) : type(LONG_LONG), as_long_long(x) {}
    AnyType(unsigned long long x) : type(UNSIGNED_LONG_LONG), as_unsigned_long_long(x) {}

    AnyType(const AnyType &other) : type(other.type) {
        switch (type) {
            case BOOL: as_bool = other.as_bool; break;
            case WCHAR_T: as_wchar_t = other.as_wchar_t; break;
            case CHAR16_T: as_char16_t = other.as_char16_t; break;
            case CHAR32_T: as_char32_t = other.as_char32_t; break;
            case FLOAT: as_float = other.as_float; break;
            case DOUBLE: as_double = other.as_double; break;
            case CHAR: as_char = other.as_char; break;
            case UNSIGNED_CHAR: as_unsigned_char = other.as_unsigned_char; break;
            case INT: as_int = other.as_int; break;
            case UNSIGNED_INT: as_unsigned_int = other.as_unsigned_int; break;
            case SHORT: as_short = other.as_short; break;
            case UNSIGNED_SHORT: as_unsigned_short = other.as_unsigned_short; break;
            case LONG: as_long = other.as_long; break;
            case UNSIGNED_LONG: as_unsigned_long = other.as_unsigned_long; break;
            case LONG_LONG: as_long_long = other.as_long_long; break;
            case UNSIGNED_LONG_LONG: as_unsigned_long_long = other.as_unsigned_long_long; break;
        }
    }

    void destroy() {
        type = NOTHING;
    }
    bool has_value() {
        return type != NOTHING;
    }

    void swap_with(AnyType &other) {
        AnyType temp = *this;
        *this = other;
        other = temp;
    }

    operator bool() {
        if (type != BOOL) {
            throw BadCast();
        }
        return as_bool;
    }

    operator wchar_t() {
        if (type != WCHAR_T) {
            throw BadCast();
        }
        return as_wchar_t;
    }

    operator char16_t() {
        if (type != CHAR16_T) {
            throw BadCast();
        }
        return as_char16_t;
    }

    operator char32_t() {
        if (type != CHAR32_T) {
            throw BadCast();
        }
        return as_char32_t;
    }

    operator float() {
        if (type != FLOAT) {
            throw BadCast();
        }
        return as_float;
    }

    operator double() {
        if (type != DOUBLE) {
            throw BadCast();
        }
        return as_double;
    }

    operator char() {
        if (type != CHAR) {
            throw BadCast();
        }
        return as_char;
    }

    operator unsigned char() {
        if (type != UNSIGNED_CHAR) {
            throw BadCast();
        }
        return as_unsigned_char;
    }

    operator int() {
        if (type != INT) {
            throw BadCast();
        }
        return as_int;
    }

    operator unsigned int() {
        if (type != UNSIGNED_INT) {
            throw BadCast();
        }
        return as_unsigned_int;
    }

    operator short() {
        if (type != SHORT) {
            throw BadCast();
        }
        return as_short;
    }

    operator unsigned short() {
        if (type != UNSIGNED_SHORT) {
            throw BadCast();
        }
        return as_unsigned_short;
    }

    operator long() {
        if (type != LONG) {
            throw BadCast();
        }
        return as_long;
    }

    operator unsigned long() {
        if (type != UNSIGNED_LONG) {
            throw BadCast();
        }
        return as_unsigned_long;
    }

    operator long long() {
        if (type != LONG_LONG) {
            throw BadCast();
        }
        return as_long_long;
    }

    operator unsigned long long() {
        if (type != UNSIGNED_LONG_LONG) {
            throw BadCast();
        }
        return as_unsigned_long_long;
    }

    enum Type {
        NOTHING,
        BOOL,
        WCHAR_T,
        CHAR16_T,
        CHAR32_T,
        FLOAT,
        DOUBLE,
        CHAR,
        UNSIGNED_CHAR,
        INT,
        UNSIGNED_INT,
        SHORT,
        UNSIGNED_SHORT,
        LONG,
        UNSIGNED_LONG,
        LONG_LONG,
        UNSIGNED_LONG_LONG,
    };

    Type get_type() {
        return type;
    }
private:
    Type type;
    union {
        bool as_bool;
        wchar_t as_wchar_t;
        char16_t as_char16_t;
        char32_t as_char32_t;
        float as_float;
        double as_double;
        char as_char;
        unsigned char as_unsigned_char;
        int as_int;
        unsigned int as_unsigned_int;
        short as_short;
        unsigned short as_unsigned_short;
        long as_long;
        unsigned long as_unsigned_long;
        long long as_long_long;
        unsigned long long as_unsigned_long_long;
    };
};
