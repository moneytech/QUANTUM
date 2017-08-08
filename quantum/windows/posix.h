// =============================================================================
// <windows/posix.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A063100459E847F08D23B2DCC6141E00
#define H_A063100459E847F08D23B2DCC6141E00

// =============================================================================
// Constants
// -----------------------------------------------------------------------------
// `access()` modes
// -----------------------------------------------------------------------------

#if C(MINGW)
  // MinGW messes up definitions
  #undef F_OK
  #undef W_OK
  #undef R_OK
  #undef X_OK
#endif

#define F_OK 0
#define W_OK 0x2u
#define R_OK 0x4u
// Windows doesn't have the executable `access()` mode
#define X_OK 0

// -----------------------------------------------------------------------------
// `creat()` and `open()` file descriptor flags
// -----------------------------------------------------------------------------

#define O_CREAT _O_CREAT
#define O_TRUNC _O_TRUNC
#define O_APPEND _O_APPEND

// Additional flags for `O_CREAT`
#define O_EXCL _O_EXCL
#define O_SHORT_LIVED _O_SHORT_LIVED
#define O_TEMPORARY _O_TEMPORARY

#define O_RDONLY _O_RDONLY
#define O_WRONLY _O_WRONLY
#define O_RDWR _O_RDWR

#define O_SEQUENTIAL _O_SEQUENTIAL
#define O_RANDOM _O_RANDOM

#define O_NOINHERIT _O_NOINHERIT

#define O_BINARY _O_BINARY

#define O_TEXT _O_TEXT
#define O_WTEXT _O_WTEXT

#define O_U8TEXT _O_U8TEXT
#define O_U16TEXT _O_U16TEXT

// -----------------------------------------------------------------------------
// `wfopen()` Unicode encoding translation modes
// -----------------------------------------------------------------------------

#define WFO_UTF8 T(",ccs=UTF-8")
#define WFO_UTF16 T(",ccs=UTF-16LE")
#define WFO_UNICODE T(",ccs=UNICODE")

// =============================================================================
// Macros
// -----------------------------------------------------------------------------

#define access _access
#define waccess _waccess

#define chdir _chdir
#define wchdir _wchdir

#define fstat _fstat64

#define fullpath _fullpath
#define wfullpath _wfullpath

#define getcwd _getcwd
#define wgetcwd _wgetcwd

#define mkdir _mkdir
#define wmkdir _wmkdir

#define rmdir _rmdir
#define wrmdir _wrmdir

#define stat(path, buffer) _stat64 (path, buffer)
#define wstat _wstat64

#define unlink _unlink
#define wunlink _wunlink

// -----------------------------------------------------------------------------

#define close _close

#define creat _creat
#define wcreat _wcreat

#if !C(MINGW)
  #define filelength _filelengthi64
#endif

#define fileno _fileno
#define isatty _isatty

#if !C(MINGW)
  #define lseek _lseeki64
#endif

#define open _open
#define wopen _wopen

#define popen _popen
#define wpopen _wpopen

#define pclose _pclose

#define pipe _pipe
#define read _read
#define setmode _setmode

#if !C(MINGW)
  #define tell _telli64
#endif

#define write _write

// -----------------------------------------------------------------------------

#endif
