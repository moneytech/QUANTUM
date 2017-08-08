// =============================================================================
// <integer/convert/decimal/serialize/basic/intro.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

char_t* b = buf;

#if T(SIGN)
  // Check if the integer is negative
  // and compute its absolute value if it is
  bint neg = (val < 0);
  t_int uv = int_negif (val, neg);

  // Write the negative sign and advance the pointer if the value was actually
  // negative. Otherwise, the negative sign would simply be overwritten.
  *b = '-';
  b += neg;
#else
  t_int uv = val;
#endif
