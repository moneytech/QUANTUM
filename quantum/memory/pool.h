// =============================================================================
// <memory/pool.h>
//
// Dynamic memory pool.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_FF9BCB9D320E4E3AB368B07B89AE9AFA
#define H_FF9BCB9D320E4E3AB368B07B89AE9AFA

// =============================================================================
// Types
// -----------------------------------------------------------------------------
// There are two kinds of memory chunks used in the pool,
// which are linked together in one chain.
//
// The first, and the most obvious one, is referred to as pool memory chunk.
//
// Pool memory chunks have a constant size, which is specified by the caller
// when the memory pool is created, and they are used to store relatively
// small or medium memory allocations.
//
// The pool memory chunk size is usually a multiple of memory page size.
//
// The second kind is referred to as heap memory chunk.
//
// Heap memory chunks have a variable size, which depends on the individual
// memory allocation size, and are used to store only large memory allocations,
// which don't fit into regular memory pool chunks.
//
// Additionally, any memory allocation larger than certain size is
// automatically turned into heap memory chunk. This size can be specified
// by the caller during the memory pool creation.
//
// Heap memory chunks are always allocated directly from the heap,
// can be resized (reallocated) independently from each other, and are always
// considered full because they aren't used for any other (small or medium)
// memory allocations. Each heap memory chunk is responsible for its own
// particular large memory allocation only.
// -----------------------------------------------------------------------------

typedef struct mem_pool_link_s mem_pool_link_t;

struct mem_pool_link_s
{
  // Next available memory address
  byte* ptr;
  // Memory chunk end address
  byte* end;
  // Next pool chain link
  mem_pool_link_t* link;
  // The value of this field depends on what kind of chain link it is
  union
  {
    // For heap memory chain links: previous heap memory chain link address
    mem_pool_link_t* heap;
    // For pool memory chain links: minimum allocation size tolerance modifier
    uintptr_t mod;
  } var;
};

typedef struct mem_pool_s aligned(CPU_CACHE_LINE_SIZE) mem_pool_t;

struct mem_pool_s
{
  // Reserved
  void* ctx;

  // Pool memory chunk size
  size_t size;
  // Maximum memory pool allocation size which doesn't go directly into heap
  size_t max;
  // Minimum pool allocation size hint used to advance the current chain link
  size_t min;

  // Current chain link from which all pool memory allocations are attempted
  // to be made by default. Not necessarily always the top-most chain link,
  // but is always close to the top.
  mem_pool_link_t* curr;
  // Chain link from which the most recent pool allocation has been made.
  // Used to undo the last memory allocation if it didn't go directly
  // into heap.
  mem_pool_link_t* rcnt;
  // Chain link after which all subsequent direct heap memory allocation chain
  // links are placed. As close to the current chain link as possible
  // to aid the CPU cache, but always comes before it in order not
  // to interfere with regular allocations.
  mem_pool_link_t* heap;
};

// =============================================================================
// Functions
// -----------------------------------------------------------------------------

#if !MEM(POOL_STATIC)
extern mem_pool_t* mem_pool_create (size_t size, size_t max, size_t min);
extern void mem_pool_reset (mem_pool_t* pool);
extern void mem_pool_destroy (mem_pool_t* pool);

extern void* mem_pool_alloc (mem_pool_t* pool, size_t size);
extern void* mem_pool_alloc_heap (mem_pool_t* pool, size_t size);

extern void* mem_pool_alloc_flex (mem_pool_t* pool, size_t objsz, size_t bufsz);

extern void* mem_pool_alloc_zero (mem_pool_t* pool, size_t size);
extern void* mem_pool_alloc_heap_zero (mem_pool_t* pool, size_t size);

extern void* mem_pool_alloc_align (mem_pool_t* pool, size_t align, size_t size);
extern void* mem_pool_alloc_heap_align (mem_pool_t* pool, size_t align, size_t size);

extern void* mem_pool_alloc_raw (mem_pool_t* pool, size_t size);
extern void* mem_pool_alloc_heap_raw (mem_pool_t* pool, size_t size);

extern void* mem_pool_realloc (mem_pool_t* pool, void* mem, size_t oldsz, size_t newsz);
extern void* mem_pool_realloc_heap (mem_pool_t* pool, void* mem, size_t size);

extern void mem_pool_free (mem_pool_t* pool, void* mem, size_t size);
extern void mem_pool_free_heap (mem_pool_t* pool, void* mem);
#endif // !MEM(POOL_STATIC)

// -----------------------------------------------------------------------------

#endif
