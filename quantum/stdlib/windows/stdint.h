// =============================================================================
// <stdlib/windows/stdint.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_E51B1120622C4498A8D921B0F16C0491
#define H_E51B1120622C4498A8D921B0F16C0491

// -----------------------------------------------------------------------------
// Visual Studio 2010 and later come with <stdint.h>
#if (C_MSC_VER >= 1600)
  #include <stdint.h>

// -----------------------------------------------------------------------------
// Reconstruct <stdint.h> for versions of Visual Studio earlier than 2010
#elif // (C_MSC_VER >= 1600) ][

// =============================================================================
// Constants
// -----------------------------------------------------------------------------
// 8-bit
// -----------------------------------------------------------------------------

#define INT8_MIN (-127i8 - 1)
#define INT8_MAX 127i8
#define UINT8_MAX 0xFFui8

#define INT_FAST8_MIN INT8_MIN
#define INT_FAST8_MAX INT8_MAX
#define UINT_LEAST8_MAX UINT8_MAX

#define INT_LEAST8_MIN INT8_MIN
#define INT_LEAST8_MAX INT8_MAX
#define UINT_FAST8_MAX UINT8_MAX

// -----------------------------------------------------------------------------
// 16-bit
// -----------------------------------------------------------------------------

#define INT16_MIN (-32767i16 - 1)
#define INT16_MAX 32767i16
#define UINT16_MAX 0xFFFFui16

#define INT_FAST16_MIN INT16_MIN
#define INT_FAST16_MAX INT16_MAX
#define UINT_FAST16_MAX UINT16_MAX

#define INT_LEAST16_MIN INT16_MIN
#define INT_LEAST16_MAX INT16_MAX
#define UINT_LEAST16_MAX UINT16_MAX

// -----------------------------------------------------------------------------
// 32-bit
// -----------------------------------------------------------------------------

#define INT32_MIN (-2147483647i32 - 1)
#define INT32_MAX 2147483647i32
#define UINT32_MAX 0xFFFFFFFFui32

#define INT_FAST32_MIN INT32_MIN
#define INT_FAST32_MAX INT32_MAX
#define UINT_FAST32_MAX UINT32_MAX

#define INT_LEAST32_MIN INT32_MIN
#define INT_LEAST32_MAX INT32_MAX
#define UINT_LEAST32_MAX UINT32_MAX

// -----------------------------------------------------------------------------
// 64-bit
// -----------------------------------------------------------------------------

#define INT64_MIN (-9223372036854775807i64 - 1)
#define INT64_MAX 9223372036854775807i64
#define UINT64_MAX 0xFFFFFFFFFFFFFFFFui64

#define INT_FAST64_MIN INT64_MIN
#define INT_FAST64_MAX INT64_MAX
#define UINT_FAST64_MAX UINT64_MAX

#define INT_LEAST64_MIN INT64_MIN
#define INT_LEAST64_MAX INT64_MAX
#define UINT_LEAST64_MAX UINT64_MAX

// -----------------------------------------------------------------------------
// Maximum
// -----------------------------------------------------------------------------

#define INTMAX_MIN INT64_MIN
#define INTMAX_MAX INT64_MAX
#define UINTMAX_MAX UINT64_MAX

// -----------------------------------------------------------------------------
// Pointer
// -----------------------------------------------------------------------------

#if OS(WIN64)
  #define INTPTR_MIN INT64_MIN
  #define INTPTR_MAX INT64_MAX
  #define UINTPTR_MAX UINT64_MAX
#else
  #define INTPTR_MIN INT32_MIN
  #define INTPTR_MAX INT32_MAX
  #define UINTPTR_MAX UINT32_MAX
#endif

// -----------------------------------------------------------------------------
// Other
// -----------------------------------------------------------------------------
// `size_t`
#ifndef SIZE_MAX
  #if OS(WIN64)
    #define SIZE_MAX UINT64_MAX
  #else
    #define SIZE_MAX UINT32_MAX
  #endif
#endif

// -----------------------------------------------------------------------------
// `ptrdiff_t`
#ifndef PTRDIFF_MAX
  #define PTRDIFF_MIN INTPTR_MIN
  #define PTRDIFF_MAX INTPTR_MAX
#endif

// -----------------------------------------------------------------------------
// `sig_atomic_t`
#ifndef SIG_ATOMIC_MAX
  #define SIG_ATOMIC_MIN INT32_MIN
  #define SIG_ATOMIC_MAX INT32_MAX
#endif

// -----------------------------------------------------------------------------
// `wchar_t`
#ifndef WCHAR_MAX
  #define WCHAR_MIN 0
  #define WCHAR_MAX UINT16_MAX
#endif

// -----------------------------------------------------------------------------
// `win_t`
#ifndef WINT_MAX
  #define WINT_MIN 0
  #define WINT_MAX UINT16_MAX
#endif

// =============================================================================
// Types
// -----------------------------------------------------------------------------
// 8-bit
// -----------------------------------------------------------------------------

typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef int8_t int_fast8_t;
typedef uint8_t uint_fast8_t;

typedef int8_t int_least8_t;
typedef uint8_t uint_least8_t;

// -----------------------------------------------------------------------------
// 16-bit
// -----------------------------------------------------------------------------

typedef signed short int16_t;
typedef unsigned short uint16_t;

typedef int16_t int_fast16_t;
typedef uint16_t uint_fast16_t;

typedef int16_t int_least16_t;
typedef uint16_t uint_least16_t;

// -----------------------------------------------------------------------------
// 32-bit
// -----------------------------------------------------------------------------

typedef signed int int32_t;
typedef unsigned int uint32_t;

typedef int32_t int_fast32_t;
typedef uint32_t uint_fast32_t;

typedef int32_t int_least32_t;
typedef uint32_t uint_least32_t;

// -----------------------------------------------------------------------------
// 64-bit
// -----------------------------------------------------------------------------

typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t;

typedef int64_t int_fast64_t;
typedef uint64_t uint_fast64_t;

typedef int64_t int_least64_t;
typedef uint64_t uint_least64_t;

// -----------------------------------------------------------------------------
// Maximum
// -----------------------------------------------------------------------------

typedef int64_t intmax_t;
typedef uint64_t uintmax_t;

// -----------------------------------------------------------------------------
// Pointer
// -----------------------------------------------------------------------------

#if OS(WIN64)
  typedef int64_t intptr_t;
  typedef uint64_t uintptr_t;
#else
  typedef int32_t intptr_t;
  typedef uint32_t uintptr_t;
#endif

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// Integer constant specifiers
// -----------------------------------------------------------------------------

#define INT8_C(i) i##i8
#define UINT8_C(u) u##ui8

#define INT16_C(i) i##i16
#define UINT16_C(u) u##ui16

#define INT32_C(i) i##i32
#define UINT32_C(u) u##ui32

#define INT64_C(i) i##i64
#define UINT64_C(u) u##ui64

#define INTMAX_C INT64_C
#define UINTMAX_C UINT64_C

// -----------------------------------------------------------------------------

#endif // !(C_MSC_VER >= 1600)

// -----------------------------------------------------------------------------

#endif
