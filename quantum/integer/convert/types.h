// =============================================================================
// <integer/convert/types.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_DEC61E590B21427B98ED4DB9D1D0C25E
#define H_DEC61E590B21427B98ED4DB9D1D0C25E

// -----------------------------------------------------------------------------

typedef enum int_parse_err_e
{
  int_parse_ok,
  int_parse_einput,
  int_parse_erange
} int_parse_err_t;

typedef struct int_parse_s
{
  char_t* end;
  int_parse_err_t err;
} int_parse_t;

// -----------------------------------------------------------------------------

typedef enum int_format_flags_e
{
  int_format_sign = 1u << 0,
  int_format_space = 1u << 2,
  int_format_pad_zero = 1u << 4,
  int_format_omit_zero = 1u << 3,
  int_format_prefix = 1u << 1,
  int_format_lcase = 1u << 5,
  int_format_left = 1u << 6
} int_format_flags_t;

typedef struct int_format_s
{
  int_format_flags_t flags;
  size_t pad;
  size_t min;
} int_format_t;

// -----------------------------------------------------------------------------

#endif
