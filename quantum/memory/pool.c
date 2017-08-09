// =============================================================================
// <memory/pool.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------
// #define MEM_POOL_OVERFLOW_CHECKS: enable paranoid integral overflow checks.
// -----------------------------------------------------------------------------

#include "../build.h"

#if OS(WIN32)
  #include <Windows.h>
#endif

#include "../core.h"
#include "../memory.h"

#include "pool.h"

// =============================================================================
// Constants
// -----------------------------------------------------------------------------
// Determine the memory pool alignment.
// Must be a power of two and more than one.
#if !MEM(POOL_ALIGNMENT) || (MEM_POOL_ALIGNMENT == 0)
  #if HAVE(C11)
    // C11 finally provides us with actual alignment value used by the standard
    // memory allocators. Took the standards committee long enough.
    #define MEM_POOL_ALIGNMENT alignof (max_align_t)
  #else
    // Pick the safest reasonable value
    #define MEM_POOL_ALIGNMENT 16u
  #endif
#endif

// -----------------------------------------------------------------------------
// Determine the alignment of standard memory allocators used by the system.
// If this value is known at compile time, then some of alignment operations
// can be simplified and the padding added to heap allocations can be reduced.
#if !MEM(POOL_MALLOC_ALIGNMENT) || (MEM_POOL_MALLOC_ALIGNMENT == 0)
  #if HAVE(C11)
    #define MEM_POOL_MALLOC_ALIGNMENT alignof (max_align_t)
  #endif
#endif

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// Determine the symbol visibility.
// This unit can be compiled statically per object file to aid the particular
// task needs or can be compiled and linked as an object file on its own.
#if MEM(POOL_STATIC)
  #define MEM_POOL_EXPORT static
#else
  #define MEM_POOL_EXPORT
#endif

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// Memory pool chunk alignment handling
// -----------------------------------------------------------------------------

static inline size_t mem_pool_chunk_rsrv (size_t align)
{
#if MEM(POOL_MALLOC_ALIGNMENT)
  return size_align_ceil (align, MEM_POOL_MALLOC_ALIGNMENT
  + sizeof (mem_pool_link_t)) - MEM_POOL_MALLOC_ALIGNMENT;
#else
  return align + sizeof (mem_pool_link_t);
#endif
}

static inline byte* mem_pool_chunk_mem (size_t align, const void* ptr)
{
#if MEM(POOL_MALLOC_ALIGNMENT)
  return (byte*)ptr + mem_pool_chunk_rsrv (align);
#else
  return ptr_align_ceil (align, ptr + sizeof (mem_pool_link_t));
#endif
}

// -----------------------------------------------------------------------------
// Memory pool management
// -----------------------------------------------------------------------------
// Create the new memory pool
MEM_POOL_EXPORT
mem_pool_t* mem_pool_create (size_t size, size_t max, size_t min)
{
  // Allocate the memory block with space reserved
  // for the memory pool data structures
  mem_pool_t* pool = mem_alloc (size);

  if (pool == null) return null;

  // Initialize the memory pool
  pool->size = size;

  // Adjust the size of maximum pool allocation
  // that doesn't go directly into heap
  pool->max = min2 (max, size - mem_pool_chunk_rsrv (MEM_POOL_ALIGNMENT));
  pool->min = min;

  // Get the chain links
  mem_pool_link_t* nlink = (mem_pool_link_t*)(pool + 1);
  mem_pool_link_t* chain = nlink + 1;

  pool->rcnt = pool->curr = chain;
  pool->heap = nlink;

  // Initialize the "null" heap link
  nlink->ptr = (byte*)UINTPTR_MAX;
  nlink->end = null;
  nlink->link = chain;
  nlink->var.heap = null;

  // Initialize the first pool link
  chain->ptr = (byte*)(chain + 1);
  chain->end = (byte*)pool + size;
  chain->link = null;
  chain->var.mod = 0;

  return pool;
}

// -----------------------------------------------------------------------------
// Free all memory pool allocations and the pool itself
MEM_POOL_EXPORT
void mem_pool_destroy (mem_pool_t* pool)
{
  mem_pool_link_t* chain = (mem_pool_link_t*)(pool + 1);

  size_t size = pool->size;

  do
  {
    // Free the heap chunk
    if (chain->ptr > chain->end)
    {
      void* ptr = chain->end;

      chain = chain->link;

      mem_free (ptr);
    }

    // Free the pool chunk
    else
    {
      byte* ptr = chain->end - size;

      chain = chain->link;

      mem_free (ptr);
    }
  }
  while (chain != null);
}

