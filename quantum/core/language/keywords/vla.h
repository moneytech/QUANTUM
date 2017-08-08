// =============================================================================
// <core/language/keywords/vla.h>
//
// Variable length array declaration.
//
// Emulate VLAs with `alloca()` if they aren't supported by the compiler.
//
// Beware that `alloca()` works differently, and the `sizeof` operator
// won't report the correct array size.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_B861F3BAD1274FB2B26A878A6C76DB82
#define H_B861F3BAD1274FB2B26A878A6C76DB82

// -----------------------------------------------------------------------------

#if HAVE(C99) && HAVE(C_VLA)
  #define vla(type, name, num) type name[num]
#else
  #define vla(type, name, num) type* name = mem_alloc_stack (sizeof (type) * (num))
#endif

// -----------------------------------------------------------------------------

#endif
