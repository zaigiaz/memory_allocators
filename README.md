# Overview

Here is some basic implementations of different allocators and allocation strategies.
This is primarily for learning, use the code at your own risk.

One of the main problems of memory allocation is tracking both used and freed memory, and figuring out where you can allocate to without needing
to do expensive operations like extra checks, tracking metadata, etc. 

Arenas can be seen as resize-able buffers that we can throw anything onto, but we can only de-allocate the entire arena at once.

Pool-Allocators are either a linked-list or array of fixed-size blocks that we can store/use and deallocate a block of that memory. Usually sized to a page-size of 4096 bytes

Slab-Allocators keep caches of fixed-object size's that we can allocate onto or deallocate.

## Roadmap

- Arena
- Pool (in-progress)
- Slab
- Buddy Allocator

## Papers and References

- To be filled
