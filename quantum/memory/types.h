// =============================================================================
// <memory/types.h>
//
// Basic memory types.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_D9971571A33742B499EB35950AC5215F
#define H_D9971571A33742B499EB35950AC5215F

// -----------------------------------------------------------------------------

typedef struct mem_s
{
  size_t size;
  void* buf;
} mem_t;

#define mem_make(buf, size) (mem_t){(size), (buf)}

#define mem_null mem_make (null, 0)

// -----------------------------------------------------------------------------

typedef struct mem_const_s
{
  size_t size;
  const void* buf;
} mem_const_t;

#define mem_const_make(buf, size) (mem_const_t){(size), (buf)}

#define mem_const_null mem_const_make (null, 0)

// -----------------------------------------------------------------------------

#endif
