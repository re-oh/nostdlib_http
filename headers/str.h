#ifndef STR_H
#define STR_H

#include "com.h"
#include "sys.h"

typedef struct {
    const char *ptr;
    usize_t len;
} str_t;

static inline usize_t strlen(const char *s) {
    usize_t len = 0;
    while (s[len]) len++;
    return len;
};

static inline str_t strfrom(const char *s) {
    return (str_t){
        .ptr = s,
        .len = strlen(s)
    };
};

static inline void print(str_t s) {
    sys_write(s.ptr, s.len);
}

#define print_c(str) print(strfrom(str))

#endif
