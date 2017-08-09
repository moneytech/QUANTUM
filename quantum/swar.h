// =============================================================================
// <swar.h>
//
// Assorted SWAR tricks.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_D21539EDCF56414B8F9E10DF6DAFE219
#define H_D21539EDCF56414B8F9E10DF6DAFE219

// -----------------------------------------------------------------------------

#if HAVE(INT16)
static inline bint swar_has_zero2 (u16 v)
{
  return (((v - 0x0101u) & ~v & 0x8080u) != 0);
}
#endif

#if HAVE(INT32)
static inline bint swar_has_zero4 (u32 v)
{
  return (((v - 0x01010101u) & ~v & 0x80808080u) != 0);
}
#endif

#if HAVE(INT64)
static inline bint swar_has_zero8 (u64 v)
{
  return (((v - 0x0101010101010101u) & ~v & 0x8080808080808080u) != 0);
}
#endif

// -----------------------------------------------------------------------------

#endif
