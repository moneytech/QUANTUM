// =============================================================================
// <core/platform/os.h>
//
// Compile-time operating system detection.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_E933C36BFDD54DB8A5B047C37F93C0A0
#define H_E933C36BFDD54DB8A5B047C37F93C0A0

// -----------------------------------------------------------------------------

#define OS(feat) (defined(OS_##feat))

// -----------------------------------------------------------------------------
// macOS / iOS
#if defined(__APPLE__)
  #include <TargetConditionals.h>

  // macOS
  #if defined(TARGET_OS_MAC)
    #define OS_MACOS
  // iOS
  #elif defined(TARGET_OS_IPHONE)
    #define OS_IOS
  #endif

// -----------------------------------------------------------------------------
// BSDs
#elif defined(__FreeBSD__)
  #define OS_FREEBSD
#elif defined(__NetBSD__)
  #define OS_NETBSD
#elif defined(__OpenBSD__)
  #define OS_OPENBSD
#elif defined(__DragonFly__)
  #define OS_DRAGONFLYBSD

// -----------------------------------------------------------------------------
// Linux-based
#elif defined(__linux__)
  #define OS_LINUX

// -----------------------------------------------------------------------------
// UNIX-compatible
#elif defined(__unix__)
  #define OS_UNIX

// -----------------------------------------------------------------------------
// Windows
#elif defined(_WIN32)
  #define OS_WIN32

  // 64-bit
  #if defined(_WIN64)
    #define OS_WIN64
  #endif
#endif

// -----------------------------------------------------------------------------
// Cygwin POSIX emulation layer for Windows
#if defined(__CYGWIN__)
  #define OS_CYGWIN
#endif

// -----------------------------------------------------------------------------
// BSD
#if OS(FREEBSD) || OS(NETBSD) || OS(OPENBSD) || OS(DRAGONFLYBSD)
  #define OS_BSD
#endif

// -----------------------------------------------------------------------------
// UNIX
#if defined(__unix__) || OS(MACOS) || OS(IOS) || OS(BSD) || OS(LINUX)
  #define OS_UNIX
#endif

// -----------------------------------------------------------------------------
// POSIX
#if defined(__posix__) || OS(UNIX) || OS(CYGWIN)
  #define OS_POSIX
#endif

// -----------------------------------------------------------------------------
// Windows uses the "\r\n" character sequence as a new line separator,
// while the rest of sane world uses just single '\n' character.
// Mac OS Classic uses "\n\r" but it's a coprolite.
#if OS(WIN32)
  #define OS_EOL "\r\n"
#else
  #define OS_EOL "\n"
#endif

// -----------------------------------------------------------------------------
// Windows uses the back slash as a path separator character.
// Forward slashes are preferred almost everywhere else.
#if OS(WIN32) && !OS(CYGWIN)
  #define OS_PATH_SEP_CHR '\\'
  #define OS_PATH_SEP_STR "\\"
#else
  #define OS_PATH_SEP_CHR '/'
  #define OS_PATH_SEP_STR "/"
#endif

// -----------------------------------------------------------------------------

#endif
