// =============================================================================
// <core/build/posix.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_AD68010D5D4D4D2A824FC4E11FF41D33
#define H_AD68010D5D4D4D2A824FC4E11FF41D33

// -----------------------------------------------------------------------------
// Minimum POSIX standard version targeted
// -----------------------------------------------------------------------------

#if !defined(POSIX_VER) && !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)\
&& !defined(_GNU_SOURCE)
  #ifndef XOPEN_VER
    // X/Open 7
    #define XOPEN_VER 700
  #endif

  #define _XOPEN_SOURCE XOPEN_VER
#endif

// -----------------------------------------------------------------------------

#if !defined(XOPEN_VER) && !defined(_XOPEN_SOURCE) && !defined(_POSIX_C_SOURCE)\
&& !defined(_GNU_SOURCE)
  #ifndef POSIX_VER
    // POSIX 2008
    #define POSIX_VER 200809L
  #endif

  #define _POSIX_C_SOURCE POSIX_VER
#endif

// -----------------------------------------------------------------------------

#endif
