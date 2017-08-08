// =============================================================================
// <core/build/windows.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_F412510807D54C8E96AA1076A509B808
#define H_F412510807D54C8E96AA1076A509B808

// -----------------------------------------------------------------------------
// Minimum Windows version targeted
// -----------------------------------------------------------------------------

#if !defined(WINVER) && !defined(_WIN32_WINNT)
  #ifndef WINNT_VER
    // Windows 7
    #define WINNT_VER 0x0601
  #endif

  #define WINVER WINNT_VER
  #define _WIN32_WINNT WINNT_VER
#endif

// -----------------------------------------------------------------------------
// Minimum C runtime version targeted (for MinGW)
// -----------------------------------------------------------------------------

#if C(MINGW) && !defined(__MSVCRT_VERSION__)
  #ifndef MSVCRT_VER
    // msvcr120.dll from Visual Studio 2013 (`-lmsvcr120` for Clang or GCC)
    #define MSVCRT_VER 0x1200
  #endif

  #define __MSVCRT_VERSION__ MSVCRT_VER
#endif

// -----------------------------------------------------------------------------
// Define the CRT macros for Unicode and MBCS builds
// -----------------------------------------------------------------------------

#if defined(UNICODE) && !defined(_UNICODE)
  #define _UNICODE
#elif defined(MBCS) && !defined(_MBCS)
  #define _MBCS
#endif

// -----------------------------------------------------------------------------

#endif
