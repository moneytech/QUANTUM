// =============================================================================
// <buffer/search.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_D1BF1C92FBA341E89128F18A4BD60E97
#define H_D1BF1C92FBA341E89128F18A4BD60E97

// -----------------------------------------------------------------------------

#include "../string/types.h"
#include "../string/search.h"

// -----------------------------------------------------------------------------
// Byte
// -----------------------------------------------------------------------------

static inline byte* buf_find_byte (const byte* buf, size_t size, byte val)
{
  return str_find_chr (buf, size, val);
}

static inline byte* buf_rfind_byte (const byte* buf, size_t size, byte val)
{
  return str_rfind_chr (buf, size, val);
}

// -----------------------------------------------------------------------------
// Sequence
// -----------------------------------------------------------------------------

static inline byte* buf_find_seq (const byte* buf, size_t bufsz
, const byte* seq, size_t seqsz)
{
  return str_find_sub (buf, bufsz, seq, seqsz);
}

static inline byte* buf_rfind_seq (const byte* buf, size_t bufsz
, const byte* seq, size_t seqsz)
{
  return str_rfind_sub (buf, bufsz, seq, seqsz);
}

// -----------------------------------------------------------------------------
// Byte set
// -----------------------------------------------------------------------------

static inline byte* buf_find_byte_set (const byte* buf, size_t bufsz
, const byte* set, size_t setsz)
{
  return str_find_chr_set (buf, bufsz, set, setsz);
}

static inline byte* buf_rfind_byte_set (const byte* buf, size_t bufsz
, const byte* set, size_t setsz)
{
  return str_rfind_chr_set (buf, bufsz, set, setsz);
}

// -----------------------------------------------------------------------------
// Sequence set
// -----------------------------------------------------------------------------

static inline byte* buf_find_seq_set (const byte* buf, size_t bufsz
, const buf_const_t* set, size_t setsz, size_t* idx)
{
  return str_find_sub_set (buf, bufsz, (const str_const_t*)set, setsz, idx);
}

static inline byte* buf_rfind_seq_set (const byte* buf, size_t bufsz
, const buf_const_t* set, size_t setsz, size_t* idx)
{
  return str_rfind_sub_set (buf, bufsz, (const str_const_t*)set, setsz, idx);
}

// -----------------------------------------------------------------------------

#endif
