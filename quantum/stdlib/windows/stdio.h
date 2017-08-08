// =============================================================================
// <stdlib/windows/stdio.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A61384A22BA848EF8AD788F25FDC33AB
#define H_A61384A22BA848EF8AD788F25FDC33AB

// =============================================================================
// Macros
// -----------------------------------------------------------------------------

#define wfopen _wfopen
#define wfreopen _wfreopen

#define fdopen _fdopen
#define wfdopen _wfdopen

#define fgetchar _fgetchar
#define fgetwchar _fgetwchar

#define fputchar _fputchar
#define fputwchar _fputwchar

#define getw _getw
#define putw _putw

#define getws _getws
#define putws _putws

#define wremove _wremove
#define wrename _wrename

#define wtmpnam _wtmpnam

#define tempnam _tempnam
#define wtempnam _wtempnam

#define wperror _wperror

// -----------------------------------------------------------------------------
// `snprintf()` has a serious security flaw whereby it doesn't null-terminate
// the output string buffer properly. Emulate the correct behavior
// using the `_snprintf_s()`.
// -----------------------------------------------------------------------------

#define snprintf(buf, num, ...) _snprintf_s ((buf), (num), _TRUNCATE, __VA_ARGS__)
#define snwprintf(buf, num, ...) _snwprintf_s ((buf), (num), _TRUNCATE, __VA_ARGS__)

#ifdef UNICODE
  #define sntprintf snwprintf
#else
  #define sntprintf snprintf
#endif

#define vsnprintf(buf, num, fmt, args) _vsnprintf_s ((buf), (num), _TRUNCATE, (fmt), (args))
#define vsnwprintf(buf, num, fmt, args) _vsnwprintf_s ((buf), (num), _TRUNCATE, (fmt), (args))

#ifdef UNICODE
  #define vsntprintf vsnwprintf
#else
  #define vsntprintf vsnprintf
#endif

// -----------------------------------------------------------------------------

#endif
