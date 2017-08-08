// =============================================================================
// <integer/convert/hexadecimal/deserialize/implicit/outro.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#if T(VALID)
outro:
  // Check if the last possible hexadecimal place is actually
  // a valid hexadecimal digit
  c = *str;

  if (unlikely (!chr_is_xdig (c)))
  {
invalid:
    out->end = (char_t*)str;
    out->err = ((c == '\0') & (len != 0)) ? int_parse_ok : int_parse_einput;

    goto done;
  }

  #if T(UNEVEN)
    // Check for overflow in the last possible hexadecimal place
    d = chr_xdig_to_int_fast (c);

    #if T(SIGN) && CPU(TWOS_COMPLEMENT)
      if (int_is_oflow_xdig (val, T_MAXVAL + neg, d))
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

    // Check if the next character is a hexadecimal digit.
    // If it is, then overflow happens for sure.
    // If it's not, then the integer ends.
    c = *str;

    if (likely (!chr_is_xdig (c))) {c = *str; goto invalid;}
    goto overflow;
  #endif
#endif

done:
#if T(SIGN)
  // Negate the result if there was a negative sign
  val = int_negif (val, neg);
#endif

return val;

skip:
  // Parse the remaining hexadecimal digit characters
#if T(VALID)
  int_from_xstri (val, str, {c = *str; goto invalid;});
#else
  int_from_xstri (val, str, {goto done;});
#endif
