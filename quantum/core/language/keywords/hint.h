// =============================================================================
// <core/language/keywords/hint.h>
//
// Compiler optimization hint keywords.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A1EDED5DEA864E7AB1765216075FD74A
#define H_A1EDED5DEA864E7AB1765216075FD74A

// -----------------------------------------------------------------------------
// Branching and basic block ordering hints
#if C(GNU)
  #define likely(expr) __builtin_expect (!!(expr), 1)
  #define unlikely(expr) __builtin_expect (!!(expr), 0)
#else
  #define likely nop
  #define unlikely nop
#endif

// -----------------------------------------------------------------------------
// Inform the compiler that a specified point in code is not reachable
#if C(GNU)
  #define assume_unreachable() __builtin_unreachable()
#elif C(MSC)
  #define assume_unreachable() __assume (0)
#else
  #define assume_unreachable()
#endif

// -----------------------------------------------------------------------------
// Inform the compiler that a particular pointer variable
// satisfies a particular alignment requirement
#if C(GNU)
  #define assume_aligned(align, ptr) __builtin_assume_aligned (ptr, align)
#else
  #define assume_aligned(align, ptr)
#endif

// -----------------------------------------------------------------------------

#endif
