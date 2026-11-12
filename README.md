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
linked-list of regions. Where we create a new node after a region is full and can't contain another object.

## Pool Allocators

Pool-Allocators are fixed-size blocks where we can store/use and deallocate a block of that memory.
Pool-Allocators allow you to refer to specific objects in the pool if you are using a array-backed design, and we could also combine this with a bitmap index
to see if any slot is currently occupied in the pool. Used for single object type. Can also use this with SoA and AoSoA for fast accessing of heap-allocated objects in the program.
You always want to have a constant slot-size in a pool so there is no memory fragmentation

## Slab Allocators

Slab-Allocators keep caches of fixed-object size's that we can allocate onto or deallocate. The Linux Kernel uses a slab-allocator. This reduces the amount of malloc()/free() that might
occur and keeps recent objects in a cache for fast reference. This is useful for large projects where objects can be passed around largely different parts of the program with variable lifetimes.

## Roadmap

- Arena Allocator
- Slab Allocator
- Buddy Allocator (potentially in future)

- Extra techniques for memory allocators (error-handling)

## Papers and References

- Research Papers in the papers/ folder
- Best Write-up https://www.rastergrid.com/blog/sw-eng/2021/03/custom-memory-allocators/
- https://github.com/mtrebi/memory-allocators
- https://os.phil-opp.com/allocator-designs/
- Great writeup about one of the papers https://www.cs.cornell.edu/courses/cs6120/2019fa/blog/custom-alloc/
- Immix garbage collector https://www.cs.cornell.edu/courses/cs6120/2019fa/blog/immix/
- Go's GreenTea Garbage-Collector https://go.dev/blog/greenteagc | https://github.com/golang/go/issues/73581
- Two-Level Segregated Fit Allocator https://github.com/mattconte/tlsf
- rpmalloc allocator from Epic-Games https://github.com/mjansson/rpmalloc 
- Memory Fragmentation Formula https://asawicki.info/news_1757_a_metric_for_memory_fragmentation
- Review of Flat_Pool by Jonathan Blow https://www.youtube.com/watch?v=IHat13NUqLo
- tslf review https://ricefields.me/2024/04/20/tlsf-allocator.html






