// =============================================================================
// <simd.h>
//
// SIMD definitions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_D2C785BB1B3D461398F23E32441AB639
#define H_D2C785BB1B3D461398F23E32441AB639

// -----------------------------------------------------------------------------
// x86 SSE
// -----------------------------------------------------------------------------

#if CPU(X86)
  #include "sse.h"
#endif

// -----------------------------------------------------------------------------
// Auto-vectorization provided by Clang & GCC
// -----------------------------------------------------------------------------

#if C(GNU)
  #if HAVE(INT8)
    typedef s8 v16s8 __attribute__((vector_size(16)));
    typedef u8 v16u8 __attribute__((vector_size(16)));
  #endif

  #if HAVE(INT16)
    typedef s16 v8s16 __attribute__((vector_size(16)));
    typedef u16 v8u16 __attribute__((vector_size(16)));
  #endif

  #if HAVE(INT32)
    typedef s32 v4s32 __attribute__((vector_size(16)));
    typedef u32 v4u32 __attribute__((vector_size(16)));
  #endif

  #if HAVE(INT64)
    typedef s64 v2s64 __attribute__((vector_size(16)));
    typedef u64 v2u64 __attribute__((vector_size(16)));
  #endif

  #if (FLT_BINARY == 32)
    typedef float v4f32 __attribute__((vector_size(16)));
  #endif

  #if (DBL_BINARY == 64)
    typedef double v2f64 __attribute__((vector_size(16)));
  #endif
#endif

// -----------------------------------------------------------------------------

#endif
