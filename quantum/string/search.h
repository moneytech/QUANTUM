// =============================================================================
// <string/search.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A000E5417EC5423C9E886E014B50F7FC
#define H_A000E5417EC5423C9E886E014B50F7FC

// =============================================================================
// Character
// -----------------------------------------------------------------------------
// Equivalent of `memchr()`: search for a particular byte in a buffer
// -----------------------------------------------------------------------------

#if NO(STDLIB)
extern char_t* str_find_chr (const char_t* buf, size_t size, char_t chr);
#else
static inline char_t* str_find_chr (const char_t* buf, size_t size, char_t chr)
{
  return memchr ((const void*)buf, chr, size);
}
#endif

extern char_t* str_ifind_chr (const char_t* buf, size_t size, char_t chr);

// -----------------------------------------------------------------------------
// Equivalent of `memrchr()`: perform the search backwards
// -----------------------------------------------------------------------------

#if NO(STDLIB) || !HAVE(MEMRCHR)
extern char_t* str_rfind_chr (const char_t* buf, size_t size, char_t chr);
#else
static inline char_t* str_rfind_chr (const char_t* buf, size_t size, char_t chr)
{
  return memrchr ((const void*)buf, chr, size);
}
#endif

extern char_t* str_rifind_chr (const char_t* buf, size_t size, char_t chr);

// -----------------------------------------------------------------------------

extern str_t str_token_chr (str_t* st, char_t chr);
extern str_t str_itoken_chr (str_t* st, char_t chr);

// =============================================================================
// String
// -----------------------------------------------------------------------------
// Equivalent of `memmem()`: search for a byte sequence in a buffer
// -----------------------------------------------------------------------------

#if NO(STDLIB) || !HAVE(MEMMEM)
extern char_t* str_find_sub (const char_t* buf, size_t bufsz
, const char_t* sub, size_t subsz);
#else
static inline char_t* str_find_sub (const char_t* buf, size_t bufsz
, const char_t* sub, size_t subsz)
{
  return memmem ((const void*)buf, bufsz, (const void*)sub, subsz);
}
#endif

extern char_t* str_ifind_sub (const char_t* buf, size_t bufsz
, const char_t* sub, size_t subsz);

// -----------------------------------------------------------------------------
// Equivalent of `memrmem()`: perform the search backwards
// -----------------------------------------------------------------------------

#if NO(STDLIB) || !HAVE(MEMRMEM)
extern char_t* str_rfind_sub (const char_t* buf, size_t bufsz
, const char_t* sub, size_t subsz);
#else
static inline char_t* str_rfind_sub (const char_t* buf, size_t bufsz
, const char_t* sub, size_t subsz)
{
  return memrmem ((const void*)buf, bufsz, (const void*)sub, subsz);
}
#endif

extern char_t* str_rifind_sub (const char_t* buf, size_t bufsz
, const char_t* sub, size_t subsz);

// -----------------------------------------------------------------------------

extern str_t str_token_sub (str_t* st, const char_t* sub, size_t subsz);
extern str_t str_itoken_sub (str_t* st, const char_t* sub, size_t subsz);

// =============================================================================
// Character set
// -----------------------------------------------------------------------------

extern char_t* str_find_chr_set (const char_t* buf, size_t bufsz
, const char_t* set, size_t setsz);

extern char_t* str_ifind_chr_set (const char_t* buf, size_t bufsz
, const char_t* set, size_t setsz);

// -----------------------------------------------------------------------------

extern char_t* str_rfind_chr_set (const char_t* buf, size_t bufsz
, const char_t* set, size_t setsz);

extern char_t* str_rifind_chr_set (const char_t* buf, size_t bufsz
, const char_t* set, size_t setsz);

// -----------------------------------------------------------------------------

extern str_t str_token_chr_set (str_t* st, const char_t* set, size_t setsz);
extern str_t str_itoken_chr_set (str_t* st, const char_t* set, size_t setsz);

// =============================================================================
// String set
// -----------------------------------------------------------------------------

extern char_t* str_find_sub_set (const char_t* buf, size_t bufsz
, const str_const_t* set, size_t setsz, size_t* idx);

extern char_t* str_ifind_sub_set (const char_t* buf, size_t bufsz
, const str_const_t* set, size_t setsz, size_t* idx);

// -----------------------------------------------------------------------------

extern char_t* str_rfind_sub_set (const char_t* buf, size_t bufsz
, const str_const_t* set, size_t setsz, size_t* idx);

extern char_t* str_rifind_sub_set (const char_t* buf, size_t bufsz
, const str_const_t* set, size_t setsz, size_t* idx);

// -----------------------------------------------------------------------------

extern str_t str_token_sub_set (str_t* st, const str_const_t* set, size_t setsz);
extern str_t str_itoken_sub_set (str_t* st, const str_const_t* set, size_t setsz);

// -----------------------------------------------------------------------------

#endif
