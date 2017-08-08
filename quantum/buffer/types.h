// =============================================================================
// <buffer/types.h>
//
// Basic buffer types.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_D805D7E23B204433ADBCDC607E87CC4F
#define H_D805D7E23B204433ADBCDC607E87CC4F

// -----------------------------------------------------------------------------

typedef struct buf_s
{
  size_t size;
  byte* buf;
} buf_t;

#define buf_make(buf, size) (buf_t){(size), (buf)}

#define buf_null buf_make (null, 0)

// -----------------------------------------------------------------------------

typedef struct buf_const_s
{
  size_t size;
  const byte* buf;
} buf_const_t;

#define buf_const_make(buf, size) (buf_const_t){(size), (buf)}

#define buf_const_null buf_const_make (null, 0)

// -----------------------------------------------------------------------------

#endif
