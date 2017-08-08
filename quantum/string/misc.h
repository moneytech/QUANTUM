// =============================================================================
// <string/misc.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_C700DD40F737468B92C4BA44A20BBD73
#define H_C700DD40F737468B92C4BA44A20BBD73

// -----------------------------------------------------------------------------

#include "../core.h"
#include "../character.h"
#include "../memory/allocate.h"

#include "buffer.h"

// -----------------------------------------------------------------------------
// Trim whitespace at the start and at the end of a buffer
// -----------------------------------------------------------------------------
// Trim from left
static inline size_t str_ltrim (const char_t* buf, size_t len)
{
  #define t_chr_is_wspace chr_is_wspace

  #include "misc/ltrim/generic.c"
}

// -----------------------------------------------------------------------------
// Trim from right
static inline size_t str_rtrim (const char_t* buf, size_t len)
{
  #define t_chr_is_wspace chr_is_wspace

  #include "misc/rtrim/generic.c"
}

// -----------------------------------------------------------------------------
// Trim from both left and right and slide the data to the left in a buffer
static inline size_t str_trim (char_t* buf, size_t len)
{
  #define t_str_ltrim str_ltrim
  #define t_str_rtrim str_rtrim
  #define t_str_move_left str_move_left

  #include "misc/trim/generic.c"
}

// -----------------------------------------------------------------------------
// Duplicate a buffer
// -----------------------------------------------------------------------------

static inline char_t* str_clone (const char_t* buf, size_t len)
{
#if NO(STDLIB) || !HAVE(MEMDUP)
  #define t_mem_alloc mem_alloc
  #define t_str_copy str_copy

  #include "misc/clone/generic.c"
#else
  return memdup ((const void*)buf, len);
#endif
}

// -----------------------------------------------------------------------------

#endif
