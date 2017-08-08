// =============================================================================
// <stdlib/complex.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_CE0CA6A66FC44CC6BA9D4387142FB394
#define H_CE0CA6A66FC44CC6BA9D4387142FB394

// -----------------------------------------------------------------------------

#if HAVE(C99) && HAVE(C_COMPLEX)
  #include <complex.h>

  #if (HAVE(C11) && HAVE(C_IEEE754_COMPLEX)) || defined(_Imaginary_I)
    #define HAVE_IMAGINARY
  #endif
#endif

// -----------------------------------------------------------------------------

#endif
