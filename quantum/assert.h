// =============================================================================
// <assert.h>
//
// Runtime and compile time (if C11 is available) assertions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_C50E044B886741EA883529AD9619FA0D
#define H_C50E044B886741EA883529AD9619FA0D

// -----------------------------------------------------------------------------

#include "stdlib/assert.h"

// -----------------------------------------------------------------------------

#ifdef NDEBUG
  #define quantum_assertions()
#else
  extern void quantum_assertions (void);
#endif

// -----------------------------------------------------------------------------

#endif
