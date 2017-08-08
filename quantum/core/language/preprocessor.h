// =============================================================================
// <core/language/preprocessor.h>
//
// Common useful C preprocessor macros.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_B33012747F15442DA915AF34A9C42AA5
#define H_B33012747F15442DA915AF34A9C42AA5

// -----------------------------------------------------------------------------
// Consume the argument list
#define zap(...)

// -----------------------------------------------------------------------------
// Return the argument list unchanged
#define nop(...) (__VA_ARGS__)

// -----------------------------------------------------------------------------
// Semantic macros for label-based loops
#define loop(name) loop_##name:
#define repeat(name) goto loop_##name

// -----------------------------------------------------------------------------
// Repeat the expression multiple times
#define REPEAT4(e) e, e, e, e
#define REPEAT8(e) REPEAT4 (e), REPEAT4 (e)
#define REPEAT16(e) REPEAT8 (e), REPEAT8 (e)
#define REPEAT32(e) REPEAT16 (e), REPEAT16 (e)
#define REPEAT64(e) REPEAT32 (e), REPEAT32 (e)

// -----------------------------------------------------------------------------
// Stringification
// -----------------------------------------------------------------------------
// Stringify an expression
#define STRING(expr) #expr
// Stringify an expanded expression value
#define SSTRING(expr) STRING (expr)

// -----------------------------------------------------------------------------
// Concatenation
// -----------------------------------------------------------------------------
// Concatenate two expressions
#define JOIN(a, b) a##b
// Concatenate two expanded expression values
#define CONCAT(a, b) JOIN (a, b)

// -----------------------------------------------------------------------------
// Turn the decimal integer constant into hexadecimal
#define HEX(c) 0x##c##u
#define HEXL(c) 0x##c##ul
#define HEXLL(c) 0x##c##ull

// -----------------------------------------------------------------------------
// Work with binary (base 2) integral number constants
// -----------------------------------------------------------------------------

#define BINARY(b)\
(                \
  (((b) & 0x0000000Fu) ? 1u   : 0)\
+ (((b) & 0x000000F0u) ? 2u   : 0)\
+ (((b) & 0x00000F00u) ? 4u   : 0)\
+ (((b) & 0x0000F000u) ? 8u   : 0)\
+ (((b) & 0x000F0000u) ? 16u  : 0)\
+ (((b) & 0x00F00000u) ? 32u  : 0)\
+ (((b) & 0x0F000000u) ? 64u  : 0)\
+ (((b) & 0xF0000000u) ? 128u : 0)\
)

#define B8(b) (u8)BINARY (HEX (b))

#define B16(msb2, lsb1) (((u16)B8 (msb2) << 8) | (u16)B8 (lsb1))

#define B32(msb4, b3, b2, lsb1)\
(                       \
  ((u32)B8 (msb4) << 24)\
| ((u32)B8 (b3) << 16)\
| ((u32)B8 (b2) << 8)\
|  (u32)B8 (lsb1)\
)

#define B64(msb8, b7, b6, b5, b4, b3, b2, lsb1)\
(                       \
  ((u64)B8 (msb8) << 56)\
| ((u64)B8 (b7) << 48)\
| ((u64)B8 (b6) << 40)\
| ((u64)B8 (b5) << 32)\
| ((u64)B8 (b4) << 24)\
| ((u64)B8 (b3) << 16)\
| ((u64)B8 (b2) << 8)\
|  (u64)B8 (lsb1)\
)

// -----------------------------------------------------------------------------
// Function-like macros
// -----------------------------------------------------------------------------
// Minimum / maximum of two numbers
#define min2(a, b) (((a) < (b)) ? (a) : (b))
#define max2(a, b) (((a) > (b)) ? (a) : (b))

// -----------------------------------------------------------------------------
// Conditional negation of a number
#define negif(v, c) ((c) ? -(v) : (v))

// -----------------------------------------------------------------------------
// Debugging
#ifdef NDEBUG
  #define debug(fmt, ...)
#else
  #define debug(fmt, ...) fprintf (stderr, "[%s:%u] %s: " fmt "\n", __FILE__, __LINE__, __func__, __VA_ARGS__)
#endif

// -----------------------------------------------------------------------------

#endif
