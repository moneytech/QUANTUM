// =============================================================================
// <time.h>
//
// Time measurement and conversion functions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_B38897A9895341B9A9B2DAAC25DAEA18
#define H_B38897A9895341B9A9B2DAAC25DAEA18

// -----------------------------------------------------------------------------

#include "stdlib/time.h"

// =============================================================================
// Constants
// -----------------------------------------------------------------------------

#define TM_RFC1123_SIZE_MIN 32u

// =============================================================================
// Types
// -----------------------------------------------------------------------------

typedef struct tm tm_t;

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// Parse a date & time string in various formats (ANSI C, RFC 822, RFC 850)
// -----------------------------------------------------------------------------

extern time_t tm_from_str (const char_t* str, size_t len, char_t** end);

#define tm_from_stri(str, end) tm_from_str ((str), stri_nlength ((str), 64u), end)

// -----------------------------------------------------------------------------
// Produce an RFC 1123 (RFC 822) compliant date & time string
// -----------------------------------------------------------------------------

extern size_t tm_to_str (char_t* str, time_t utm);

static inline char_t* tm_to_stri (char_t* str, time_t utm)
{
  size_t len = tm_to_str (str, utm);

  str[len] = '\0';

  return str + len;
}

// -----------------------------------------------------------------------------

#endif
