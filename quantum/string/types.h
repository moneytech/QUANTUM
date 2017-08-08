// =============================================================================
// <string/types.h>
//
// Basic string types.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_F0788F682D844AB187D939A32320ED1D
#define H_F0788F682D844AB187D939A32320ED1D

// -----------------------------------------------------------------------------

typedef struct str_s
{
  size_t len;
  char_t* buf;
} str_t;

#define str_make(buf, len) (str_t){(len), (buf)}

#define str_from_stri(str) str_make ((str), stri_length (str))

#define str_null str_make (null, 0)

// -----------------------------------------------------------------------------

typedef struct str_const_s
{
  size_t len;
  const char_t* buf;
} str_const_t;

#define str_const_make(buf, len) (str_const_t){(len), (buf)}

#define str_const_from_stri(str) str_const_make ((str), stri_length (str))
#define str_const_from_cstr(str) str_const_make ((str), cstrlen (str))

#define str_const_null str_const_make (null, 0)

// -----------------------------------------------------------------------------

#endif
