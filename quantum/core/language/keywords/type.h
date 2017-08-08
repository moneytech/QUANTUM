// =============================================================================
// <core/language/keywords/type.h>
//
// Type keywords.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_F6F59768B0CC4E66985868AB08399494
#define H_F6F59768B0CC4E66985868AB08399494

// -----------------------------------------------------------------------------
// C11 `alignas` alignment specifier
#include "../../../stdlib/stdalign.h"

// -----------------------------------------------------------------------------
// `restrict`: the pointed memory isn't subject to aliasing
#if !HAVE(C99)
  #if C(GNU)
    #define restrict __restrict__
  #elif C(MSC)
    #if (C_MSC_VER >= 1900)
      // Visual Studio 2015 and later support the `restrict` qualifier natively
    #elif (C_MSC_VER >= 1400)
      // Visual Studio 2005 and later provide the `__restrict` qualifier
      #define restrict __restrict
    #else
      #define restrict
    #endif
  #else
    #define restrict
  #endif
#endif

// -----------------------------------------------------------------------------
// `alignas`: variable declaration with the stricter alignment requirement
#ifndef __alignas_is_defined
  #if C(GNU)
    // Can be emulated using the `aligned` GCC attribute
    #define alignas aligned
  #elif C(MSC)
    #if (C_MSC_VER >= 1900)
      // Visual Studio 2015 and later support the `alignas` specifier natively
      #define __alignas_is_defined 1
    #elif (C_MSC_VER >= 1310)
      // Can be emulated using the `align` specifier
      #define alignas aligned
    #endif
  #endif
#endif

// -----------------------------------------------------------------------------
// `aligned`: type definition with the stricter alignment requirement
#if C(GNU)
  #define aligned(n) __attribute__((aligned(n)))
#elif (C_MSC_VER >= 1310)
  // Visual Studio 2003 .NET and later provide the `align` specifier
  #define aligned(n) __declspec(align(n))
#endif

// -----------------------------------------------------------------------------
// `atomic`: C11 atomic type specifier & qualifier for concurrent object access
#if HAVE(C11) && HAVE(C_ATOMICS)
  #define atomic _Atomic
#endif

// -----------------------------------------------------------------------------
// `packed`: packed structure or union definition
#if C(GNU)
  // GCC and Clang provide both the pragma `pack` directive
  // and the `packed` attribute
  #define HAVE_PRAGMA_PACK
  #define HAVE_ATTRIBUTE_PACKED

  // Compile with the `-mno-ms-bitfields` switch on Windows to make it work
  #define packed __attribute__((packed))
#elif (C_MSC_VER >= 1310)
  // Visual Studio provides the `pack` pragma directive
  #define HAVE_PRAGMA_PACK
#endif

// -----------------------------------------------------------------------------

#endif
