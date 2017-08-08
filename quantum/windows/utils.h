// =============================================================================
// <windows/utils.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A0588637FE5A41678463BFE754C5E4E9
#define H_A0588637FE5A41678463BFE754C5E4E9

// -----------------------------------------------------------------------------

#include "../io.h"

// =============================================================================
// Constants
// -----------------------------------------------------------------------------

#ifndef WIN_FORMAT_MESSAGE_MAX
  #define WIN_FORMAT_MESSAGE_MAX 1024u
#endif

#if (WIN_FORMAT_MESSAGE_MAX < 256)
  #error "Invalid definition of `WIN_FORMAT_MESSAGE_MAX`"
#endif

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// 64-bit `MAKELONG`
#ifndef MAKELONGLONG
  #define MAKELONGLONG(hi, lo) (((DWORD64)(hi) << 32) | (lo))
#endif

// -----------------------------------------------------------------------------
// Get 64-bit file size from a `WIN32_FIND_DATA` structure
#define wfd_file_size(wfd) MAKELONGLONG ((wfd)->nFileSizeHigh, (wfd)->nFileSizeLow)

// -----------------------------------------------------------------------------
// Convert a Windows `FILETIME` structure time to UNIX timestamp
#define filetime_to_time(ft) ((MAKELONGLONG ((ft)->dwHighDateTime, (ft)->dwLowDateTime) - 116444736000000000u) / 10000000u)

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// Analog of `perror()` standard C function for WinAPI & WinSock calls
// -----------------------------------------------------------------------------
// Converts Windows error code to a meaningful error message string
// -----------------------------------------------------------------------------

#define win_formatmsg_a(buf, size, code)\
  FormatMessageA (FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS\
  , null, (DWORD)(code), MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT)\
  , (LPSTR)(msg), (DWORD)(size), null)

#define win_formatmsg_w(buf, size, code)\
  FormatMessageW (FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS\
  , null, (DWORD)(code), MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT)\
  , (LPWSTR)(msg), (DWORD)(size), null)

// -----------------------------------------------------------------------------
// Print the error to `stderr` (like `perror()` does)
// -----------------------------------------------------------------------------

#define win_error_print_a(str) win_error_print_internal_a (str ": %s [%u]\n", GetLastError())
#define win_sock_error_print_a(str) win_error_print_internal_a (str ": %s [%u]\n", WSAGetLastError())
#define win_error_code_print_a(str, code) win_error_print_internal_a (str ": %s [%u]\n", (code))

// -----------------------------------------------------------------------------
// Do not call directly
static inline void win_error_print_internal_a (const char_t* fmt, DWORD code)
{
  char_t msg[WIN_FORMAT_MESSAGE_MAX];

  DWORD num = win_formatmsg_a (msg, WIN_FORMAT_MESSAGE_MAX, code);

  if (unlikely (num == 0))
  {
    fprintf (stderr, "FormatMessage: %u [%u]\n", GetLastError(), code);
  }
  else
  {
    fprintf (stderr, fmt, msg, code);
  }
}

// -----------------------------------------------------------------------------
// Unicode version
// -----------------------------------------------------------------------------

#ifdef UNICODE

#define win_error_print_w(str) win_error_print_internal_w (str T(": %s [%u]\n"), GetLastError())
#define win_sock_error_print_w(str) win_error_print_internal_w (str T(": %s [%u]\n"), WSAGetLastError())
#define win_error_code_print_w(str, code) win_error_print_internal_w (str T(": %s [%u]\n"), (code))

// -----------------------------------------------------------------------------
// Do not call directly
static inline void win_error_print_internal_w (const wchar_t* fmt, DWORD code)
{
  wchar_t msg[WIN_FORMAT_MESSAGE_MAX];

  DWORD num = win_formatmsg_w (msg, WIN_FORMAT_MESSAGE_MAX, code);

  if (unlikely (num = 0))
  {
    fwprintf (stderr, T("FormatMessage: %u [%u]\n"), GetLastError(), code);
  }
  else
  {
    fwprintf (stderr, fmt, msg, code);
  }
}

#endif // UNICODE

// -----------------------------------------------------------------------------
// Show the error message box
// -----------------------------------------------------------------------------

