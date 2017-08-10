// =============================================================================
// <core/platform/cpu.h>
//
// Target CPU architecture definitions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A86F127E0E9F4C9FB55E5541250F600F
#define H_A86F127E0E9F4C9FB55E5541250F600F

// -----------------------------------------------------------------------------
// #define CPU_CUSTOM_ENDIAN: if the target CPU architecture is
// neither little- nor big-endian.
// -----------------------------------------------------------------------------
// #define CPU_BIG_ENDIAN: if the target CPU architecture is big-endian.
// -----------------------------------------------------------------------------
// #define CPU_LITTLE_ENDIAN: if the target CPU architecture is little-endian.
// -----------------------------------------------------------------------------
// #define CPU_CACHE_LINE_SIZE: explicitly set the CPU cache line size hint.
// -----------------------------------------------------------------------------
// #define CPU_PAGE_SIZE: explicitly set the CPU virtual page size hint.
// -----------------------------------------------------------------------------
// #define NO_CPU_SIGN_EXTENSION: if the target CPU doesn't have
// the arithmetic right shift.
// -----------------------------------------------------------------------------
// #define DISABLE_CPU_UNALIGNED_ACCESS: prevent optimizations that rely
// on unaligned memory access even if the target CPU supports it.
// -----------------------------------------------------------------------------

#define CPU(feat) (defined(CPU_##feat))

// =============================================================================
// Architecture
// -----------------------------------------------------------------------------
// Attempt to determine the target CPU architecture according to the target ABI
// -----------------------------------------------------------------------------
// x86-64
#if defined(__x86_64__) || defined(__amd64__)\
|| defined(_M_X64) || defined(_M_AMD64)
  #define CPU_X86_64

// -----------------------------------------------------------------------------
// x86
#elif defined(__i386__) || defined(_M_IX86)
  #define CPU_X86

// -----------------------------------------------------------------------------
// ARM Cortex 64-bit
#elif defined(__aarch64__)
  #define CPU_AARCH64

// -----------------------------------------------------------------------------
// ARM Cortex 32-bit
#elif defined(__arm__) || defined(_M_ARM)
  #define CPU_ARM

// -----------------------------------------------------------------------------
// MIPS
#elif defined(__mips__)
  #define CPU_MIPS
#endif

// -----------------------------------------------------------------------------
// x86-64 is backwards-compatible with x86
#if CPU(X86_64)
  #define CPU_X86
#endif

// =============================================================================
// Characteristics
// -----------------------------------------------------------------------------
// Width
// -----------------------------------------------------------------------------
// 64-bit
#if CPU(X86_64) || CPU(AARCH64)\
|| (CPU(MIPS) && defined(__mips64__))\
|| defined(__LP64__)
  #define CPU_64BIT

// -----------------------------------------------------------------------------
// 32-bit
#elif CPU(X86) || CPU(ARM) || CPU(MIPS)
  #define CPU_32BIT
#endif

// -----------------------------------------------------------------------------
// Endianness
// -----------------------------------------------------------------------------
// Assume the target CPU uses little-endian byte ordering when accessing memory
// if the exact endianness cannot be figured out
#if !CPU(LITTLE_ENDIAN) && !CPU(BIG_ENDIAN) && !CPU(CUSTOM_ENDIAN)
  #if (defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__))\
  || defined(__AARCH64EB__) || defined(__ARMEB__) || defined(__THUMBEB__)\
  || defined(__MIPSEB__) || defined(__MIPSEB) || defined(_MIPSEB)\
  || defined(__BIG_ENDIAN__)
    #define CPU_BIG_ENDIAN
  #else
    #define CPU_LITTLE_ENDIAN
  #endif
#endif

// -----------------------------------------------------------------------------
// Cache
// -----------------------------------------------------------------------------
// CPU cache line size (in bytes)
#if !CPU(CACHE_LINE_SIZE)
  #define CPU_CACHE_LINE_SIZE 64u
#endif

// -----------------------------------------------------------------------------
// Prefetch memory into various levels of the CPU cache
#if C(GNU)
  #define cpu_prefetch(...) __builtin_prefetch (__VA_ARGS__)
#else
  #define cpu_prefetch(...)
#endif

// -----------------------------------------------------------------------------
// Virtual memory
// -----------------------------------------------------------------------------
// CPU virtual page size (in bytes)
#if !CPU(PAGE_SIZE)
  #define CPU_PAGE_SIZE 4096u
#endif

// =============================================================================
// Features
// -----------------------------------------------------------------------------
// Signed integers handling
// -----------------------------------------------------------------------------
// Assume the CPU uses two's complement to represent signed integers
#if (-1 == ~0)
  #define CPU_TWOS_COMPLEMENT
#endif

// -----------------------------------------------------------------------------
// Assume the CPU performs arithmetic right shift (extends the negative sign)
// when shifting signed integers to the right
#if !NO(CPU_SIGN_EXTENSION)
  #define CPU_SIGN_EXTENSION
#endif

// -----------------------------------------------------------------------------
// Unaligned access
// -----------------------------------------------------------------------------
// Determine if the CPU is capable of unaligned memory access.
// (x86(-64) always permitted non-atomic unaligned memory access.)
#if CPU(X86) || defined(__ARM_FEATURE_UNALIGNED)
  #define CPU_UNALIGNED_ACCESS
#endif

// -----------------------------------------------------------------------------
// Forcefully disable unaligned memory access
#if DISABLED(CPU_UNALIGNED_ACCESS)
  #undef CPU_UNALIGNED_ACCESS
#endif

// =============================================================================
// CPU architecture-specific definitions
// -----------------------------------------------------------------------------

#if CPU(X86)
  #include "cpu/x86.h"
#endif

// -----------------------------------------------------------------------------

#endif
