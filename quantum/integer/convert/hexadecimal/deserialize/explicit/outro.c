// =============================================================================
// <integer/convert/hexadecimal/deserialize/explicit/outro.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#if T(VALID)
outro:
  // Integral overflow test
  if (unlikely (flags & 0x4u))
  {
    // Check if the last possible hexadecimal place is actually
    // a valid hexadecimal digit
    c = *str;

    if (unlikely (!chr_is_xdig (c)))
    {
invalid:
      out->end = (char_t*)str;
      out->err = int_parse_einput;

      goto done;
    }

  #if T(UNEVEN)
    // Check for overflow in the last possible hexadecimal place
    d = chr_xdig_to_int_fast (c);

    #if T(SIGN) && CPU(TWOS_COMPLEMENT)
      if (int_is_oflow_xdig (val, T_MAXVAL + (flags & 0x1u), d))
    #else
      if (int_is_oflow_xdig (val, T_MAXVAL, d))
    #endif
  #endif
    {
overflow:
      out->end = (char_t*)str;
      out->err = int_parse_erange;

      goto done;
    }

  #if T(UNEVEN)
    // No overflow
    val = (val << 4) | d;
    str++;

    // Check if the next character is a decimal digit.
    // If it is, then overflow happens for sure.
    // If it's not, then the integer ends.
    if (unlikely (flags & 0x2u))
    {
      c = *str;

      if (likely (!chr_is_xdig (c))) goto invalid;
      goto overflow;
    }
  #endif
  }

  // No overflow and no non-decimal character
  out->end = (char_t*)str;
  out->err = int_parse_ok;
#endif

done:
#if T(SIGN)
  // Negate the result if there was a negative sign
  #if T(VALID)
    val = int_negif (val, flags & 0x1u);
  #else
    val = int_negif (val, flags);
  #endif
#endif

return val;

#if T(VALID)
skip:
  // Parse the remaining hexadecimal digit characters
  int_from_xstri (val, str, {goto invalid;});
#endif
