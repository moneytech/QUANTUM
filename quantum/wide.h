// =============================================================================
// <wide.h>
//
// Combined wide character type definitions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_FCD6E1ADD01C4C87A3963B0EDBB2E719
#define H_FCD6E1ADD01C4C87A3963B0EDBB2E719

// -----------------------------------------------------------------------------

#include "stdlib/wctype.h"
#include "stdlib/wchar.h"

// =============================================================================
// Constants
// -----------------------------------------------------------------------------
// Characteristics of the wide types
// -----------------------------------------------------------------------------

#if (WCHAR_MIN < 0)
  #define WCHAR_BIT (INT_BIT_MAX (WCHAR_MAX) + 1)
#else
  #define WCHAR_BIT INT_BIT_MAX (WCHAR_MAX)
#endif

#define WCHAR_DIG INT_DIG_MAX (WCHAR_BIT)
#define WCHAR_XDIG INT_XDIG_MAX (WCHAR_BIT)
#define WCHAR_ODIG INT_ODIG_MAX (WCHAR_BIT)

// -----------------------------------------------------------------------------

#if (WINT_MIN < 0)
  #define WINT_BIT (INT_BIT_MAX (WINT_MAX) + 1)
#else
  #define WINT_BIT INT_BIT_MAX (WINT_MAX)
#endif

#define WINT_DIG INT_DIG_MAX (WINT_BIT)
#define WINT_XDIG INT_XDIG_MAX (WINT_BIT)
#define WINT_ODIG INT_ODIG_MAX (WINT_BIT)

// =============================================================================
// Types
// -----------------------------------------------------------------------------
// Wide character type that are guaranteed to be unsigned
// -----------------------------------------------------------------------------

#if (WCHAR_BIT == 8)
  #define HAVE_WIDE_CHAR
  typedef u8 wide_char_t;
#elif (WCHAR_BIT == 16)
  #define HAVE_WIDE_CHAR
  typedef u16 wide_char_t;
#elif (WCHAR_BIT == 32)
  #define HAVE_WIDE_CHAR
  typedef u32 wide_char_t;
#elif (WCHAR_BIT == 64)
  #define HAVE_WIDE_CHAR
  typedef u64 wide_char_t;
#elif (WCHAR_BIT == INTMAX_BIT)
  #define HAVE_WIDE_CHAR
  typedef intmax_t wide_char_t;
#elif (WCHAR_BIT == CHAR_BIT)
  #define HAVE_WIDE_CHAR
  typedef uchar wide_char_t;
#elif (WCHAR_BIT == SHRT_BIT)
  #define HAVE_WIDE_CHAR
  typedef ushort wide_char_t;
#elif (WCHAR_BIT == INT_BIT)
  #define HAVE_WIDE_CHAR
  typedef uint wide_char_t;
#elif (WCHAR_BIT == LONG_BIT)
  #define HAVE_WIDE_CHAR
  typedef ulong wide_char_t;
#elif (WCHAR_BIT == LLONG_BIT)
  #define HAVE_WIDE_CHAR
  typedef ullong wide_char_t;
#endif

// -----------------------------------------------------------------------------

typedef wint_t wide_int_t;

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// Wide string literal
#define W(str) L##str

// -----------------------------------------------------------------------------

#endif
