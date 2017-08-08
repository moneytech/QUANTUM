// =============================================================================
// <integer/convert/decimal/deserialize/implicit/intro.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

register uint c;
register uint d;

register t_int val = 0;

#if T(VALID)
  register size_t len = 0;
#endif

#if T(SIGN)
  // Get the sign if it's present
  c = *str;

  bint sign = chr_is_sign (c);
  bint neg = sign & (c >> 2);

  str += sign;
#endif

#if T(VALID)
  // Skip the leading zeros
  int_skip_zerosi (str);
#endif
