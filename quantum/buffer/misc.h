// =============================================================================
// <buffer/misc.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_C21065F2AB3C489391EE57148714030C
#define H_C21065F2AB3C489391EE57148714030C

// -----------------------------------------------------------------------------

#include "../string/misc.h"

// -----------------------------------------------------------------------------

static inline byte* buf_clone (const byte* buf, size_t size)
{
  return str_clone (buf, size);
}

// -----------------------------------------------------------------------------

#endif
