// =============================================================================
// <string/implicit/search.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_B7FCB91C13104AC6A16962B5F3DF1C14
#define H_B7FCB91C13104AC6A16962B5F3DF1C14

// -----------------------------------------------------------------------------

#include "../../array/implicit.h"
#include "../../stdlib/string.h"

#include "../types.h"
#include "../search.h"

#include "buffer.h"

// -----------------------------------------------------------------------------
// Character
// -----------------------------------------------------------------------------
// Equivalent of `strchr()`
// -----------------------------------------------------------------------------

#if NO(STDLIB)
extern char_t* stri_find_chr (const char_t* str, char_t chr);
#else
static inline char_t* stri_find_chr (const char_t* str, char_t chr)
{
  return strchr (str, chr);
}
#endif

extern char_t* stri_ifind_chr (const char_t* str, char_t chr);

// -----------------------------------------------------------------------------
// Equivalent of `strrchr()`
// -----------------------------------------------------------------------------

static inline char_t* stri_rfind_chr (const char_t* str, char_t chr)
{
#if NO(STDLIB)
  #define t_stri_length stri_length
  #define t_str_rfind_chr str_rfind_chr

  #include "search/character/backward/generic.c"
#else
  return strrchr (str, chr);
#endif
}

static inline char_t* stri_rifind_chr (const char_t* str, char_t chr)
{
  #define t_stri_length stri_length

  #define T_ICASE
  #define t_str_rfind_chr str_rifind_chr

  #include "search/character/backward/generic.c"
}

// -----------------------------------------------------------------------------

extern char_t* stri_token_chr (char_t** st, char_t chr);
extern char_t* stri_itoken_chr (char_t** st, char_t chr);

// -----------------------------------------------------------------------------
// String
// -----------------------------------------------------------------------------
// Equivalent of `strstr()`
// -----------------------------------------------------------------------------

#if NO(STDLIB)
extern char_t* stri_find_sub (const char_t* str, const char_t* sub);
#else
static inline char_t* stri_find_sub (const char_t* str, const char_t* sub)
{
  return strstr (str, sub);
}
#endif

extern char_t* stri_ifind_sub (const char_t* str, const char_t* sub);

// -----------------------------------------------------------------------------

static inline char_t* stri_rfind_sub (const char_t* str, const char_t* sub)
{
#if NO(STDLIB) || !HAVE(STRRSTR)
  #define t_stri_length stri_length
  #define t_str_rfind_sub str_rfind_sub

  #include "search/string/backward/generic.c"
#else
  return strrstr (str, sub);
#endif
}

static inline char_t* stri_rifind_sub (const char_t* str, const char_t* sub)
{
  #define t_stri_length stri_length

  #define T_ICASE
  #define t_str_rfind_sub str_rifind_sub

  #include "search/string/backward/generic.c"
}

// -----------------------------------------------------------------------------

extern char_t* stri_token_sub (char_t** st, const char_t* sub);
extern char_t* stri_itoken_sub (char_t** st, const char_t* sub);

// -----------------------------------------------------------------------------
// Character set
// -----------------------------------------------------------------------------

#if NO(STDLIB)
extern char_t* stri_find_chr_set (const char_t* str, const char_t* set);
#else
static inline char_t* stri_find_chr_set (const char_t* str, const char_t* set)
{
  return strpbrk (str, set);
}
#endif

extern char_t* stri_ifind_chr_set (const char_t* str, const char_t* set);

// -----------------------------------------------------------------------------

static inline char_t* stri_rfind_chr_set (const char_t* str, const char_t* set)
{
  #define t_stri_length stri_length
  #define t_str_rfind_chr_set str_rfind_chr_set

  #include "search/set/character/backward/generic.c"
}

static inline char_t* stri_rifind_chr_set (const char_t* str, const char_t* set)
{
  #define t_stri_length stri_length

  #define T_ICASE
  #define t_str_rfind_chr_set str_rifind_chr_set

  #include "search/set/character/backward/generic.c"
}

// -----------------------------------------------------------------------------

extern char_t* stri_token_chr_set (char_t** st, const char_t* set);
extern char_t* stri_itoken_chr_set (char_t** st, const char_t* set);

// -----------------------------------------------------------------------------
// String set
// -----------------------------------------------------------------------------

extern char_t* stri_find_sub_set (const char_t* str, const char_t* const* set);
extern char_t* stri_ifind_sub_set (const char_t* str, const char_t* const* set);

// -----------------------------------------------------------------------------

static inline char_t* stri_rfind_sub_set (const char_t* str, const char_t* const* set)
{
  #define t_stri_length stri_length
  #define t_str_rfind_sub_set str_rfind_sub_set

  #include "search/set/string/backward/generic.c"
}

static inline char_t* stri_rifind_sub_set (const char_t* str, const char_t* const* set)
{
  #define t_stri_length stri_length

  #define T_ICASE
  #define t_str_rfind_sub_set str_rifind_sub_set

  #include "search/set/string/backward/generic.c"
}

// -----------------------------------------------------------------------------

extern char_t* stri_token_sub_set (char_t** st, const char_t* const* set);
extern char_t* stri_itoken_sub_set (char_t** st, const char_t* const* set);

// -----------------------------------------------------------------------------

#endif
