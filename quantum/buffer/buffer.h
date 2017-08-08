// =============================================================================
// <buffer/buffer.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_E9793A9FA2E84903949A5F56A0B30521
#define H_E9793A9FA2E84903949A5F56A0B30521

// -----------------------------------------------------------------------------

#include "../string/buffer.h"

// -----------------------------------------------------------------------------

static inline void buf_copy (byte* restrict dst, const byte* restrict src, size_t size)
{
  str_copy (dst, src, size);
}

// -----------------------------------------------------------------------------

static inline void buf_move_left (byte* dst, const byte* src, size_t size)
{
  str_move_left (dst, src, size);
}

static inline void buf_move_right (byte* dst, const byte* src, size_t size)
{
  str_move_right (dst, src, size);
}

static inline void buf_move (byte* dst, const byte* src, size_t size)
{
  str_move (dst, src, size);
}

// -----------------------------------------------------------------------------

static inline void buf_fill (byte* buf, size_t size, byte val)
{
  str_fill (buf, size, val);
}

static inline void buf_zero (byte* buf, size_t size)
{
  str_zero (buf, size);
}

// -----------------------------------------------------------------------------

static inline bint buf_equal (const byte* buf1, const byte* buf2, size_t size)
{
  return str_equal (buf1, buf2, size);
}

static inline int buf_compare (const byte* buf1, const byte* buf2, size_t size)
{
  return str_compare (buf1, buf2, size);
}

// -----------------------------------------------------------------------------

static inline size_t buf_prefix (const byte* buf1, const byte* buf2, size_t size)
{
  return str_prefix (buf1, buf2, size);
}

static inline size_t buf_postfix (const byte* buf1, const byte* buf2, size_t size)
{
  return str_postfix (buf1, buf2, size);
}

static inline size_t buf_parity (const byte* buf1, const byte* buf2, size_t size)
{
  return str_parity (buf1, buf2, size);
}

// -----------------------------------------------------------------------------

static inline void buf_bswap (byte* buf, size_t size)
{
  str_reverse (buf, size);
}

// -----------------------------------------------------------------------------

static inline void buf_swap (byte* restrict buf1, byte* restrict buf2, size_t size)
{
  str_swap (buf1, buf2, size);
}

// -----------------------------------------------------------------------------

#endif
