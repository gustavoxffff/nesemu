#ifndef _RESULT_H_
#define _RESULT_H_

#include <stdint.h>

#define DEFINE_RESULT(T)              \
typedef struct Result_##T {           \
    char *err;                        \
    T type;                           \
} Result_##T;

#define OK(T, v) ((Result_##T){ .value = v, .err = NULL })
#define ERR(T, e) ((Result_##T){ .err = e })

#define TRY(T, expr)                \
{                                   \
    Result_##T _r = (expr);         \
    if (_r.err != NULL) return _r;  \
}

typedef enum Type {
    TYPE_VOID,
    TYPE_INT,
    TYPE_BYTE,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_CHAR_P
}Type;

typedef struct Result {
    char *err;
    Type type;
    union res {
        int     INT_RESULT;
        uint8_t BYTE_RESULT;
        float   FLOAT_RESULT;
        char    CHAR_RESULT;
        char    *CHAR_POINTER_RESULT;
    }res;
} Result;

#endif
