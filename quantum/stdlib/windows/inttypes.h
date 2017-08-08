// =============================================================================
// <stdlib/windows/inttypes.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A6206B74735C47F0ADF0CBB5A4B0279B
#define H_A6206B74735C47F0ADF0CBB5A4B0279B

// -----------------------------------------------------------------------------
// Visual Studio 2013 and later come with <inttypes.h>
#if (C_MSC_VER >= 1800)
  #include <inttypes.h>

// -----------------------------------------------------------------------------
// Reconstruct <inttypes.h> for versions of Visual Studio earlier than 2013
#else // !(C_MSC_VER >= 1800) ][

// =============================================================================
// Constants
// -----------------------------------------------------------------------------
// `printf()`
// -----------------------------------------------------------------------------
// 8 bits: the `hh` prefix is not supported by Windows CRT earlier than 2013
#define PRId8 "hhd"
#define PRIi8 "hhi"
#define PRIu8 "hhu"
#define PRIo8 "hho"
#define PRIx8 "hhx"
#define PRIX8 "hhX"

#define PRIdFAST8 PRId8
#define PRIiFAST8 PRIi8
#define PRIuFAST8 PRIu8
#define PRIoFAST8 PRIo8
#define PRIxFAST8 PRIx8
#define PRIXFAST8 PRIX8

#define PRIdLEAST8 PRId8
#define PRIiLEAST8 PRIi8
#define PRIuLEAST8 PRIu8
#define PRIoLEAST8 PRIo8
#define PRIxLEAST8 PRIx8
#define PRIXLEAST8 PRIX8

// 16 bits
#define PRId16 "hd"
#define PRIi16 "hi"
#define PRIu16 "hu"
#define PRIo16 "ho"
#define PRIx16 "hx"
#define PRIX16 "hX"

#define PRIdFAST16 PRId16
#define PRIiFAST16 PRIi16
#define PRIuFAST16 PRIu16
#define PRIoFAST16 PRIo16
#define PRIxFAST16 PRIx16
#define PRIXFAST16 PRIX16

#define PRIdLEAST16 PRId16
#define PRIiLEAST16 PRIi16
#define PRIuLEAST16 PRIu16
#define PRIoLEAST16 PRIo16
#define PRIxLEAST16 PRIx16
#define PRIXLEAST16 PRIX16

// 32 bits
#define PRId32 "I32d"
#define PRIi32 "I32i"
#define PRIu32 "I32u"
#define PRIo32 "I32o"
#define PRIx32 "I32x"
#define PRIX32 "I32X"

#define PRIdFAST32 PRId32
#define PRIiFAST32 PRIi32
#define PRIuFAST32 PRIu32
#define PRIoFAST32 PRIo32
#define PRIxFAST32 PRIx32
#define PRIXFAST32 PRIX32

#define PRIdLEAST32 PRId32
#define PRIiLEAST32 PRIi32
#define PRIuLEAST32 PRIu32
#define PRIoLEAST32 PRIo32
#define PRIxLEAST32 PRIx32
#define PRIXLEAST32 PRIX32

// 64 bits
#define PRId64 "I64d"
#define PRIi64 "I64i"
#define PRIu64 "I64u"
#define PRIo64 "I64o"
#define PRIx64 "I64x"
#define PRIX64 "I64X"

#define PRIdFAST64 PRId64
#define PRIiFAST64 PRIi64
#define PRIuFAST64 PRIu64
#define PRIoFAST64 PRIo64
#define PRIxFAST64 PRIx64
#define PRIXFAST64 PRIX64

#define PRIdLEAST64 PRId64
#define PRIiLEAST64 PRIi64
#define PRIuLEAST64 PRIu64
#define PRIoLEAST64 PRIo64
#define PRIxLEAST64 PRIx64
#define PRIXLEAST64 PRIX64

// Maximum
#define PRIdMAX PRId64
#define PRIiMAX PRIi64
#define PRIuMAX PRIu64
#define PRIoMAX PRIo64
#define PRIxMAX PRIx64
#define PRIXMAX PRIX64

// Pointer
#define PRIdPTR "Id"
#define PRIiPTR "Ii"
#define PRIuPTR "Iu"
#define PRIoPTR "Io"
#define PRIxPTR "Ix"
#define PRIXPTR "IX"

