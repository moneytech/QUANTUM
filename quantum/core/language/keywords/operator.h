// =============================================================================
// <core/language/keywords/operator.h>
//
// Operator keywords.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_BC02D21EAC44417DBDA95A6A13511B6D
#define H_BC02D21EAC44417DBDA95A6A13511B6D

// -----------------------------------------------------------------------------
// `offsetof` offset operator
#include "../../../stdlib/stddef.h"

// -----------------------------------------------------------------------------
// C95 logical and bitwise operator keywords
#include "../../../stdlib/iso646.h"

// -----------------------------------------------------------------------------
// C11 `alignof` alignment operator
#include "../../../stdlib/stdalign.h"

// -----------------------------------------------------------------------------
// `alignof`: alignment requirement of the type
#ifndef __alignof_is_defined
  #if C(GNU)
    #define alignof __alignof__
  #elif C(MSC)
    #if (C_MSC_VER >= 1900)
      // Visual Studio 2015 and later support the `alignof` operator natively
      #define __alignof_is_defined 1
    #elif (C_MSC_VER >= 1310)
      // Visual Studio 2003 .NET and later provide the `__alignof` operator
      #define alignof __alignof
    #else
      // It is always safe to default to the `sizeof` operator
      #define alignof sizeof
    #endif
  #else
    // Default to the `sizeof` operator
    #define alignof sizeof
  #endif
#endif

// -----------------------------------------------------------------------------
// `typeof`: declared type of a variable
#if C(GNU)
  #define typeof __typeof__
#endif

// -----------------------------------------------------------------------------
// Number of elements in a static array of any type
#define numof(arr) (sizeof (arr) / sizeof ((arr)[0]))

// -----------------------------------------------------------------------------
// Length (number of characters before the terminating null character)
// of a null-terminated string literal constant (of any type)
#define cstrlen(str) (numof (str) - 1u)

// -----------------------------------------------------------------------------
// Exchange two variables of the same type using an intermediate variable
#define xchg swap

#define swap(t, a, b) do\
{         \
  t c = a;\
  a = b;  \
  b = c;  \
} while (0)

// -----------------------------------------------------------------------------

#endif
