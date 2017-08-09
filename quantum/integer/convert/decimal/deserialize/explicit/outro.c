// =============================================================================
// <integer/convert/decimal/deserialize/explicit/outro.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#if T(VALID)
outro:
  // Integral overflow test
  if (unlikely (flags & 0x4u))
  {
    // Check if the last possible decimal place is actually
    // a valid decimal digit
    c = *str;

    if (unlikely (!chr_is_dig (c)))
    {
invalid:
      out->end = (char_t*)str;
      out->err = int_parse_einput;

      goto done;
    }

    // Check for overflow in the last possible decimal place
    d = chr_dig_to_int (c);

  #if T(SIGN) && CPU(TWOS_COMPLEMENT)
    if (int_will_oflow_dig (val, T_MAXVAL + (flags & 0x1u), d))
  #else
    if (int_can_oflow_dig (val, T_MAXVAL)
    && int_will_oflow_dig (val, T_MAXVAL, d))
  #endif
    {
overflow:
      out->end = (char_t*)str;
      out->err = int_parse_erange;

      goto done;
    }

    // No overflow
    val = (val * 10u) + d;
    str++;

    // Check if the next character is a decimal digit.
    // If it is, then overflow happens for sure.
    // If it's not, then the integer ends.
    if (unlikely (flags & 0x2u))
    {
      c = *str;

      if (likely (!chr_is_dig (c))) goto invalid;
      goto overflow;
    }
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
  // Parse the remaining decimal digit characters
  int_from_stri (val, str, {goto invalid;});
#endif