#define win_error_box_a(str, cap, win, flags) win_error_box_internal_a (str ": %s [%u]\n", GetLastError(), (cap), (win), (flags))
#define win_sock_error_box_a(str, cap, win, flags) win_error_box_internal_a (str ": %s [%u]\n", WSAGetLastError(), (cap), (win), (flags))
#define win_error_code_box_a(str, code, cap, win, flags) win_error_box_internal_a (str ": %s [%u]\n", (code), (cap), (win), (flags))

// -----------------------------------------------------------------------------
// Do not call directly
static inline int win_error_box_internal_a (const char_t* fmt, DWORD code
, const char_t* title, HWND wnd, DWORD flags)
{
  char_t msg[WIN_FORMAT_MESSAGE_MAX];
  char_t buf[WIN_FORMAT_MESSAGE_MAX];

  DWORD num = win_formatmsg_a (msg, WIN_FORMAT_MESSAGE_MAX, code);

  if (unlikely (num == 0))
  {
    snprintf (buf, WIN_FORMAT_MESSAGE_MAX, "FormatMessage: %u [%u]\n"
    , GetLastError(), code);

    return MessageBoxA (wnd, buf, title, MB_ICONERROR | MB_OK | flags);
  }
  else
  {
    snprintf (buf, WIN_FORMAT_MESSAGE_MAX, fmt, msg, code);
    return MessageBoxA (wnd, buf, title, MB_ICONERROR | MB_OK | flags);
  }
}

// -----------------------------------------------------------------------------
// Unicode version
// -----------------------------------------------------------------------------

#ifdef UNICODE

#define win_error_box_w(str, cap, win, flags) win_error_box_internal_w (str T(": %s [%u]\n"), GetLastError(), (cap), (win), (flags))
#define win_sock_error_box_w(str, cap, win, flags) win_error_box_internal_w (str T(": %s [%u]\n"), WSAGetLastError(), (cap), (win), (flags))
#define win_error_code_box_w(str, code, cap, win, flags) win_error_box_internal_w (str T(": %s [%u]\n"), (code), (cap), (win), (flags))

// -----------------------------------------------------------------------------
// Do not call directly
static inline int win_error_box_internal_w (const wchar_t* fmt, DWORD code
, const wchar_t* title, HWND wnd, DWORD flags)
{
  wchar_t msg[WIN_FORMAT_MESSAGE_MAX];
  wchar_t buf[WIN_FORMAT_MESSAGE_MAX];

  DWORD num = win_formatmsg_w (msg, WIN_FORMAT_MESSAGE_MAX, code);

  if (unlikely (num == 0))
  {
    snwprintf (buf, WIN_FORMAT_MESSAGE_MAX, T("FormatMessage: %u [%u]\n")
    , GetLastError(), code);

    return MessageBoxW (wnd, buf, title, MB_ICONERROR | MB_OK | flags);
  }
  else
  {
    snwprintf (buf, WIN_FORMAT_MESSAGE_MAX, fmt, msg, code);
    return MessageBoxW (wnd, buf, title, MB_ICONERROR | MB_OK | flags);
  }
}

#endif // UNICODE

// -----------------------------------------------------------------------------

#ifdef UNICODE
  #define win_error_print win_error_print_w
  #define win_sock_error_print win_sock_error_print_w
  #define win_error_code_print win_error_code_print_w

  #define win_error_box win_error_box_w
  #define win_sock_error_box win_sock_error_box_w
  #define win_error_code_box win_error_code_box_w
#else
  #define win_error_print win_error_print_a
  #define win_sock_error_print win_sock_error_print_a
  #define win_error_code_print win_error_code_print_a

  #define win_error_box win_error_box_a
  #define win_sock_error_box win_sock_error_box_a
  #define win_error_code_box win_error_code_box_a
#endif

// -----------------------------------------------------------------------------

#undef win_formatmsg_a
#undef win_formatmsg_w

// -----------------------------------------------------------------------------
// Retrieve command line arguments for a GUI app
extern int win_args_get (tchar_t*** argv);

// -----------------------------------------------------------------------------
// Request a console window for a GUI app
extern bint win_console (bint rstdin, bint inherit);

// -----------------------------------------------------------------------------

#endif
