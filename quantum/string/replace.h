// =============================================================================
// <string/replace.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_D3458F7536A24F9E80810DFA57D548BA
#define H_D3458F7536A24F9E80810DFA57D548BA

// -----------------------------------------------------------------------------
// Character
// -----------------------------------------------------------------------------

extern void str_replace_chr (char_t* buf, size_t size, char_t old, char_t new);
extern void str_ireplace_chr (char_t* buf, size_t size, char_t old, char_t new);

// -----------------------------------------------------------------------------
// String
// -----------------------------------------------------------------------------

extern void str_replace_sub (char_t* buf, size_t bufsz
, const char_t* old, const char_t* new, size_t subsz);

extern void str_ireplace_sub (char_t* buf, size_t bufsz
, const char_t* old, const char_t* new, size_t subsz);

// -----------------------------------------------------------------------------
// Character set
// -----------------------------------------------------------------------------

extern void str_replace_chr_set (char_t* buf, size_t bufsz
, const char_t* old, const char_t* new, size_t setsz);

extern void str_ireplace_chr_set (char_t* buf, size_t bufsz
, const char_t* old, const char_t* new, size_t setsz);

// -----------------------------------------------------------------------------
// String set
// -----------------------------------------------------------------------------

extern void str_replace_sub_set (char_t* buf, size_t bufsz
, const str_const_t* old, const char_t* const* new, size_t setsz);

extern void str_ireplace_sub_set (char_t* buf, size_t bufsz
, const str_const_t* old, const char_t* const* new, size_t setsz);

// -----------------------------------------------------------------------------

#endif
