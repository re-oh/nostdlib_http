#ifndef COM_H
#define COM_H

/* common types */
typedef unsigned long usize_t;
typedef long isize_t;

typedef unsigned int   u32_t;
typedef unsigned short u16_t;
typedef unsigned char  u8_t;

typedef int   i32_t;
typedef short i16_t;
typedef char  i8_t;

typedef int bool;

#define true 1
#define false 0
#define NULL ((void*)0)

/* args type */
typedef struct {
    int argc;
    char **argv;
    char **envp;
} args_t;

#endif
