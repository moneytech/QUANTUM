// =============================================================================
// <integer/convert/decimal/deserialize/implicit/outro.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#if T(VALID)
outro:
  // Check if the last possible decimal place is actually
  // a valid decimal digit
  c = *str;

  if (unlikely (!chr_is_dig (c)))
  {
invalid:
    out->end = (char_t*)str;
    out->err = ((c == '\0') & (len != 0)) ? int_parse_ok : int_parse_einput;

    goto done;
  }

  // Check for overflow in the last possible decimal place
  d = chr_dig_to_int (c);

  #if T(SIGN) && CPU(TWOS_COMPLEMENT)
    if (int_will_oflow_dig (val, T_MAXVAL + neg, d))
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
  c = *str;

  if (likely (!chr_is_dig (c))) {c = *str; goto invalid;}
  goto overflow;
#endif

done:
#if T(SIGN)
  // Negate the result if there was a negative sign
  val = int_negif (val, neg);
#endif

return val;

skip:
  // Parse the remaining decimal digit characters
#if T(VALID)
  int_from_stri (val, str, {c = *str; goto invalid;});
#else
  int_from_stri (val, str, {goto done;});
#endif
