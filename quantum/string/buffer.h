// =============================================================================
// <string/buffer.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_F6F3874EE2E04076B023746B99741983
#define H_F6F3874EE2E04076B023746B99741983

// -----------------------------------------------------------------------------

#include "../stdlib/string.h"
#include "../memory/macros.h"

// -----------------------------------------------------------------------------
// Equivalent of `memcpy()`: copy data from the source buffer to
// the destination buffer. Both buffers cannot overlap with each other.
// -----------------------------------------------------------------------------

#if NO(STDLIB)
extern void str_copy (char_t* restrict dst, const char_t* restrict src, size_t size);
#else
static inline void str_copy (char_t* restrict dst, const char_t* restrict src, size_t size)
{
  memcpy ((void* restrict)dst, (const void* restrict)src, size);
}
#endif

// -----------------------------------------------------------------------------
// Equivalent of `memmove()`: copy data from the source address to
// the destination address. Both memory regions can overlap with each other.
// -----------------------------------------------------------------------------
// Copy forwards
#if NO(STDLIB)
extern void str_move_left (char_t* dst, const char_t* src, size_t size);
#else
static inline void str_move_left (char_t* dst, const char_t* src, size_t size)
{
  memmove ((void*)dst, (const void*)src, size);
}
#endif

// -----------------------------------------------------------------------------
// Copy backwards
#if NO(STDLIB)
extern void str_move_right (char_t* dst, const char_t* src, size_t size);
#else
static inline void str_move_right (char_t* dst, const char_t* src, size_t size)
{
  memmove ((void*)dst, (const void*)src, size);
}
#endif

// -----------------------------------------------------------------------------
// Choose the copying direction
#if NO(STDLIB)
extern void str_move (char_t* dst, const char_t* src, size_t size);
#else
static inline void str_move (char_t* dst, const char_t* src, size_t size)
{
  memmove ((void*)dst, (const void*)src, size);
}
#endif

// -----------------------------------------------------------------------------
// Equivalent of `memset()`: fill a buffer with a particular byte value
// -----------------------------------------------------------------------------

#if NO(STDLIB)
extern void str_fill (char_t* buf, size_t size, char_t chr);
#else
static inline void str_fill (char_t* buf, size_t size, char_t chr)
{
  memset ((void*)buf, chr, size);
}
#endif

// -----------------------------------------------------------------------------
// `memzero()`: fill a buffer with the zero byte value
#if NO(STDLIB)
extern void str_zero (char_t* buf, size_t size);
#else
static inline void str_zero (char_t* buf, size_t size)
{
  memset ((void*)buf, 0, size);
}
#endif

// -----------------------------------------------------------------------------
// Equivalent of `memcmp()`: compare the contents of two buffers
// -----------------------------------------------------------------------------
// Returns `true` if the contents of two buffers are identical
// or `false` otherwise
#if NO(STDLIB)
extern bint str_equal (const char_t* buf1, const char_t* buf2, size_t size);
#else
static inline bint str_equal (const char_t* buf1, const char_t* buf2, size_t size)
{
  return memequ ((const void*)buf1, (const void*)buf2, size);
}
#endif

extern bint str_iequal (const char_t* buf1, const char_t* buf2, size_t size);

// -----------------------------------------------------------------------------
// Mimics the exact behavior of `memcmp()`: returns zero if two buffers
// are equal or non-zero value otherwise, which represents the difference
// between the first two mismatching bytes. Not very useful, except for sorting.
#if NO(STDLIB)
extern int str_compare (const char_t* buf1, const char_t* buf2, size_t size);
#else
static inline int str_compare (const char_t* buf1, const char_t* buf2, size_t size)
{
  return memcmp ((const void*)buf1, (const void*)buf2, size);
}
#endif

extern int str_icompare (const char_t* buf1, const char_t* buf2, size_t size);

// -----------------------------------------------------------------------------
// Returns the number of bytes that are equal between two buffers
// starting from the beginning until the first mismatch is encountered
// -----------------------------------------------------------------------------

extern size_t str_prefix (const char_t* buf1, const char_t* buf2, size_t size);
extern size_t str_iprefix (const char_t* buf1, const char_t* buf2, size_t size);

// -----------------------------------------------------------------------------
// Returns the number of bytes that are equal between two buffers
// starting from the ending until the first mismatch is encountered
// -----------------------------------------------------------------------------

extern size_t str_postfix (const char_t* buf1, const char_t* buf2, size_t size);
extern size_t str_ipostfix (const char_t* buf1, const char_t* buf2, size_t size);

// -----------------------------------------------------------------------------
// Returns the total number of bytes that are equal between two buffers
// -----------------------------------------------------------------------------

extern size_t str_parity (const char_t* buf1, const char_t* buf2, size_t size);
extern size_t str_iparity (const char_t* buf1, const char_t* buf2, size_t size);

// -----------------------------------------------------------------------------
// Interchange (reverse) the order of bytes in a buffer
// -----------------------------------------------------------------------------

extern void str_reverse (char_t* buf, size_t size);

// -----------------------------------------------------------------------------
// Exchange the contents of two buffers without using an intermediate buffer.
// If memory regions overlap, then the result is undefined.
// -----------------------------------------------------------------------------

extern void str_swap (char_t* restrict buf1, char_t* restrict buf2, size_t size);

// -----------------------------------------------------------------------------

#endif
