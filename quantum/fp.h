// =============================================================================
// <fp.h>
//
// Essential floating point definitions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_FE9041904E4D42F9A40BB2F1EAA396EC
#define H_FE9041904E4D42F9A40BB2F1EAA396EC

// -----------------------------------------------------------------------------
// #define FP_CUSTOM: if the target platform doesn't use IEEE 754 standard
// for floating point number representation.
// -----------------------------------------------------------------------------
// #define FP_CUSTOM_ENDIAN: if the target platform stores floating point
// numbers in memory in neither little- nor big-endian format.
// -----------------------------------------------------------------------------
// #define FP_BIG_ENDIAN: if the target platform stores floating point
// numbers in memory in big-endian format.
// -----------------------------------------------------------------------------
// #define FP_LITTLE_ENDIAN: if the target platform stores floating point
// numbers in memory in little-endian format.
// -----------------------------------------------------------------------------

#define FP(feat) (defined(FP_##feat))

// -----------------------------------------------------------------------------

#include "stdlib/fenv.h"

// -----------------------------------------------------------------------------
// Determine if the floating point types conform to IEEE 754
#if HAVE(C_IEEE754) || !FP(CUSTOM)
  #define FP_IEEE754
#endif

// -----------------------------------------------------------------------------
// Determine the endianness of the floating point types
// -----------------------------------------------------------------------------
// Assume floating point numbers are represented in little-endian format
#if !FP(LITTLE_ENDIAN) && !FP(BIG_ENDIAN) && !FP(CUSTOM_ENDIAN)
  #if defined(__FLOAT_WORD_ORDER__) && (__FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__)
    #define FP_BIG_ENDIAN
  #else
    #define FP_LITTLE_ENDIAN
  #endif
#endif

// -----------------------------------------------------------------------------
// Check if endianness of integers is opposite
#if (CPU(LITTLE_ENDIAN) && FP(BIG_ENDIAN))\
|| (CPU(BIG_ENDIAN) && FP(LITTLE_ENDIAN))
  #define FP_DIFFERENT_ENDIAN
#endif

// -----------------------------------------------------------------------------

#endif
