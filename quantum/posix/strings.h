// =============================================================================
// <posix/strings.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A304A8C4FB424DDE9B16E28479C1DFD1
#define H_A304A8C4FB424DDE9B16E28479C1DFD1

// -----------------------------------------------------------------------------

#if (XOPEN_VER >= 500) || (POSIX_VER >= 200112L)
  #include <strings.h>

  #define HAVE_STRCASECMP
  #define HAVE_STRNCASECMP
#endif

// -----------------------------------------------------------------------------
// Compare two null-terminated strings for equality case-insensitively
#define strcaseequ(str1, str2) (strcasecmp ((str1), (str2)) == 0)

// -----------------------------------------------------------------------------
// Length-limited version of the above
#define strncaseequ(str1, str2, max) (strncasecmp ((str1), (str2), (max)) == 0)

// -----------------------------------------------------------------------------

#endif
