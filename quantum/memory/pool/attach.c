// =============================================================================
// <memory/pool/attach.c>
//
// Dynamic memory pool allocation template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  // Find the pool memory chunk with enough free space
  mem_pool_link_t* curr = pool->curr;

  do
  {
    // Apply the pointer alignment
#if T(ALIGN_DEFAULT)
    byte* ptr = ptr_align_ceil (MEM_POOL_ALIGNMENT, curr->ptr);
#elif T(ALIGN_CUSTOM)
    byte* ptr = ptr_align_ceil (align, curr->ptr);
#else
    byte* ptr = curr->ptr;
#endif

    // See if there's enough free space in this memory chunk
#if MEM(POOL_OVERFLOW_CHECKS)
  #if T(ALIGN_DEFAULT) || T(ALIGN_CUSTOM)
    if (likely ((size_t)(curr->end - curr->ptr) >= ((size_t)(ptr - curr->ptr) + size)))
  #else
    if (likely ((size_t)(curr->end - curr->ptr) >= size))
  #endif
#else
    if (likely ((ptr + size) <= curr->end))
#endif
    {
      curr->ptr = ptr + size;
      pool->rcnt = curr;

      return ptr;
    }

    mem_pool_link_t* link = curr->link;

    // Allow some degree of tolerance towards failed allocations.
    //
    // This prevents one failed allocation of large memory size to
    // mark the memory chunk as filled, even though it might have lots
    // of space left in it for smaller objects.
    //
    // Thus we ensure that each pool memory chunk is utilized to its fullest.
    size_t mod = ++(curr->var.mod);

    if (unlikely (link == null)) break;

    if (unlikely (((size_t)(curr->end - curr->ptr) >> mod) < pool->min))
    {
      // Mark this memory chunk as filled by leaving its chain link behind
      // if it continuously fails to provide allocations
      pool->curr = link;
      pool->heap = curr;
    }

    curr = link;
  }
  while (true);

  // No pool memory chunks are left with enough free space.
  // Allocate the new memory chunk and link it.
  mem_pool_link_t* link = mem_alloc (pool->size);

  if (unlikely (link == null)) return null;

  // Get the actual memory pointer
#if T(ALIGN_DEFAULT)
  byte* mem = mem_pool_chunk_mem (MEM_POOL_ALIGNMENT, link);
#elif T(ALIGN_CUSTOM)
  byte* mem = mem_pool_chunk_mem (align, link);
#else
  byte* mem = (byte*)link + sizeof (mem_pool_link_t);
#endif

#if T(ZERO)
  // Zero out the memory block
  mem_zero (mem, size);
#endif

  // Initialize the new memory chain link
  link->ptr = mem + size;
  link->end = (byte*)link + pool->size;
  link->link = null;
  link->var.mod = 0;

  curr->link = link;
  pool->rcnt = link;

  return mem;
}

// -----------------------------------------------------------------------------

#undef T_ALIGN_DEFAULT
#undef T_ALIGN_CUSTOM
#undef T_ZERO
