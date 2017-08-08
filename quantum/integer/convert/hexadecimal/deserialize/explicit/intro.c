// =============================================================================
// <integer/convert/hexadecimal/deserialize/explicit/intro.c>
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

// Skip the hexadecimal prefix
if (likely (len > 2u))
{
#if CPU(UNALIGNED_ACCESS) && HAVE(INT16)
  #if CPU(LITTLE_ENDIAN)
    if (unlikely ((*(u16*)str | 0x2000u) == 0x7830u))
  #else
    if (unlikely ((*(u16*)str | 0x0020u) == 0x3078u))
  #endif
#else
  if (unlikely ((str[0] == '0') & (chr_to_lcase_fast (str[1]) == 'x')))
#endif
  {
    str += 2u;
    len -= 2u;
  }
}

#if T(VALID)
  // Skip the leading zeros
  int_skip_zeros (str, len);

  #if T(UNEVEN)
    // Determine if integral overflow test
    // must be performed in the end
    if (unlikely (len >= T_MAXDIG))
    {
      flags |= 0x4u | ((len > T_MAXDIG) << 1);

      // Parse no more than this number of decimal places
      // to avoid the overflow
      len = T_MAXDIG - 1u;
    }
  #else
    flags |= ((len > T_MAXDIG) << 1);
  #endif
#endif
