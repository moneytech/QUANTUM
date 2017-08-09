// =============================================================================
// <integer/convert/hexadecimal/deserialize/implicit/intro.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#if T(VALID)
  #if ((T_MAXBIT % 4) != 0)
    #define T_UNEVEN
  #endif

  #define t_valid(expr) expr
#else
  #define t_valid(expr)
#endif

// -----------------------------------------------------------------------------
// Parse `x` misaligned characters one at a time until the desired alignment
// is reached and check if they are valid hexadecimal digit characters
#define t_stri_align(align) do\
{                             \
  if ((align) == 2u)          \
  {                           \
    if (likely (!ptr_aligned (2u, str)))\
    {                         \
      c = *str;               \
      register uint d = chr_xdig_to_int (c);\
                              \
      if (unlikely (d > 0xFu)) {t_valid ({goto invalid;}); goto done;}\
      val = d;                \
                              \
      str++;                  \
      t_valid ({len++;});     \
    }                         \
  }                           \
  else                        \
  {                           \
    const char_t* ptr = ptr_align_ceil (align, str);\
                              \
    t_valid ({len += (size_t)(ptr - str);});\
    int_from_xstr (val, str, ptr, {t_valid ({c = *str; goto invalid;}); goto done;});\
  }                           \
                              \
  str = assume_aligned (align, str);\
} while (0)
