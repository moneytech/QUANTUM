// =============================================================================
// <signal.h>
//
// Signal management.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_D103531180CE4F43AF6C990880B72D95
#define H_D103531180CE4F43AF6C990880B72D95

// -----------------------------------------------------------------------------

#include "stdlib/signal.h"

// =============================================================================
// Constants
// -----------------------------------------------------------------------------
// Characteristics of the `sig_atomic_t` type
// -----------------------------------------------------------------------------

#if (SIG_ATOMIC_MIN < 0)
  #define SIG_ATOMIC_BIT (INT_BIT_MAX (SIG_ATOMIC_MAX) + 1)
#else
  #define SIG_ATOMIC_BIT INT_BIT_MAX (SIG_ATOMIC_MAX)
#endif

#define SIG_ATOMIC_DIG INT_DIG_MAX (SIG_ATOMIC_BIT)
#define SIG_ATOMIC_XDIG INT_XDIG_MAX (SIG_ATOMIC_BIT)
#define SIG_ATOMIC_ODIG INT_ODIG_MAX (SIG_ATOMIC_BIT)

// -----------------------------------------------------------------------------

#endif
