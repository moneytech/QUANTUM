// =============================================================================
// <memory/misc.h>
//
// Miscellaneous memory functions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A062C55687E44FEE9F6BB90DF75DFA01
#define H_A062C55687E44FEE9F6BB90DF75DFA01

// -----------------------------------------------------------------------------

#include "../buffer/misc.h"

// -----------------------------------------------------------------------------
// Casts are for C++: so that it can consume the header
// -----------------------------------------------------------------------------

static inline void* mem_clone (const void* mem, size_t size)
{
  return buf_clone ((const byte*)mem, size);
}

// -----------------------------------------------------------------------------

#endif
