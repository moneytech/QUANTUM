// =============================================================================
// <stdlib/fenv.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_C222C89688434FA6AD427D516C596F5C
#define H_C222C89688434FA6AD427D516C596F5C

// -----------------------------------------------------------------------------

#if HAVE(C99) || (C_MSC_VER >= 1800)
  // Visual Studio 2013 and later come with <fenv.h>
  #include <fenv.h>
#endif

// -----------------------------------------------------------------------------

#endif