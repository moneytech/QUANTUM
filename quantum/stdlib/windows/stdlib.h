// =============================================================================
// <stdlib/windows/stdlib.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_B54599F02C644863975A6B9BAE9E134E
#define H_B54599F02C644863975A6B9BAE9E134E

// -----------------------------------------------------------------------------

#include <malloc.h>

// =============================================================================
// Macros
// -----------------------------------------------------------------------------

#define aligned_malloc _aligned_malloc
#define aligned_free _aligned_free

#if C(MSC)
  #define alloca _alloca
#endif

// -----------------------------------------------------------------------------

#define itoa _itoa
#define itow _itow

#define ltoa _ltoa
#define ltow _ltow

#define ultoa _ultoa
#define ultow _ultow

#define i64toa _i64toa
#define i64tow _i64tow

#define ui64toa _ui64toa
#define ui64tow _ui64tow

// -----------------------------------------------------------------------------

#define wtoi _wtoi
#define wtol _wtol
#define wtoll _wtoi64
#define wtof _wtof

// -----------------------------------------------------------------------------

#define wgetenv _wgetenv
#define wsystem _wsystem

// -----------------------------------------------------------------------------

#endif
