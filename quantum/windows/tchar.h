// =============================================================================
// <windows/tchar.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_B592EF89D06F4B3C832A87ED03F3E891
#define H_B592EF89D06F4B3C832A87ED03F3E891

// -----------------------------------------------------------------------------

#include <Tchar.h>

// =============================================================================
// Constants
// -----------------------------------------------------------------------------

#define TEOF _TEOF

// =============================================================================
// Types
// -----------------------------------------------------------------------------

typedef _TCHAR tchar_t;
typedef _TSCHAR tschar_t;
typedef _TUCHAR tuchar_t;
typedef _TXCHAR txchar_t;

typedef _TINT tint_t;

// =============================================================================
// Macros
// -----------------------------------------------------------------------------

#define tmain _tmain
#define tWinMain _tWinMain

#define WinMain(hInst, hPrevInst, lpCmdLine, nShowCmd)\
  CALLBACK tWinMain (HINSTANCE hInst, HINSTANCE hPrevInst\
  , LPTSTR lpCmdLine, int nShowCmd)

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// <ctype.h>
#define istalnum _istalnum
#define istalpha _istalpha
#define istblank _istblank
#define istcntrl _istcntrl
#define istdigit _istdigit
#define istgraph _istgraph
#define istlower _istlower
#define istprint _istprint
#define istpunct _istpunct
#define istspace _istspace
#define istupper _istupper
#define istxdigit _istxdigit

#define totlower _totlower
#define totupper _totupper

// -----------------------------------------------------------------------------
// <inttypes.h>
#define tcstoimax _tcstoimax
#define tcstoumax _tcstoumax

// -----------------------------------------------------------------------------
// <locale.h>
#define tsetlocale _tsetlocale

// -----------------------------------------------------------------------------
// <stdio.h>
#define tremove _tremove
#define trename _trename
#define ttmpnam _ttmpnam
#define ttmpnam_s _ttmpnam_s

#define tfopen _tfopen
#define tfreopen _tfreopen

#define ftprintf _ftprintf
#define ftscanf _ftscanf
#define tprintf _tprintf
#define tscanf _tscanf
#define stprintf _stprintf
#define stscanf _stscanf
#define vftprintf _vftprintf
#define vftscanf _vftscanf
#define vtprintf _vtprintf
#define vtscanf _vtscanf
#define vstprintf _vstprintf
#define vstscanf _vstscanf

#define fgettc _fgettc
#define fgetts _fgetts
#define fputtc _fputtc
#define fputts _fputts
#define gettc _gettc
#define gettchar _gettchar
#define getts _getts
#define getts_s _getts_s
#define puttc _puttc
#define puttchar _puttchar
#define putts _putts
#define ungettc _ungettc

#define tperror _tperror

// -----------------------------------------------------------------------------
// <stdlib.h>
#define ttof _ttof
#define ttoi _ttoi
#define ttol _ttol
#define ttoi64 _ttoi64
#define tcstod _tcstod
#define tcstof _tcstof
#define tcstol _tcstol
#define tcstold _tcstold
#define tcstoi64 _tcstoi64
#define tcstoul _tcstoul
#define tcstoui64 _tcstoui64

#define tgetenv _tgetenv
#define tsystem _tsystem

#define itot _itot

// -----------------------------------------------------------------------------
// <string.h>
#define tcscpy _tcscpy
#define tcsncpy _tcsncpy
#define tcscat _tcscat
#define tcsncat _tcsncat

#define tcscmp _tcscmp
#define tcsicmp _tcsicmp
#define tcscoll _tcscoll
#define tcsncmp _tcsncmp
#define tcsnicmp _tcsnicmp
#define tcsxfrm _tcsxfrm

#define tcschr _tcschr
#define tcscspn _tcscspn
#define tcspbrk _tcspbrk
#define tcsrchr _tcsrchr
#define tcsspn _tcsspn
#define tcsstr _tcsstr
#define tcstok _tcstok
#define tcstok_s _tcstok_s

#define tcserror _tcserror
#define tcslen _tcslen

#define tcsdup _tcsdup

// -----------------------------------------------------------------------------
// <time.h>
#define tasctime _tasctime
#define tasctime_s _tasctime_s
#define tctime _tctime
#define tctime_s _tctime_s
#define tcsftime _tcsftime

