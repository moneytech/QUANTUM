// =============================================================================
// <stdlib/string.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_B867E0A84B0B4889A7F04D5A9C513E6D
#define H_B867E0A84B0B4889A7F04D5A9C513E6D

// -----------------------------------------------------------------------------

#include <string.h>

#if OS(WIN32)
  #include "windows/string.h"

  #define HAVE_STRCASECMP
  #define HAVE_STRNCASECMP
#endif

// -----------------------------------------------------------------------------

#endif