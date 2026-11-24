#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define arena_cap (4*1024*1024) // (4 MB)

// TODO :: make linked list design so this can grow forevermore
// TODO :: implement functions, macros, and other things
// NOTE :: take inspo from to other designs that I have been looking at. (GB, CD, TS)

typedef struct Region Region;
struct Region {
  u8 * buffer;
  u64 capacity;
  u64 used;
  Region * prev;
};

// the bump allocator is just a region of memory that we can scroll through
typedef struct {
  Region * first;
  u32 region_count;
} arena;

void arena_init(arena * Arena) {
  return 0;
}

rawptr arena_alloc(arena* Arena, sz obj) {
  return 0;
}

void arena_reset(arena* Arena) {
  // dealloc all blocks and chunks and leave empty or something
  return 0;
}

b32 arena_realloc(arena* Arena) {
  return 0;
}

int main() {
  printf("working");
  /* arena * thread_buf = arena_init(thread_buf); */
}
