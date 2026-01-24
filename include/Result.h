#ifndef _RESULT_H_
#define _RESULT_H_

#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define DEFINE_RESULT(T, name) \
typedef struct Result##name {  \
    char *err;                 \
    T data;                    \
} Result##name;

#define OK(name, v) ((Result##name){ .data = v, .err = NULL})
#define OKV(name) ((Result##name){ .err = NULL})
#define ERR(name, e) ((Result##name){ .err = e})

#define TRY(T, expr)                \
do{                                 \
    T _r = (expr);                  \
    if (_r.err != NULL) return _r;  \
}while(0)

#define TRYGET(v, expr)             \
do{                                 \
    (v) = (expr);                   \
    if((v).err != NULL) return (v); \
} while(0)

#define _TRYGET(T, v, expr)            \
/* Try get a velue from a expression that returns an Result(name) */  \
/* T: Return type */  \
/* v: Variable that will receive value */  \
/* expr: expression that returns an Result(name) */  \
do{                        \
    (v) = (expr);          \
    T _r = {0}; \
    _r.err = v.err;        \
    if((v).err != NULL) {  \
        return _r;         \
    }                      \
} while(0)

typedef struct ResultVoid {
    char *err;
} ResultVoid;

#endif
