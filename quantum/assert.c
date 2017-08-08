// =============================================================================
// <assert.c>
//
// Perform runtime assertions to determine the correctness of QUANTUM headers.
//
// Compile this unit with all optimizations disabled (`-O0` for GCC & Clang).
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "build.h"
#include "core.h"

#include "assert.h"

// -----------------------------------------------------------------------------

#ifndef NDEBUG

// -----------------------------------------------------------------------------

#if !CPU(CUSTOM_ENDIAN)
static bint cpu_is_little_endian (void)
{
  uint i = 1u;
  return *(byte*)&i;
}
#endif

// -----------------------------------------------------------------------------

#if FP(IEEE754) && !FP(CUSTOM_ENDIAN)
static bint fp_is_little_endian (void)
{
  float f = 1.0f;
  return !*(byte*)&f;
}
#endif

// -----------------------------------------------------------------------------

void quantum_assertions (void)
{
  bint test;

  // Endianness
#if !CPU(CUSTOM_ENDIAN)
  test = cpu_is_little_endian();

  #if CPU(LITTLE_ENDIAN)
    assert (test == true);
  #elif CPU(BIG_ENDIAN)
    assert (test == false);
  #endif
#endif

  // Floating point endianness
#if FP(IEEE754) && !FP(CUSTOM_ENDIAN)
  test = fp_is_little_endian();

  #if FP(LITTLE_ENDIAN)
    assert (test == true);
  #elif FP(BIG_ENDIAN)
    assert (test == false);
  #endif
#endif
}

// -----------------------------------------------------------------------------

#endif // !NDEBUG
