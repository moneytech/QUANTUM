// =============================================================================
// <character/class.h>
//
// Classify individual characters.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_C498900871454E99A4859BACC6AF61A9
#define H_C498900871454E99A4859BACC6AF61A9

// -----------------------------------------------------------------------------
// Functions in this unit take advantage of unsigned integral wrap-around
// and use bitwise operations instead of logical ones to reduce the number
// of branches at the cost of no short-circuit boolean evaluation, which we
// hardly benefit from anyway. No lookup tables are used.
// -----------------------------------------------------------------------------

#include "../stdlib/ctype.h"

// =============================================================================
// Miscellaneous
// -----------------------------------------------------------------------------
// Test if a character is from ASCII range
static inline bint chr_is_ascii (uint c)
{
#if CPU(BRANCHES_SLOWLY)
  return !(c & ~0x7Fu);
#else
  return (c < 0x80u);
#endif
}

// =============================================================================
// Whitespace
// -----------------------------------------------------------------------------
// Test for a whitespace character of any kind
#define chr_is_wspace(c) ((uint)(c) <= (uint)' ')

// -----------------------------------------------------------------------------
// Test for any whitespace character, but treat the terminating null character
// as a non-whitespace character: to catch it in null-terminated strings,
// for example
static inline bint chr_is_wspace_zero (uint c)
{
#if CPU(X86)
  // XOR variant is slower on x86(-64)
  return (chr_is_wspace (c) & !!c);
#else
  return (chr_is_wspace (c) ^ !c);
#endif
}

// -----------------------------------------------------------------------------
// Equivalent of `isspace()`: test for ASCII whitespace characters
// ('\t', '\n', '\v', '\f', '\r' and ' ') with strict conformance
static inline bint chr_is_wspace_ascii (uint c)
{
#if 1
  return ((c == (uint)' ') | ((c - (uint)'\t') < 5u));
#else
  return ((c == (uint)' ') || ((c - (uint)'\t') < 5u));
#endif
}

#define chr_is_wspace_strict chr_is_wspace_ascii

// -----------------------------------------------------------------------------
// Equivalent of `isblank()`: test for the whitespace characters '\t' and ' '
static inline bint chr_is_wspace_blank (uint c)
{
#if 1
  return ((c == (uint)' ') | (c == (uint)'\t'));
#else
  return ((c == (uint)' ') || (c == (uint)'\t'));
#endif
}

// -----------------------------------------------------------------------------
// Opposite of `isblank()`: test for the remaining whitespace control codes only
// ('\n', '\v', '\f' and '\r')
static inline bint chr_is_wspace_ctrl (uint c)
{
#if 1
  return ((c - (uint)'\n') < 4u);
#else
  return ((c - (uint)'\n') < 4u);
#endif
}

// -----------------------------------------------------------------------------
// Test for the line breaking whitespace characters only
static inline bint chr_is_wspace_lnbrk (uint c)
{
#if 1
  return ((c == (uint)'\n') | (c == (uint)'\r'));
#else
  return ((c == (uint)'\n') || (c == (uint)'\r'));
#endif
}

// -----------------------------------------------------------------------------
// Version which doesn't accept the vertical tab `\v` and the form feed `\f`
// characters, which aren't in widespread use anymore
static inline bint chr_is_wspace_tnrs (uint c)
{
#if 1
  if (chr_is_wspace (c))
  {
  #if CPU(64BIT)
    return (0x100002600u >> c) & 1u;
  #else
    return ((c == (uint)' ') | (c == (uint)'\t') | (c == (uint)'\n') | (c == (uint)'\r'));
  #endif
  }

  return false;
#else
  return ((c == (uint)' ') || (c == (uint)'\t') || (c == (uint)'\n') || (c == (uint)'\r'));
#endif
}

