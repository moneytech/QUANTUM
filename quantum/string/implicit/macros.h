// =============================================================================
// <string/implicit/macros.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_E42E76E2F47F4A2F8C1128121A62D911
#define H_E42E76E2F47F4A2F8C1128121A62D911

// -----------------------------------------------------------------------------
// Specialized standard C string functions
// -----------------------------------------------------------------------------
// Compare two null-terminated strings for equality
#define strequ(str1, str2) (strcmp ((str1), (str2)) == 0)

// -----------------------------------------------------------------------------
// Length-limited version of the above
#define strnequ(str1, str2, max) (strncmp ((str1), (str2), (max)) == 0)

// -----------------------------------------------------------------------------
// Deprecated BSD string function definitions
// -----------------------------------------------------------------------------

#ifndef index
  #define index strchr
#endif

#ifndef rindex
  #define rindex strrchr
#endif

// -----------------------------------------------------------------------------

#endif
