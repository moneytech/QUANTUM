// =============================================================================
// <integer/convert/decimal/serialize/format/intro.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

// Get the formatting parameters
size_t flags = fmt.flags;
size_t pad = fmt.pad;
size_t min = fmt.min;

// Get the absolute integer value
#if T(SIGN)
  t_int mask = (val < 0) ? ~(t_int)0 : 0;
  t_int uv = t_int_abs (val);
#else
  t_int uv = val;
#endif

// Get the decimal integer length
size_t len = t_int_len (uv);

// Check if the zero must not be written,
// but write it anyway if the minimum number
// of decimal digit characters to write isn't zero
len -= (flags >> 3) & !min & !uv;

// Determine the total number of characters to write
size_t size = len;

// Determine the minimum number
// of decimal digit characters to write.
// See if it's larger than the actual integer length.
min -= min2 (size, min);
size += min;

// Check if the sign character must be written
bint sign = flags & !!len;

#if T(SIGN)
  sign |= mask & 0x1u;
#endif

size += sign;

// Determine the number of padding characters to write
pad -= min2 (size, pad);
size += pad;

// Determine the justification
size_t just = pad & ((flags >> 6) - 1u);
char_t* ptr = buf + just + sign + min + len;
char_t* p = just ? buf : ptr;

// Determine the sign character
#if T(SIGN)
  #if CPU(BRANCHES_SLOWLY)
    uint sc = ' ' | (0xBu >> ((flags & int_format_space) >> mask));
  #else
    uint sc = ((flags & int_format_space) >> mask) ? ' ' : '+';
  #endif
#else
  #if CPU(BRANCHES_SLOWLY)
    uint sc = ' ' | (0xBu >> (flags & int_format_space));
  #else
    uint sc = (flags & int_format_space) ? ' ' : '+';
  #endif
#endif

// Prefetch
buf[0] = '\0';

// Write the sign
#if T(SIGN)
  buf[just] = sc + (mask & 0x2u);
#else
  buf[just] = sc;
#endif

// Write the decimal digit characters
ptr -= len;
