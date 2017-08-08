// =============================================================================
// <unicode.h>
//
// Essential Unicode definitions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_F0956719BC644D4683093CF88B2E73D0
#define H_F0956719BC644D4683093CF88B2E73D0

// -----------------------------------------------------------------------------

#include "stdlib/uchar.h"

// -----------------------------------------------------------------------------
// Unicode character types
// -----------------------------------------------------------------------------

#if HAVE(INT8)
  #define HAVE_UTF8
  typedef char_t u8_char_t;
#endif

#if HAVE(INT16) && defined(__STD_UTF_16__)
  #define HAVE_UTF16
  typedef char16_t u16_char_t;
#endif

#if HAVE(INT32) && defined(__STD_UTF_32__)
  #define HAVE_UTF32
  typedef char32_t u32_char_t;
#endif

// -----------------------------------------------------------------------------
// Unicode string literals
// -----------------------------------------------------------------------------

#if HAVE(C11)
  #define U8(str) u8##str
  #define U16(str) u##str
  #define U32(str) U##str
#else
  #define U8(str) str
  #define U16(str) str
  #define U32(str) str
#endif

// -----------------------------------------------------------------------------
// UTF byte order marks
// -----------------------------------------------------------------------------

#if HAVE(INT8)
  static const u8 utf8_bom[3] = {0xEFu, 0xBBu, 0xBFu};
#endif

#if HAVE(INT16)
  static const u16 utf16_bom = 0xFEFFu;
#endif

#if HAVE(INT32)
  static const u32 utf32_bom = 0xFEFFu;
#endif

// -----------------------------------------------------------------------------

#endif