// -----------------------------------------------------------------------------
// Version which also doesn't accept the carriage return `\r` character,
// which is used as part of a line ending sequence in Windows and Mac OS Classic
static inline bint chr_is_wspace_tns (uint c)
{
#if 1
  return ((c == (uint)' ') | ((c - (uint)'\t') < 2u));
#else
  return ((c == (uint)' ') || ((c - (uint)'\t') < 2u));
#endif
}

// =============================================================================
// Printable
// -----------------------------------------------------------------------------
// Fastest variant which tests for any printable character, but the DEL `0x7F`
// control character is considered to be printable as well
#define chr_is_print(c) ((uint)(c) >= (uint)' ')

// -----------------------------------------------------------------------------
// Equivalent of `isprint()`: test for printable characters in ASCII range only
static inline bint chr_is_print_ascii (uint c)
{
  return ((c - (uint)' ') < 95u);
}

// -----------------------------------------------------------------------------
// A slightly slower but better version which treats the DEL control character
// correctly and treats all characters from extended ASCII range as printable
// as well
static inline bint chr_is_print_strict (uint c)
{
#if 1
  #if CPU(BRANCHES_SLOWLY)
    return !!((c & 0xE0u) & (c ^ 0x7Fu));
  #else
    return (chr_is_print (c) & (c != 0x7Fu));
  #endif
#else
  return (chr_is_print (c) && (c != 0x7Fu));
#endif
}

// =============================================================================
// Graphical
// -----------------------------------------------------------------------------
// Fastest variant which tests for any graphical character, but the DEL `0x7F`
// control character is considered to be graphical as well
#define chr_is_graph(c) ((uint)(c) >= (uint)'!')

// -----------------------------------------------------------------------------
// Equivalent of `isgraph()`: test for graphical characters in ASCII range only
static inline bint chr_is_graph_ascii (uint c)
{
  return ((c - (uint)'!') < 94u);
}

// -----------------------------------------------------------------------------
// A slightly slower but better version which treats the DEL control character
// correctly and treats all characters from extended ASCII range as graphical
// as well
static inline bint chr_is_graph_strict (uint c)
{
#if 1
  return (chr_is_graph (c) & (c != 0x7Fu));
#else
  return (chr_is_graph (c) && (c != 0x7Fu));
#endif
}

// =============================================================================
// Numbers
// -----------------------------------------------------------------------------
// Test for the number sign
static inline bint chr_is_sign (uint c)
{
#if 1
  return ((c == (uint)'-') | (c == (uint)'+'));
#else
  return ((c + (c & 0x2u)) == (uint)'-');
#endif
}

// -----------------------------------------------------------------------------
// Test if a character is from the binary digit character range [0..1]
static inline bint chr_is_bdig (uint c)
{
#if CPU(BRANCHES_SLOWLY)
  return ((c | 1u) == (uint)'1');
#else
  return (chr_to_int (c) < 2u);
#endif
}

// -----------------------------------------------------------------------------
// Test if a character is from the octal digit character range [0..7]
static inline bint chr_is_odig (uint c)
{
#if 1
  return (chr_to_int (c) < 8u);
#else
  return ((c >= (uint)'0') && (c <= (uint)'7'));
#endif
}

// -----------------------------------------------------------------------------
// Equivalent of `isdigit()`: test if a character is from the decimal digit
// character range [0..9]
static inline bint chr_is_dig (uint c)
{
#if 1
  return (chr_to_int (c) < 10u);
#else
  return ((c >= (uint)'0') && (c <= (uint)'9'));
#endif
}

// -----------------------------------------------------------------------------
// Equivalent of `isxdigit()`: test if a character is from the hexadecimal
// digit character ranges [0..9], [A..F] or [a..f]
static inline bint chr_is_xdig (uint c)
{
#if 1
  return ((chr_to_int (c) < 10u)
  | ((chr_to_lcase_fast (c) - (uint)'a') < 6u));
#else
  return (((c >= (uint)'0') && (c <= (uint)'9'))
  || ((c >= (uint)'A') && (c <= (uint)'F'))
  || ((c >= (uint)'a') && (c <= (uint)'f')));
#endif
}

