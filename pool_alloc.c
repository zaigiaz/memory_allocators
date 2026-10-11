#include <stdio.h>
#include "declares.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// for testing
#define pool_default_size 1024

// size fits inside u16
#define MAX_SIZE 64000
#define BITMAP_BYTES ((BITMAP_BITS + 7) / 8)

// memory pool which has area of bytes, stride (size of object), slots (the amount of objects in the pool)
// and a id to the last used slot, once the (last-used-slot == max_slots) then we refer to the bitmap to find new space
typedef struct {
  u8 * area;
  u8 * bmap;
  size_t stride;
  size_t slots;
} pool;

// bitset helpers (safe to ignore for purposes of learning the main logic)
static bool bit_get(const u8 *bmap, u16 i) { return (bmap[i / 8] & (u8)(1u << (i % 8))) != 0; }
static void bit_set(u8 *bmap, size_t i) { bmap[i / 8] |= (u8)(1u << (i % 8)); }
static void bit_clear(u8 *bmap, size_t i) { bmap[i / 8] &= (u8)~(1u << (i % 8)); }


// find the first free index in bmap
size_t find_free_index(u8* bmap, u16 slots) {
  for (u16 i = 0; i < slots; i++) {
    if (!bit_get(bmap, i)) {
      return i;
    }
  }
  return slots;
}

// create a pool
void pool_init(pool* p, size_t stride, size_t slots) {
  if (stride == 0 || slots <= 1) {
    fprintf(stderr, "please give correct size for parameters to pool (params > 0)\n");
  }

  if(slots > MAX_SIZE) { fprintf(stderr, "pool size is too big, make it smaller plz"); }

  p->area = malloc((stride*slots));
  if(p->area == NULL) {
    free(p->area);
    fprintf(stderr, "failed to allocate region for pool\n");
  }

  size_t bmap_bytes = slots / 8 + (slots % 8 != 0);
  p->bmap = calloc(bmap_bytes, (stride*slots));
  if(p->bmap == NULL) { 
    free(p->bmap);
    fprintf(stderr, "failed to alloc the bitmap in the pool\n");
 }

  p->stride = stride;
  p->slots = slots;  
}


// adds an item into the pool
size_t pool_alloc(pool *p, const void* obj) {
  u16 free_idx = find_free_index(p->bmap, p->slots);

  if(free_idx >= p->slots) {
    fprintf(stderr, "pool is full, implement error handling later\n");
  }

  if(sizeof(obj) != p->stride) {
    fprintf(stderr, "object is of different type than the pool slot\n");
  }

  memcpy(p, obj, p->stride);
  return free_idx;
}


// remove an item from the pool
void pool_remove(pool *p, u16 idx) {
  printf("implement here");
}


// clear the entire pool
void pool_clear(pool * p) {

  // clear the pool and the bitmap
  memset(p->area, 0, p->stride);
  memset(p->bmap, 0, sizeof(u8));
}


// frees all the memory in the pool
void pool_destroy(pool* p) {

  free(p->area);
  free(p->bmap);
}

int main() {
  pool mypool;
  pool_init(&mypool, sizeof(int), pool_default_size);
  printf("pool has %zu slots and object size %zu", mypool.slots, mypool.stride);
  return 0;
}
