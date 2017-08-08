// =============================================================================
// <core/platform/cpu/x86.h>
//
// x86 (Intel / AMD / VIA / etc.) architecture definitions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_BBBFB9376E3A471C97F774BEB3D122F7
#define H_BBBFB9376E3A471C97F774BEB3D122F7

// -----------------------------------------------------------------------------
// Determine the available SSE ISA support
// -----------------------------------------------------------------------------
// Defined by GCC & Clang
#ifdef __SSE__
  #define CPU_SSE
#endif
#ifdef __SSE2__
  #define CPU_SSE2
#endif
#ifdef __SSE3__
  #define CPU_SSE3
#endif
#ifdef __SSSE3__
  #define CPU_SSSE3
#endif
#ifdef __SSE4_1__
  #define CPU_SSE41
#endif
#ifdef __SSE4_2__
  #define CPU_SSE42
#endif

// -----------------------------------------------------------------------------
// MSVC defines only `_M_IX86_FP` from which only SSE and SSE2 support
// can be figured out. SSE3+ constants would have to be defined manually.
#if (_M_IX86_FP != 0)
  #define CPU_SSE
#endif
#if (_M_IX86_FP == 2)
  #define CPU_SSE2
#endif

// -----------------------------------------------------------------------------
// All x86-64 CPUs come equipped with SSE and SSE2
#if CPU(X86_64)
  #if !CPU(SSE) && !DISABLED(CPU_SSE)
    #define CPU_SSE
  #endif
  #if !CPU(SSE2) && !DISABLED(CPU_SSE2)
    #define CPU_SSE2
  #endif
#endif

// -----------------------------------------------------------------------------
// Determine the available AVX ISA support
// -----------------------------------------------------------------------------
// GCC, Clang and MSVC all properly define these
#ifdef __AVX__
  #define CPU_AVX
#endif
#ifdef __AVX2__
  #define CPU_AVX2
#endif

// -----------------------------------------------------------------------------

#endif
