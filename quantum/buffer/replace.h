// =============================================================================
// <buffer/replace.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_D0595A46BE26490BA6C99C5BC7058AF3
#define H_D0595A46BE26490BA6C99C5BC7058AF3

// -----------------------------------------------------------------------------

#include "../string/types.h"
#include "../string/replace.h"

// -----------------------------------------------------------------------------
// Byte
// -----------------------------------------------------------------------------

static inline void buf_replace_byte (byte* buf, size_t size, byte old, byte new)
{
  str_replace_chr (buf, size, old, new);
}

// -----------------------------------------------------------------------------
// Sequence
// -----------------------------------------------------------------------------

static inline void buf_replace_seq (byte* buf, size_t bufsz
, const byte* old, const byte* new, size_t seqsz)
{
  str_replace_sub (buf, bufsz, old, new, seqsz);
}

// -----------------------------------------------------------------------------
// Byte set
// -----------------------------------------------------------------------------

static inline void buf_replace_byte_set (byte* buf, size_t bufsz
, const byte* old, const byte* new, size_t setsz)
{
  str_replace_chr_set (buf, bufsz, old, new, setsz);
}

// -----------------------------------------------------------------------------
// Sequence set
// -----------------------------------------------------------------------------

static inline void buf_replace_seq_set (byte* buf, size_t bufsz
, const buf_const_t* old, const byte* const* new, size_t setsz)
{
  str_replace_sub_set (buf, bufsz, (const str_const_t*)old, new, setsz);
}

// -----------------------------------------------------------------------------

#endif
