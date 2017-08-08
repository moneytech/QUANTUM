// =============================================================================
// <memory/allocate.h>
//
// Memory allocation functions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_CD8AD9DD92AF46978E90B8B3570D3590
#define H_CD8AD9DD92AF46978E90B8B3570D3590

// -----------------------------------------------------------------------------

#include "../stdlib/stdlib.h"

// -----------------------------------------------------------------------------

static inline void* mem_alloc (size_t size)
{
  return malloc (size);
}

static inline void* mem_alloc_zero (size_t size)
{
  return calloc (1u, size);
}

static inline void* mem_alloc_align (size_t align, size_t size)
{
#if OS(WIN32)
  return aligned_malloc (size, align);
#elif HAVE(C11)
  return aligned_alloc (align, size);
#else
  void* ptr;

  if ((errno = posix_memalign (&ptr, align, size)) != EOK) return null;

  return ptr;
#endif
}

#define mem_alloc_stack(size) alloca (size)

// -----------------------------------------------------------------------------

static inline void* mem_realloc (void* mem, size_t size)
{
  return realloc (mem, size);
}

// -----------------------------------------------------------------------------

static inline void mem_free (void* mem)
{
  free (mem);
}

static inline void mem_free_align (void* mem)
{
#if OS(WIN32)
  aligned_free (mem);
#else
  free (mem);
#endif
}

// -----------------------------------------------------------------------------

#endif
