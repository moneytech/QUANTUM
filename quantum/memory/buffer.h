// =============================================================================
// <memory/buffer.h>
//
// Memory buffer functions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_B760B6D496E14EECA5C64890B0A3B237
#define H_B760B6D496E14EECA5C64890B0A3B237

// -----------------------------------------------------------------------------

#include "../buffer/buffer.h"

// -----------------------------------------------------------------------------
// Casts are for C++: so that it can consume the header
// -----------------------------------------------------------------------------

static inline void mem_copy (void* restrict dst, const void* restrict src, size_t size)
{
  buf_copy ((byte* restrict)dst, (const byte* restrict)src, size);
}

// -----------------------------------------------------------------------------

static inline void mem_move_left (void* dst, const void* src, size_t size)
{
  buf_move_left ((byte*)dst, (const byte*)src, size);
}

static inline void mem_move_right (void* dst, const void* src, size_t size)
{
  buf_move_right ((byte*)dst, (const byte*)src, size);
}

static inline void mem_move (void* dst, const void* src, size_t size)
{
  buf_move ((byte*)dst, (const byte*)src, size);
}

// -----------------------------------------------------------------------------

static inline void mem_zero (void* mem, size_t size)
{
  buf_zero ((byte*)mem, size);
}

// -----------------------------------------------------------------------------

static inline bint mem_equal (const void* mem1, const void* mem2, size_t size)
{
  return buf_equal ((const byte*)mem1, (const byte*)mem2, size);
}

// -----------------------------------------------------------------------------

#endif