// -----------------------------------------------------------------------------
// Reclaim all memory occupied by the pool chains, but don't free
// the individual links themselves, unless they are heap links
MEM_POOL_EXPORT
void mem_pool_reset (mem_pool_t* pool)
{
  mem_pool_link_t* chain = (mem_pool_link_t*)(pool + 1);

  pool->rcnt = pool->curr = chain + 1;
  pool->heap = chain;

  do
  {
    void* ptr = chain->end;

    chain = chain->link;

    mem_free (ptr);
  }
  while (chain->ptr > chain->end);

  // Next link is always the first chain link allocated together
  // with the memory pool itself
  chain->ptr = (byte*)(chain + 1);
  chain->var.mod = 0;

  // Reset the following links
  chain = chain->link;

  while (chain != null)
  {
    if (chain->ptr > chain->end)
    {
      void* ptr = chain->end;

      chain = chain->link;

      mem_free (ptr);
    }
    else
    {
      chain->ptr = (byte*)(chain + 1);
      chain->var.mod = 0;

      chain = chain->link;
    }
  }
}

// -----------------------------------------------------------------------------
// Memory pool allocations
// -----------------------------------------------------------------------------
// Allocate memory from the pool. If there aren't any memory chunks
// with enough free space left, then allocate the new empty chunk
// and get requested memory from there.
static inline void* mem_pool_attach (mem_pool_t* pool, size_t size)
{
  #define T_ALIGN_DEFAULT

  #include "pool/attach.c"
}

// -----------------------------------------------------------------------------
// Attach the large heap memory chunk chain link to the pool
static inline void* mem_pool_attach_heap (mem_pool_t* pool
, mem_pool_link_t* link, const void* ptr)
{
  link->ptr = (byte*)UINTPTR_MAX;
  link->end = (byte*)ptr;
  link->link = pool->heap->link;
  link->var.heap = pool->heap;

  pool->heap->link = link;
  pool->heap = link;
}

// -----------------------------------------------------------------------------
// Allocate the large memory block from heap
MEM_POOL_EXPORT
void* mem_pool_alloc_heap (mem_pool_t* pool, size_t size)
{
  size_t res = mem_pool_chunk_rsrv (MEM_POOL_ALIGNMENT);
  byte* ptr = mem_alloc (res + size);
  if (unlikely (ptr == null)) return null;

#if MEM(POOL_MALLOC_ALIGNMENT)
  byte* mem = ptr + res;
#else
  byte* mem = ptr_align_ceil (MEM_POOL_ALIGNMENT, ptr
  + sizeof (mem_pool_link_t));
#endif

  mem_pool_link_t* link = (mem_pool_link_t*)mem - 1;
  mem_pool_attach_heap (pool, link, ptr);

  return mem;
}

// -----------------------------------------------------------------------------
// Allocate the small or medium memory block from the current pool chunk,
// or allocate directly from heap if requested size is too big
MEM_POOL_EXPORT
void* mem_pool_alloc (mem_pool_t* pool, size_t size)
{
  if (likely (size <= pool->max)) return mem_pool_attach (pool, size);

  return mem_pool_alloc_heap (pool, size);
}

// -----------------------------------------------------------------------------
// Allocate the object with flexible member in single allocation so that
// the flexible part can be resized independently
MEM_POOL_EXPORT
void* mem_pool_alloc_flex (mem_pool_t* pool, size_t objsz, size_t bufsz)
{
  bufsz += objsz;

  if (likely (bufsz > pool->max)) return null;

  return mem_pool_attach (pool, bufsz);
}

// -----------------------------------------------------------------------------
// `mem_pool_alloc_heap()` that zeroes out the allocated memory block
MEM_POOL_EXPORT
void* mem_pool_alloc_heap_zero (mem_pool_t* pool, size_t size)
{
  size_t res = mem_pool_chunk_rsrv (MEM_POOL_ALIGNMENT);
  byte* ptr = mem_alloc_zero (res + size);
  if (unlikely (ptr == null)) return null;

#if MEM(POOL_MALLOC_ALIGNMENT)
  byte* mem = ptr + res;
#else
  byte* mem = ptr_align_ceil (MEM_POOL_ALIGNMENT, ptr
  + sizeof (mem_pool_link_t));
#endif

  mem_pool_link_t* link = (mem_pool_link_t*)mem - 1;
  mem_pool_attach_heap (pool, link, ptr);

  return mem;
}

// -----------------------------------------------------------------------------
// `mem_pool_alloc()` that zeroes out the allocated memory block
MEM_POOL_EXPORT
void* mem_pool_alloc_zero (mem_pool_t* pool, size_t size)
{
  if (likely (size <= pool->max))
  {
    #define T_ALIGN_DEFAULT
    #define T_ZERO

    #include "pool/attach.c"
  }

  return mem_pool_alloc_heap_zero (pool, size);
}

// -----------------------------------------------------------------------------
// `mem_pool_alloc_heap()` with stricter alignment
MEM_POOL_EXPORT
void* mem_pool_alloc_heap_align (mem_pool_t* pool, size_t align, size_t size)
{
  size_t res = mem_pool_chunk_rsrv (align);
  byte* ptr = mem_alloc (res + size);
  if (unlikely (ptr == null)) return null;

#if MEM(POOL_MALLOC_ALIGNMENT)
  byte* mem = ptr + res;
#else
  byte* mem = ptr_align_ceil (align, ptr + sizeof (mem_pool_link_t));
#endif

  mem_pool_link_t* link = (mem_pool_link_t*)mem - 1;
  mem_pool_attach_heap (pool, link, ptr);

  return mem;
}

