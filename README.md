# Overview

Here is some basic implementations of different allocators and allocation strategies.
This is primarily for learning, use the code at your own risk. 

This is oriented to programmers looking at allocation strategies for 'user-space' programs. Kernel-space programs or very low-level memory-allocators
have other larger classes of problems to worry about like fragmentation and correct allocation.

One of the main problems of memory allocation is tracking both used and freed memory, and figuring out where you can allocate to without needing
to do expensive operations like extra checks, tracking metadata, etc. 

## Arenas (linear alloc, bump alloc)

Arenas can be seen as resize-able buffers that we can throw anything onto, but we can only de-allocate the entire arena at once.
They can be implemented as a single pointer (where there is some complicated byte-alignment logic involved) or we can implement it as a 
linked-list of regions. Where we create a new node after a region is full and cant contain another object.

## Pool Allocators

Pool-Allocators are either a linked-list or array of fixed-size blocks that we can store/use and deallocate a block of that memory.
Pool-Allocators allow you to refer to specific objects in the pool if you are using a array-backed design, and we could also combine this with a bitmap index
to see if any slot is currently occupied in the pool. Used for single object type.

## Slab Allocators

Slab-Allocators keep caches of fixed-object size's that we can allocate onto or deallocate. The Linux Kernel uses a slab-allocator. This reduces the amount of malloc()/free() that might
occur and keeps recent objects in a cache for fast reference.

## Roadmap

- Arena
- Pool (in-progress)
- Slab
- Buddy Allocator (potentially in future)

## Papers and References

- https://github.com/mtrebi/memory-allocators
- https://os.phil-opp.com/allocator-designs/
- Research Papers in the papers/ folder