// -----------------------------------------------------------------------------
// Test for either the upper case `E` or the lower case `e` exponent character
#define chr_is_exp(c) (chr_to_lcase_fast (c) == (uint)'e')

// -----------------------------------------------------------------------------
// Test for either the upper case `P` or the lower case `p` power character
#define chr_is_pow(c) (chr_to_lcase_fast (c) == (uint)'p')

// =============================================================================
// Alphanumeric
// -----------------------------------------------------------------------------
// Equivalent of `isupper()`: test if a character is from the upper case
// character range [A..Z]
static inline bint chr_is_ucase (uint c)
{
#if 1
  return ((c - (uint)'A') < 26u);
#else
  return ((c >= (uint)'A') && (c <= (uint)'Z'));
#endif
}

// -----------------------------------------------------------------------------
// Equivalent of `islower()`: test if a character is from the lower case
// character range [a..z]
static inline bint chr_is_lcase (uint c)
{
#if 1
  return ((c - (uint)'a') < 26u);
#else
  return ((c >= (uint)'a') && (c <= (uint)'z'));
#endif
}

// -----------------------------------------------------------------------------
// Equivalent of `isalpha()`: test if a character is from the alphabetic
// character ranges [A..Z] and [a..z]
static inline bint chr_is_alpha (uint c)
{
  return chr_is_lcase (chr_to_lcase_fast (c));
}

// -----------------------------------------------------------------------------
// Equivalent of `isalnum()`: test if a character is from the alphanumeric
// character ranges [0..9], [A..Z] and [a..z]
static inline bint chr_is_alnum (uint c)
{
#if 1
  return ((chr_to_int (c) < 10u)
  | ((chr_to_lcase_fast (c) - (uint)'a') < 26u));
#else
  return (((c >= (uint)'0') && (c <= (uint)'9'))
  || ((c >= (uint)'A') && (c <= (uint)'Z'))
  || ((c >= (uint)'a') && (c <= (uint)'z')));
#endif
}

// =============================================================================
// Punctuation
// -----------------------------------------------------------------------------
// Equivalent of `ispunct()`: test if a character is from the punctuation
// character ranges [!../]. [:..@], [[..`] and [{..~]
static inline bint chr_is_punct (uint c)
{
#if 1
  return ((c >= (uint)'!') & !chr_is_alnum (c) & (c < 0x7Fu));
#else
  return (((c >= (uint)'!') && (c <= (uint)'/'))
  || ((c >= (uint)':') && (c <= (uint)'@'))
  || ((c >= (uint)'[') && (c <= (uint)'`'))
  || ((c >= (uint)'{') && (c <= (uint)'~')));
#endif
}

#define chr_is_punct_ascii chr_is_punct

// -----------------------------------------------------------------------------
// Version that treats characters from extended ASCII range as punctuation
static inline bint chr_is_punct_strict (uint c)
{
  if (chr_is_ascii (c)) return chr_is_punct (c);
  return true;
}

// =============================================================================
// Control
// -----------------------------------------------------------------------------
// Fastest variant which tests for any control character, but ignores
// the DEL `0x7F` control character
#define chr_is_cntrl(c) ((uint)(c) < (uint)' ')

// -----------------------------------------------------------------------------
// Equivalent of `iscntrl()`: test for ASCII control characters
static inline bint chr_is_cntrl_ascii (uint c)
{
#if 1
  #if CPU(BRANCHES_SLOWLY)
    return clamp ((c & 0x1Fu) | (c & 0x7Fu));
  #else
    return (chr_is_cntrl (c) | (c == 0x7Fu));
  #endif
#else
  return (chr_is_cntrl (c) || (c == 0x7Fu));
#endif
}

#define chr_is_cntrl_strict chr_is_cntrl_ascii

// -----------------------------------------------------------------------------

#endif