// -----------------------------------------------------------------------------
// `mem_pool_alloc()` with stricter alignment
MEM_POOL_EXPORT
void* mem_pool_alloc_align (mem_pool_t* pool, size_t align, size_t size)
{
  if (likely (align + size <= pool->max))
  {
    #define T_ALIGN_CUSTOM

    #include "pool/attach.c"
  }

#if MEM(POOL_MALLOC_ALIGNMENT)
  align = (align < MEM_POOL_MALLOC_ALIGNMENT) ? MEM_POOL_MALLOC_ALIGNMENT : align;
#else
  align = (align < sizeof (void_t)) ? sizeof (void_t) : align;
#endif

  return mem_pool_alloc_heap_align (pool, align, size);
}

// -----------------------------------------------------------------------------
// `mem_pool_alloc_heap()` without alignment at all (good for short strings)
MEM_POOL_EXPORT
void* mem_pool_alloc_heap_raw (mem_pool_t* pool, size_t size)
{
  mem_pool_link_t* link = mem_alloc (sizeof (mem_pool_link_t) + size);
  if (unlikely (link == null)) return null;

  byte* mem = (byte*)(link + 1);
  mem_pool_attach_heap (pool, link, link);

  return mem;
}

// -----------------------------------------------------------------------------
// `mem_pool_alloc()` without alignment at all (good for short strings)
MEM_POOL_EXPORT
void* mem_pool_alloc_raw (mem_pool_t* pool, size_t size)
{
  if (likely (size <= pool->max))
  {
    #include "pool/attach.c"
  }

  return mem_pool_alloc_heap_raw (pool, size);
}

// -----------------------------------------------------------------------------
// Free the heap allocation
MEM_POOL_EXPORT
void mem_pool_free_heap (mem_pool_t* pool, void* mem)
{
  if (mem == null) return;
  mem_pool_link_t* link = (mem_pool_link_t*)mem - 1;
  mem_free (link->end);
}

// -----------------------------------------------------------------------------
// Free the pool allocation
MEM_POOL_EXPORT
void mem_pool_free (mem_pool_t* pool, void* mem, size_t size)
{
  mem_pool_link_t* rcnt = pool->rcnt;

  if (likely (mem == (rcnt->ptr - size)))
  {
    rcnt->ptr -= size;
    rcnt->var.mod = 0;

    return;
  }

  if (likely (size <= pool->max)) return;

  mem_pool_free_heap (pool, mem);
}

// -----------------------------------------------------------------------------
// Resize the heap allocation
MEM_POOL_EXPORT
void* mem_pool_realloc_heap (mem_pool_t* pool, void* mem, size_t size)
{
  mem_pool_link_t* link = (mem_pool_link_t*)mem - 1;

  byte* old = link->end;
  size_t res = (size_t)((byte*)mem - old);
  byte* ptr = mem_realloc (old, res + size);

  if (likely (ptr != null))
  {
    if (unlikely (ptr != old))
    {
      link = (mem_pool_link_t*)(ptr + res) - 1;

      link->end = ptr;
      link->var.heap->link = link;
    }

    return ptr + res;
  }

  return null;
}

// -----------------------------------------------------------------------------
// Resize the pool allocation
MEM_POOL_EXPORT
void* mem_pool_realloc (mem_pool_t* pool, void* mem, size_t oldsz, size_t newsz)
{
  if (unlikely (mem == null)) return mem_pool_alloc (pool, newsz);

  size_t max = pool->max;
  mem_pool_link_t* rcnt = pool->rcnt;
  byte* p = rcnt->ptr - oldsz;

  if (likely (mem == p))
  {
    if (likely (newsz <= max))
    {
      if (likely ((size_t)(rcnt->end - p) >= newsz))
      {
        rcnt->ptr = p + newsz;
        return p;
      }

      byte* ptr = mem_pool_attach (pool, newsz);

      if (unlikely (ptr == null)) return null;

      rcnt->ptr = p;
      rcnt->var.mod = 0;

      mem_copy (ptr, p, oldsz);

      return ptr;
    }

    byte* ptr = mem_pool_alloc_heap (pool, newsz);

    if (unlikely (ptr == null)) return null;

    rcnt->ptr = p;
    rcnt->var.mod = 0;

    mem_copy (ptr, p, oldsz);

    return ptr;
  }

  if (likely (newsz <= max))
  {
    byte* ptr = mem_pool_attach (pool, newsz);

    if (unlikely (ptr == null)) return null;

    mem_copy (ptr, mem, oldsz);

    if (unlikely (oldsz > max)) mem_pool_free_heap (pool, mem);

    return ptr;
  }

  if (likely (oldsz <= max))
  {
    byte* ptr = mem_pool_alloc_heap (pool, newsz);

    if (unlikely (ptr == null)) return null;

    mem_copy (ptr, mem, oldsz);

    return ptr;
  }

  return mem_pool_realloc_heap (pool, mem, newsz);
}
