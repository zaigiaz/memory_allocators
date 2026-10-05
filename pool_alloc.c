#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "declares.h"

// TODO :: pool_alloc
// TODO :: handles and index-based free and search?

#define pool_default_size 2048

typedef struct region {
  u8 area[pool_default_size];
  size_t used;
  struct region * next;
} region;

typedef struct {
  region *start, *end;
  u16 regions_amount;
} pool;

// allocate a 2kb region
region * region_create() {
  region* new_region;
  new_region = malloc(sizeof *new_region);
  if(new_region == NULL) { return NULL; }
    
  memset(new_region->area, 0, pool_default_size); 
  new_region->used = 0;
  new_region->next = NULL;

  return new_region;
}

// create a pool
pool pool_init() {

  pool newpool = {0};
  region* new_region = region_create();
  if(new_region == NULL) { return newpool; }

  newpool.start = new_region;
  newpool.end = new_region;
  newpool.regions_amount = 1;
  
  return newpool;
}

// add page to the pool
pool* pool_add(pool* p) {
  region* new_region = region_create();

  if(new_region == NULL) { return p; }

  // the pool.end is the tail pointer that points inwards, then the next
  p->end->next = new_region;
  p->end = new_region;
  p->regions_amount++;

  return p;
}

// adds an item into the pool
void pool_alloc(pool *p, size_t size) {
  printf("implementation here");
}

// free each element in the list
void pool_clear(pool * p) {  
  if (p == NULL) { return; }

  region *current = p->start;
  while (current != NULL) {
    region *next = current->next;
    free(current);
    current = next;
  }

  p->start = NULL;
  p->end = NULL;
  p->regions_amount = 0;
}

int main() {
  printf("hello\n");
  pool pool_ui = pool_init();
  pool_add(&pool_ui);
  pool_add(&pool_ui);
  // pool_clear(&pool_ui);
  printf("pool has %d regions in the linked list", pool_ui.regions_amount);
  return 0;
}
