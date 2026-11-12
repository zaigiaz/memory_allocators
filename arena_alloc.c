#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define arena_cap (8*1024*1024) // (8 kilobytes)

// TODO :: make linked list design so this can grow forevermore

// the bump allocator is just a region of memory that we can scroll through
typedef struct {
  u8 * buffer;
  u64 capacity;
  u64 used;
} arena;

arena * arena_init(arena * Arena) {

  // set arena to fixed-size block
  // TODO :: change this to mmap() to avoid malloc use
  Arena->buffer = malloc(arena_cap);
  Arena->capacity = 0;
  Arena->used = 0;

  return Arena;
}

arena * arena_alloc(arena* Arena, size_t obj_size) {
  if(obj_size > Arena->capacity - Arena->used) {
    fprintf(stderr, "capacity of array was exceeded in the arena_alloc function");
    return NULL;
  }

  // implement alloc stuff here
  
}

arena * arena_reset(arena* Arena) {
  // dealloc all blocks and chunks and leave empty or something
}

arena * realloc(arena* Arena) {
  // TODO :: implement here
}

int main() {
  printf("working");
  arena * thread_buf = arena_init(thread_buf);
}




