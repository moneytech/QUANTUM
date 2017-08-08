// =============================================================================
// <io.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "build.h"
#include "core.h"

#include "unicode.h"
#include "memory.h"
#include "string/implicit.h"
#include "fs.h"

#include "io.h"

// =============================================================================
// Constants
// -----------------------------------------------------------------------------

#ifndef BUF_SIZE
  #define BUF_SIZE 4096u
#endif

#if (BUF_SIZE < 256)
  #error "Invalid definition of `BUF_SIZE`"
#endif

// =============================================================================
// Functions
// -----------------------------------------------------------------------------

bint io_file_consume (io_file_t* file, u8** out, size_t* size
, io_consume_flags_t flags)
{
  stat_t sb;

  u8* buf;
  u8* b;

  size_t sz;
  size_t rd;

  io_fd_t fd = fileno (file);

  bint text = flags & io_consume_text;
  uint utf8 = flags & io_consume_utf8;
  uint part = flags & io_consume_part;

#if OS(WIN32)
  // Put the file into binary mode on Windows
  if (unlikely (part)) if (unlikely (fflush (file) == EOF)) return false;
  if (unlikely (setmode (fd, O_BINARY) == -1)) return false;
#endif

  // Get the file size
#if OS(WIN32)
  off_t len = filelength (fd);

  if (unlikely (len == -1)) return false;

  sz = (size_t)len;
#else
  if (unlikely (fstat (fd, &sb) != 0)) return false;

  sz = (size_t)(sb.st_size);
#endif

  // Get the current file position
  if (unlikely (part))
  {
    off_t pos;

#if OS(WIN32)
    pos = tell (fd);
#else
    pos = lseek (fd, 0, SEEK_CUR);
#endif

    if (unlikely (pos == -1)) return false;

    sz -= (size_t)pos;
  }

  // Allocate the buffer
  buf = mem_alloc (sz + text);

  if (unlikely (buf == null)) return false;

  b = buf;
  rd = sz;

  // Skip the UTF-8 BOM if it's present
  if (unlikely (utf8))
  {
    if (likely (rd >= 3u))
    {
      if (unlikely (fread (b, 1u, 3u, file) != 3u)) goto error;
      rd -= 3u;

      if (buf_equal (b, utf8_bom, 3u)) sz -= 3u;
      else b += 3;

      if (unlikely (rd == 0)) goto done;
    }
  }

  // Read the entire contents of the file
  if (unlikely (fread (b, 1u, rd, file) != rd))
  {
error:
    mem_free (buf);
    errno = EIO;

    return false;
  }

  // Null-terminate
done:
  if (unlikely (text)) b[rd] = '\0';

  *out = buf;
  *size = sz;

  return true;
}

// -----------------------------------------------------------------------------

bint io_stream_consume (io_file_t* stream, u8** out, size_t* size
, io_consume_flags_t flags)
{
  u8* buf;
  u8* b;

  size_t sz;
  size_t ud;
  size_t rd;
  size_t nd;

  io_fd_t fd = fileno (stream);

  bint text = flags & io_consume_text;
  uint utf8 = flags & io_consume_utf8;
  uint part = flags & io_consume_part;

#if OS(WIN32)
  // Put the stream into binary mode on Windows
  if (unlikely (part)) if (unlikely (fflush (stream) == EOF)) return false;
  if (unlikely (setmode (fd, O_BINARY) == -1)) return false;
#endif

  // Allocate the buffer
  buf = mem_alloc (BUF_SIZE);

  if (unlikely (buf == null)) return false;

  b = buf;
  sz = BUF_SIZE;
  ud = 0;

  // Skip the UTF-8 BOM if it's present
  if (unlikely (utf8))
  {
    rd = fread (b, 1u, 3u, stream);

    if (unlikely (rd < 3u))
    {
      if (unlikely (!feof (stream)))
      {
error_io:
        mem_free (buf);
        errno = EIO;

        return false;
      }

      // Null-terminate
      if (unlikely (text))
      {
        b = mem_realloc (buf, rd + 1u);

        if (unlikely (b == null))
        {
error_mem:
          mem_free (buf);
          return false;
        }

        b[rd] = '\0';
      }

      *out = buf;
      *size = rd;

      return true;
    }

    if (!buf_equal (b, utf8_bom, 3u))
    {
      b += 3;
      ud = 3u;
    }
  }

  // Read from the stream until it ends
  while (true)
  {
    nd = sz - ud;
    rd = fread (b, 1u, nd, stream);

    if (unlikely (rd != nd))
    {
      if (likely (feof (stream)))
      {
done:
        ud += rd;

        // Null-terminate
        if (unlikely (text))
        {
          b = mem_realloc (buf, ud + 1u);

          if (unlikely (b == null)) goto error_mem;

          b[ud] = '\0';
        }

        *out = b;
        *size = ud;

        return true;
      }

      goto error_io;
    }

    if (unlikely (feof (stream))) goto done;

    ud = sz;
    sz *= 2u;

    b = mem_realloc (buf, sz);

    if (unlikely (b == null)) goto error_mem;

    buf = b;
    b += ud;
  }
}

// -----------------------------------------------------------------------------

size_t io_line_read (char_t* str, size_t size)
{
#if HAVE(C11) || OS(WIN32)
  if (gets_s (str, size) == null) return IO_SIZE_ERROR;

  return stri_length (str);
#else
  if (fgets (str, size, stdin) == null) return IO_SIZE_ERROR;

  size_t len = stri_length (str);

  #if OS(WIN32)
    if (len > 1u)
    {
      if (str[len - 1] == '\n') len--;
      if (str[len - 1] == '\r') len--;
    }
  #else
    if (len != 0)
    {
      if (str[len - 1] == '\n') len--;
    }
  #endif

  str[len] = '\0';

  return len;
#endif
}
