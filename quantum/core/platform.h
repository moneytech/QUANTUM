// =============================================================================
// <core/platform.h>
//
// Target platform definitions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_D02E0418D81B46608009B364A70F7215
#define H_D02E0418D81B46608009B364A70F7215

// -----------------------------------------------------------------------------

#include "platform/os.h"
#include "platform/compiler.h"
#include "platform/cpu.h"

// -----------------------------------------------------------------------------
// If, for some reason, the OS was detected to be 64-bit, but the CPU wasn't.
// (Or the other way around.)
#if OS(64BIT) || CPU(64BIT)
  #if !OS(64BIT)
    #define OS_64BIT
  #elif !CPU(64BIT)
    #define CPU_64BIT
  #endif
#endif

// -----------------------------------------------------------------------------
// Enable support for files larger than 2 GB (for 32-bit builds only).
// (Not all platforms recognize the definition of `_FILE_OFFSET_BITS`.)
#if !CPU(64BIT)
  #define _FILE_OFFSET_BITS 64
#endif

// -----------------------------------------------------------------------------

#endif
