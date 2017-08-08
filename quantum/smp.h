// =============================================================================
// <smp.h>
//
// Symmetric multiprocessing utility functions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_F26AAF2A4D8F4DEC941585E45949643B
#define H_F26AAF2A4D8F4DEC941585E45949643B

// -----------------------------------------------------------------------------

#define SMP(feat) (defined(SMP_##feat))

// -----------------------------------------------------------------------------
// See if the compiler comes with support for OpenMP
#ifdef _OPENMP
  #define SMP_OPENMP
#endif

// -----------------------------------------------------------------------------
// Get the number of available logical processing cores
extern uint smp_core_count (void);

// -----------------------------------------------------------------------------

#endif