// -----------------------------------------------------------------------------
// `scanf()`
// -----------------------------------------------------------------------------
// 8 bits: the `hh` prefix is not supported by Windows CRT earlier than 2013
#define SCNd8 "hhd"
#define SCNi8 "hhi"
#define SCNu8 "hhu"
#define SCNo8 "hho"
#define SCNx8 "hhx"

#define SCNdFAST8 SCNd8
#define SCNiFAST8 SCNi8
#define SCNuFAST8 SCNu8
#define SCNoFAST8 SCNo8
#define SCNxFAST8 SCNx8

#define SCNdLEAST8 SCNd8
#define SCNiLEAST8 SCNi8
#define SCNuLEAST8 SCNu8
#define SCNoLEAST8 SCNo8
#define SCNxLEAST8 SCNx8

// 16 bits
#define SCNd16 "hd"
#define SCNi16 "hi"
#define SCNu16 "hu"
#define SCNo16 "ho"
#define SCNx16 "hx"

#define SCNdFAST16 SCNd16
#define SCNiFAST16 SCNi16
#define SCNuFAST16 SCNu16
#define SCNoFAST16 SCNo16
#define SCNxFAST16 SCNx16

#define SCNdLEAST16 SCNd16
#define SCNiLEAST16 SCNi16
#define SCNuLEAST16 SCNu16
#define SCNoLEAST16 SCNo16
#define SCNxLEAST16 SCNx16

// 32 bits
#define SCNd32 "I32d"
#define SCNi32 "I32i"
#define SCNu32 "I32u"
#define SCNo32 "I32o"
#define SCNx32 "I32x"

#define SCNdFAST32 SCNd32
#define SCNiFAST32 SCNi32
#define SCNuFAST32 SCNu32
#define SCNoFAST32 SCNo32
#define SCNxFAST32 SCNx32

#define SCNdLEAST32 SCNd32
#define SCNiLEAST32 SCNi32
#define SCNuLEAST32 SCNu32
#define SCNoLEAST32 SCNo32
#define SCNxLEAST32 SCNx32

// 64 bits
#define SCNd64 "I64d"
#define SCNi64 "I64i"
#define SCNu64 "I64u"
#define SCNo64 "I64o"
#define SCNx64 "I64x"

#define SCNdFAST64 SCNd64
#define SCNiFAST64 SCNi64
#define SCNuFAST64 SCNu64
#define SCNoFAST64 SCNo64
#define SCNxFAST64 SCNx64

#define SCNdLEAST64 SCNd64
#define SCNiLEAST64 SCNi64
#define SCNuLEAST64 SCNu64
#define SCNoLEAST64 SCNo64
#define SCNxLEAST64 SCNx64

// Maximum
#define SCNdMAX SCNd64
#define SCNiMAX SCNi64
#define SCNuMAX SCNu64
#define SCNoMAX SCNo64
#define SCNxMAX SCNx64

// Pointer
#define SCNdPTR "Id"
#define SCNiPTR "Ii"
#define SCNuPTR "Iu"
#define SCNoPTR "Io"
#define SCNxPTR "Ix"

// =============================================================================
// Types
// -----------------------------------------------------------------------------

typedef struct imaxdiv_s
{
  intmax_t quot;
  intmax_t rem;
} imaxdiv_t;

// =============================================================================
// Macros
// -----------------------------------------------------------------------------

#define strtoimax _strtoi64
#define wcstoimax _wcstoi64

#define strtoumax _strtoui64
#define wcstoumax _wcstoui64

// =============================================================================
// Functions
// -----------------------------------------------------------------------------

static inline imaxdiv_t imaxdiv (intmax_t numer, intmax_t denom)
{
  imaxdiv_t res;

  res.quot = numer / denom;
  res.rem = numer % denom;

  // Not needed for Microsoft C compiler
#if 0
  if ((numer < 0) && (res.rem > 0))
  {
    res.quot++;
    res.rem -= denom;
  }
#endif

  return res;
}

// -----------------------------------------------------------------------------

#endif // !(C_MSC_VER >= 1800)

// -----------------------------------------------------------------------------

#endif
