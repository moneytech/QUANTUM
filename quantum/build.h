// =============================================================================
// <core/build.h>
//
// Common build definitions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_EC929321B35F45AF8E0AFDE1AD95C943
#define H_EC929321B35F45AF8E0AFDE1AD95C943

// -----------------------------------------------------------------------------

#include "core/platform/os.h"
#include "core/platform/compiler.h"

// -----------------------------------------------------------------------------

#if OS(LINUX)
  #include "build/linux.h"
#endif

#if OS(POSIX)
  #include "build/posix.h"
#endif

#if OS(WIN32)
  #include "build/windows.h"
#endif

// -----------------------------------------------------------------------------

#endif