// -----------------------------------------------------------------------------
// Posix
#define taccess _taccess
#define tchdir _tchdir
#define tchmod _tchmod
#define tcreat _tcreat
#define tfdopen _tfdopen
#define tfullpath _tfullpath
#define tgetcwd _tgetcwd
#define tmkdir _tmkdir
#define topen _topen
#define tpopen _tpopen
#define trmdir _trmdir
#define tstat _tstat
#define tunlink _tunlink

// -----------------------------------------------------------------------------
// Convert between `tchar_t*` and UTF-8 strings
// -----------------------------------------------------------------------------

#ifdef UNICODE

// -----------------------------------------------------------------------------
// Returns the number of UTF-8 characters (including the terminating null)
// copied to the buffer `out` of `outsz` size managed by the caller.
//
// If the `outsz` argument has zero value passed in, then the function returns
// the required number of byte characters (including the terminating null)
// needed for the `out` buffer to be in order to perform the conversion.
//
// Returns zero in case of an error.
static inline size_t tcsitoutf8 (const tchar_t* restrict in, u8* restrict out
, size_t outsz)
{
  return WideCharToMultiByte (CP_UTF8, 0, in, -1, out, outsz, null, null);
}

// -----------------------------------------------------------------------------
// Same as above, but the input string buffer isn't null-terminated and its
// size is provided explicitly
static inline size_t tcstoutf8 (const tchar_t* restrict in, size_t insz
, u8* restrict out, size_t outsz)
{
  return WideCharToMultiByte (CP_UTF8, 0, in, insz, out, outsz, null, null);
}

// -----------------------------------------------------------------------------
// Reverse the procedure and return the number of `tchar_t` characters
// -----------------------------------------------------------------------------

static inline size_t utf8totcsi (const u8* restrict in, tchar_t* restrict out
, size_t outsz)
{
  return MultiByteToWideChar (CP_UTF8, 0, in, -1, out, outsz);
}

static inline size_t utf8totcs (const u8* restrict in, size_t insz
, tchar_t* restrict out, size_t outsz)
{
  return MultiByteToWideChar (CP_UTF8, 0, in, insz, out, outsz);
}

// -----------------------------------------------------------------------------

#else // UNICODE ][

// -----------------------------------------------------------------------------

static inline size_t tcsitoutf8 (const tchar_t* restrict in, u8* restrict out
, size_t outsz)
{
  size_t bufsz = MultiByteToWideChar (CP_THREAD_ACP, 0, in, -1, null, 0);
  if (unlikely (bufsz == 0)) return 0;

  vla (wchar_t, buf, bufsz);
  MultiByteToWideChar (CP_THREAD_ACP, 0, in, -1, buf, bufsz);

  return WideCharToMultiByte (CP_UTF8, 0, buf, -1, out, outsz, null, null);
}

static inline size_t tcstoutf8 (const tchar_t* restrict in, size_t insz
, u8* restrict out, size_t outsz)
{
  size_t bufsz = MultiByteToWideChar (CP_THREAD_ACP, 0, in, insz, null, 0);
  if (unlikely (bufsz == 0)) return 0;

  vla (wchar_t, buf, bufsz);
  MultiByteToWideChar (CP_THREAD_ACP, 0, in, insz, buf, bufsz);

  return WideCharToMultiByte (CP_UTF8, 0, buf, bufsz, out, outsz, null, null);
}

// -----------------------------------------------------------------------------

static inline size_t utf8totcsi (const u8* restrict in, tchar_t* restrict out
, size_t outsz)
{
  size_t bufsz = MultiByteToWideChar (CP_UTF8, 0, in, -1, null, 0);
  if (bufsz == 0) return 0;

  vla (wchar_t, buf, bufsz);
  MultiByteToWideChar (CP_UTF8, 0, in, -1, buf, bufsz);

  return WideCharToMultiByte (CP_THREAD_ACP, 0, buf, -1, out, outsz, null, null);
}

static inline size_t utf8totcs (const u8* restrict in, size_t insz
, tchar_t* restrict out, size_t outsz)
{
  size_t bufsz = MultiByteToWideChar (CP_UTF8, 0, in, insz, null, 0);
  if (bufsz == 0) return 0;

  vla (wchar_t, buf, bufsz);
  MultiByteToWideChar (CP_UTF8, 0, in, insz, buf, bufsz);

  return WideCharToMultiByte (CP_THREAD_ACP, 0, buf, bufsz, out, outsz, null, null);
}

// -----------------------------------------------------------------------------

#endif // !UNICODE

// -----------------------------------------------------------------------------

#endif
