#ifndef SYS_H
#define SYS_H

#include "com.h"

/* syscall codes */
#define SYS_READ  0
#define SYS_WRITE 1
#define SYS_EXIT  60

/* syscall  */
static inline long syscall(long number, long param1, long param2, long param3) {
    long ret;
    __asm__ __volatile__(
        "syscall"
        : "=a"(ret)
        : "a"(number), "D"(param1), "S"(param2), "d"(param3)
        : "rcx", "r11", "memory"
    );
    return ret;
}

/* syscall impl */

static inline void sys_write(const char *msg, usize_t len) {
    syscall(SYS_WRITE, 1, (isize_t)msg, (isize_t)len);
}

static inline void sys_exit(long code) {
    syscall(SYS_EXIT, code, 0, 0);
    __builtin_unreachable();
}

static inline isize_t sys_read(int fd, char *buf, usize_t len) {
    return syscall(SYS_READ, fd, (isize_t)buf, (isize_t)len);
}

/* runtime startup */

// post asm startup
static inline void __attribute__((used)) _start_c(long *sp, int (*main_func)(args_t)) {
    long argc = *sp;
    char **argv = (char **)(sp + 1);
    char **envp = (char **)(sp + 1 + argc + 1);

    args_t args = {
        .argc = (int)argc,
        .argv = argv,
        .envp = envp
    };

    int ret = main_func(args);
    sys_exit(ret);
}

// define the program entry point
#define ENTRY_POINT(func) \
    __attribute__((__naked__)) void _start() { \
        __asm__ __volatile__( \
            "movq %%rsp, %%rdi \n\t" \
            "andq $-16, %%rsp \n\t" \
            "movq %0, %%rsi \n\t" \
            "call _start_c \n\t" \
            : \
            : "r"(func) \
            : "memory" \
        ); \
    };
#endif