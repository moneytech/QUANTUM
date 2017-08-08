// =============================================================================
// <string/implicit/replace.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_C2588F92D6954B248A4EB713C202653C
#define H_C2588F92D6954B248A4EB713C202653C

// -----------------------------------------------------------------------------
// Character
// -----------------------------------------------------------------------------

extern char_t* stri_replace_chr (char_t* str, char_t old, char_t new);
extern char_t* stri_ireplace_chr (char_t* str, char_t old, char_t new);

// -----------------------------------------------------------------------------
// Character set
// -----------------------------------------------------------------------------

extern char_t* stri_replace_chr_set (char_t* str, const char_t* old, const char_t* new);
extern char_t* stri_ireplace_chr_set (char_t* str, const char_t* old, const char_t* new);

// -----------------------------------------------------------------------------

#endif
