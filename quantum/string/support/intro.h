// =============================================================================
// <string/support/intro.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#if T(WIDE)
  #define T_CHAR_BIT WCHAR_BIT
  #define T_CHAR_MAX ~(wide_char_t)0

  #define t_char wide_char_t

  #define t_str_null wide_str_null
  #define t_str_make wide_str_make
#else
  #define T_CHAR_BIT CHAR_BIT
  #define T_CHAR_MAX UCHAR_MAX

  #define t_char char_t

  #define t_str_null str_null
  #define t_str_make str_make
#endif

// -----------------------------------------------------------------------------

#if CPU(UNALIGNED_ACCESS)\
&& CPU(64BIT) && HAVE(INT64) && T(64BIT) && (INT_BIT == 32)
  #define T_WORD_BIT 64u
  #define T_WORD_MAX UINT64_MAX

  #define t_word u64
#else
  #define T_WORD_BIT INT_BIT
  #define T_WORD_MAX UINT_MAX

  #define t_word uint
#endif
