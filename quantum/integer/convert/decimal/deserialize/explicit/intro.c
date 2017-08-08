// =============================================================================
// <integer/convert/decimal/deserialize/explicit/intro.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

register uint c;
register uint d;

register t_int val = 0;
register uint flags = 0;

#if T(VALID)
  // No digits?
  if (unlikely (len == 0))
  {
    out->end = (char_t*)str;
    out->err = int_parse_einput;

    return 0;
  }
#endif

#if T(SIGN)
  // Get the sign if it's present
  #if !T(VALID)
    if (likely (len != 0))
  #endif
  {
    c = *str;

    bint sign = chr_is_sign (c);
    flags = sign & (c >> 2);

    str += sign;
    len -= sign;
  }
#endif

#if T(VALID)
  // Skip the leading zeros
  int_skip_zeros (str, len);

  // Determine if integral overflow test
  // must be performed in the end
  if (unlikely (len >= T_MAXDIG))
  {
    flags |= 0x4u | ((len > T_MAXDIG) << 1);

    // Parse no more than this number of decimal places
    // to avoid the overflow
    len = T_MAXDIG - 1u;
  }
#endif
