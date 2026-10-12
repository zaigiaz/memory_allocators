#include <stdio.h>
#include "declares.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// for testing
#define pool_default_size 1024

// size fits inside u16, in worse case we use 500 bytes for bmap
// max-size case is 12.5KB for 64,0000 objects where each object is 200 bytes large
#define MAX_SIZE 64000

// memory pool which has area of bytes, stride (size of object), slots (the amount of objects in the pool)
// we refer to the bitmap to find new space
typedef struct {
  u8 * area;
  u8 * bmap;
  size_t stride;
  size_t slots;
} pool;

// object for showcase of api
typedef struct {
  char name[10];
  u8 age;
} foo_obj;

// bitset helpers (safe to ignore for purposes of learning the main logic)
static bool bit_get(const u8 *bmap, u16 i) { return (bmap[i / 8] & (u8)(1u << (i % 8))) != 0; }
static void bit_set(u8 *bmap, size_t i) { bmap[i / 8] |= (u8)(1u << (i % 8)); }
static void bit_clear(u8 *bmap, size_t i) { bmap[i / 8] &= (u8)~(1u << (i % 8)); }

// find the first free index in bmap
u16 find_free_index(u8* bmap, u16 slots) {
  for (u16 i = 0; i < slots; i++) {
    if (!bit_get(bmap, i)) {
      return i;
    }
  }
  return slots;
}

// create a pool
pool* pool_init(pool* p, size_t stride, size_t slots) {
  if (stride == 0 || slots <= 1) {
    fprintf(stderr, "ERROR: please give correct size for parameters to pool (params > 0)\n");
  }

  if(slots > MAX_SIZE) { fprintf(stderr, "ERROR: pool size is too big, make it smaller plz"); }

  p->area = malloc((stride*slots));
  if(p->area == NULL) {
    free(p->area);
    fprintf(stderr, "ERROR: failed to allocate region for pool\n");
  }

  size_t bmap_bytes = slots / 8 + (slots % 8 != 0);
  p->bmap = calloc(bmap_bytes, 1);
  if(p->bmap == NULL) { 
    free(p->bmap);
    fprintf(stderr, "ERROR: failed to alloc the bitmap in the pool\n");
  }

  p->stride = stride;
  p->slots = slots;  
}


// adds an item into the pool
u16 pool_alloc(pool *p, const void* obj) {
  u16 free_idx = find_free_index(p->bmap, p->slots);

  if(free_idx >= p->slots) {
    fprintf(stderr, "ERROR: pool is full, implement error handling later\n");
  }

  // take the pool, and get the base + first free slot + slot size and insert
  u8 * index = p->area + (size_t)free_idx * p->stride;
  memcpy(index, obj, p->stride);
  bit_set(p->bmap, free_idx);
  return free_idx;
}


// remove an item from the pool
void pool_remove(pool *p, u16 idx) {
  if (p == NULL || idx >= p->slots || !bit_get(p->bmap, idx)) {
    return;
  }

  bit_clear(p->bmap, idx);
  u8 * index = p->area + (size_t)idx * p->stride;
  memset(index, 0, p->stride);
}

// clear the entire pool
void pool_clear(pool * p) {

  if (p == NULL) {
    return;
  }
  
  // clear the pool and the bitmap
  memset(p->area, 0, p->stride * p->slots);
  size_t bmap_bytes = p->slots / 8 + (p->slots % 8 != 0);
  memset(p->bmap, 0, bmap_bytes);
}

// frees all the memory in the pool
void pool_destroy(pool* p) {

  free(p->area);
  free(p->bmap);

  p->area = NULL;
  p->bmap = NULL;
  p->stride = 0;
  p->slots = 0;
}

// get the item at index
void *pool_at(pool *p, size_t idx) {
  if (p == NULL || idx >= p->slots || !bit_get(p->bmap, (u16)idx)) {
    return NULL;
  }
  return p->area + idx * p->stride;
}

int main() {
  pool mypool;
  pool_init(&mypool, sizeof(int), pool_default_size);
 
  printf("pool has %zu slots and object size %zu", mypool.slots, mypool.stride);

  // NOTE :: THIS IS COOL!!!! (only works for u8 data however)
  printf("\nhere is some basic data %u\n", mypool.area[3]);

  // first example with int
  int x = 1024;
  u16 idx = pool_alloc(&mypool, &x);
  int * data = pool_at(&mypool, idx);
  printf("here is the data from the pool %d", *data);

  // now with foo objects
  pool foo_pool;
  pool_init(&foo_pool, sizeof(foo_obj), 20);
  printf("\nsize of foo object is : %zu", sizeof(foo_obj));

  foo_obj rec1 = { .name="John", .age=12 };
  u16 rec1_idx = pool_alloc(&foo_pool, &rec1);
  foo_obj * f_data = pool_at(&foo_pool, rec1_idx);
  printf("\nhere is foo-object name '%s', and age: %u", f_data->name, f_data->age);

  pool_destroy(&mypool);
  pool_destroy(&foo_pool);
  return 0;
}
