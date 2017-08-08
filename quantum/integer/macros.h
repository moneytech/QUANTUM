// =============================================================================
// <integer/macros.h>
//
// Useful integer macros.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_B5FC5556927E49C993B62FFEA6F1A391
#define H_B5FC5556927E49C993B62FFEA6F1A391

// -----------------------------------------------------------------------------

#include "../stdlib/inttypes.h"

// -----------------------------------------------------------------------------
// Missing `printf()` and `scanf()` constants
// -----------------------------------------------------------------------------
// `size_t` and `ssize_t` format specifiers for `printf()` family of functions
#if OS(WIN32)
  #define PRIdSIZE "Id"
  #define PRIiSIZE "Ii"
  #define PRIuSIZE "Iu"
  #define PRIoSIZE "Io"
  #define PRIxSIZE "Ix"
  #define PRIXSIZE "IX"
#else
  #define PRIdSIZE "zd"
  #define PRIiSIZE "zi"
  #define PRIuSIZE "zu"
  #define PRIoSIZE "zo"
  #define PRIxSIZE "zx"
  #define PRIXSIZE "zX"
#endif

// -----------------------------------------------------------------------------
// `ptrdiff_t` format specifiers for `printf()` family of functions
#if OS(WIN32)
  #define PRIdPTRDIFF PRIdSIZE
  #define PRIiPTRDIFF PRIiSIZE
  #define PRIuPTRDIFF PRIuSIZE
  #define PRIoPTRDIFF PRIoSIZE
  #define PRIxPTRDIFF PRIxSIZE
  #define PRIXPTRDIFF PRIXSIZE
#else
  #define PRIdPTRDIFF "td"
  #define PRIiPTRDIFF "ti"
  #define PRIuPTRDIFF "tu"
  #define PRIoPTRDIFF "to"
  #define PRIxPTRDIFF "tx"
  #define PRIXPTRDIFF "tX"
#endif

// -----------------------------------------------------------------------------
// `size_t` and `ssize_t` format specifiers for `scanf()` family of functions
#if OS(WIN32)
  #define SCNdSIZE "Id"
  #define SCNiSIZE "Ii"
  #define SCNuSIZE "Iu"
  #define SCNoSIZE "Io"
  #define SCNxSIZE "Ix"
#else
  #define SCNdSIZE "zd"
  #define SCNiSIZE "zi"
  #define SCNuSIZE "zu"
  #define SCNoSIZE "zo"
  #define SCNxSIZE "zx"
#endif

// -----------------------------------------------------------------------------
// `ptrdiff_t` format specifiers for `scanf()` family of functions
#if OS(WIN32)
  #define SCNdPTRDIFF SCNdSIZE
  #define SCNiPTRDIFF SCNiSIZE
  #define SCNuPTRDIFF SCNuSIZE
  #define SCNoPTRDIFF SCNoSIZE
  #define SCNxPTRDIFF SCNxSIZE
#else
  #define SCNdPTRDIFF "td"
  #define SCNiPTRDIFF "ti"
  #define SCNuPTRDIFF "tu"
  #define SCNoPTRDIFF "to"
  #define SCNxPTRDIFF "tx"
#endif

// -----------------------------------------------------------------------------
// Simple bounds checking
// -----------------------------------------------------------------------------
// Base 10 (decimal)
#define int_can_oflow_dig(i, m) ((i) > (((m) - 9u) / 10u))
#define int_is_oflow_dig(i, m, d) ((i) > (((m) - (d)) / 10u))

// -----------------------------------------------------------------------------
// Base 16 (hexadecimal)
#define int_can_oflow_xdig(i, m) ((i) > (((m) - 15u) >> 4))
#define int_is_oflow_xdig(i, m, d) ((i) > (((m) - (d)) >> 4))

// -----------------------------------------------------------------------------
// Base 8 (octal)
#define int_can_oflow_odig(i, m) ((i) > (((m) - 7u) >> 3))
#define int_is_oflow_odig(i, m, d) ((i) > (((m) - (d)) >> 3))

// -----------------------------------------------------------------------------

#endif
