// =============================================================================
// <intrinsics.h>
//
// Compiler intrinsics for the target architecture.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_C75AF77C7AD245A48F7892618E9797BA
#define H_C75AF77C7AD245A48F7892618E9797BA

// -----------------------------------------------------------------------------

#if C(GNU)
  #include <x86intrin.h>
#elif C(MSC)
  #include <intrin.h>
#endif

// -----------------------------------------------------------------------------

#endif