#ifndef DECLARES_H
#define DECLARES_H

#include <stdint.h>
#include <stddef.h>

// some snippets from https://nullprogram.com/blog/2023/10/08/
// and some of my own extensions for making C more "modern"

// simple helpful macros
#define countof(a)    (size)(sizeof(a) / sizeof(*(a)))
#define lengthof(s)   (countof(s) - 1)
/* #define MAX(a,b)      () */
/* #define MIN(a,b)      () */

// signed types
typedef uint8_t       u8;
typedef uint16_t      u16;
typedef uint32_t      u32;
typedef uint64_t      u64;

typedef int8_t        i8;
typedef int16_t       i16;
typedef int32_t       i32;
typedef int64_t       i64;

typedef float         f32;
typedef double        f64;

typedef size_t        usize;
typedef ptrdiff_t     size;
typedef unsigned char utf8;

// length based-strings
#define s8(s) (s8){(utf8 *)s, lengthof(s)}
typedef struct {
  utf8 * data;
  usize len;
} s8;

#endif
