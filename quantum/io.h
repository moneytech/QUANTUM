// =============================================================================
// <io.h>
//
// Input / output routines.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_E30E85DB25DF4DE2B6BFD04ED3A34575
#define H_E30E85DB25DF4DE2B6BFD04ED3A34575

// -----------------------------------------------------------------------------

#include "stdlib/stdio.h"

#include <sys/types.h>
#include <fcntl.h>

#if OS(WIN32)
  #include <io.h>
  #include "windows/posix.h"
#else
  #include <unistd.h>
#endif

// =============================================================================
// Constants
// -----------------------------------------------------------------------------
// Standard I/O file descriptors
// -----------------------------------------------------------------------------
// `stdin`
#ifdef STDIN_FILENO
  #define STDIN STDIN_FILENO
#else
  #define STDIN 0
#endif

// `stdout`
#ifdef STDOUT_FILENO
  #define STDOUT STDOUT_FILENO
#else
  #define STDOUT 1
#endif

// `stderr`
#ifdef STDERR_FILENO
  #define STDERR STDERR_FILENO
#else
  #define STDERR 2
#endif

// -----------------------------------------------------------------------------
// `io_line_read()` error condition
#define IO_SIZE_ERROR SIZE_MAX

// =============================================================================
// Types
// -----------------------------------------------------------------------------

typedef int io_fd_t;
typedef FILE io_file_t;

typedef enum io_consume_flags_e
{
  io_consume_text = 1u << 0,
  io_consume_utf8 = 1u << 1,
  io_consume_part = 1u << 2
} io_consume_flags_t;

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// Read the entire file contents into the dynamically allocated buffer
extern bint io_file_consume (io_file_t* file, char_t** out, size_t* size
, io_consume_flags_t flags);

// -----------------------------------------------------------------------------
// Consume a stream in its entirety into the dynamically allocated buffer
extern bint io_stream_consume (io_file_t* stream, char_t** out, size_t* size
, io_consume_flags_t flags);

// -----------------------------------------------------------------------------
// Read a line of text from the standard input.
// Link with msvcr90 or higher on Windows (`-lmsvcr90` for Clang or GCC).
extern size_t io_line_read (char_t* str, size_t size);

// -----------------------------------------------------------------------------

#endif
