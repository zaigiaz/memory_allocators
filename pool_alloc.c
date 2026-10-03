#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "declares.h"

#define pool_default_size 2048

typedef struct region {
  u8 * area;
  size_t used;
  size_t capacity;
  struct region * next;
} region;

typedef struct {
  region *start, *end;
  u16 regions_amount;
} pool;

// allocate a 2kb region
region * region_create(size_t capacity) {

  if(capacity <= 0) { capacity = pool_default_size; }

  region* new_region;
  new_region = malloc(sizeof *new_region);
  if(new_region == NULL) { return NULL; }
    
  new_region->area = malloc(capacity);
  new_region->capacity = capacity;
  new_region->used = 0;
  new_region->next = NULL;
}

pool pool_init() {

  pool newpool = {0};
  region* new_region = region_create(0);
  if(new_region == NULL) { return newpool; }

  newpool.start = new_region;
  newpool.end = new_region;
  newpool.regions_amount = 1;
  
  return newpool;
}

// add page to the pool
pool* pool_add(pool* p, size_t allocated) {
  if(p == NULL || allocated == 0) { return NULL; }

  size_t size = pool_default_size;
  if (allocated > size) {
    size = allocated;
  }

  region* new_region = region_create(size);

  if(new_region == NULL) { return p; }

  // TODO: fix this logic
  // the pool.end is the tail pointer that points inwards, use that
  p->start->next = new_region;
  
  return p;
}

// free each element in the list
void pool_free_all(pool p) {
  // traverse list and free each element
}

int main() {
  printf("hello\n");
  pool pool_ui = pool_init();
  printf("pool has %d regions in the linked list", pool_ui.regions_amount + 1);
  return 0;
}
