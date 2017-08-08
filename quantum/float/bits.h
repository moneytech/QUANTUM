// =============================================================================
// <float/bits.h>
//
// Examine the binary representation of floating point numbers.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_DEB77D1613DA411689EB78420A031410
#define H_DEB77D1613DA411689EB78420A031410

// -----------------------------------------------------------------------------

#include "../bswap.h"

// -----------------------------------------------------------------------------

#if FP(IEEE754)

// -----------------------------------------------------------------------------
// 32-bit binary representation
#if HAVE(FLT32) && HAVE(INT32)
static inline void flt_f32_bits (uchar* b, f32 f)
{
  u32 u = *(u32*)&f;

#if FP(DIFFERENT_ENDIAN)
  u = bswap32 (u);
#endif

  // Sign bit
  b[0] = chr_bdig_from_int (bit_is_set (u, 31));
  b[1] = ' ';
  u <<= 1;

  // Exponent bits
  for (uint i = 2u; i < 10u; i++)
  {
    b[i] = chr_bdig_from_int (bit_is_set (u, 31));
    u <<= 1;
  }

  b[11] = ' ';

  // Mantissa bits
  for (uint i = 12u; i < 35u; i++)
  {
    b[i] = chr_bdig_from_int (bit_is_set (u, 31));
    u <<= 1;
  }

  // Null-terminate
  b[36] = '\0';
}
#endif // HAVE(FLT32) && HAVE(INT32)

// -----------------------------------------------------------------------------
// 64-bit binary representation
#if HAVE(FLT64) && HAVE(INT64)
static inline void flt_f64_bits (uchar* b, f64 f)
{
  u64 u = *(u64*)&f;

#if FP(DIFFERENT_ENDIAN)
  u = bswap64 (u);
#endif

  // Sign bit
  b[0] = chr_bdig_from_int (bit_is_set (u, 63));
  b[1] = ' ';
  u <<= 1;

  // Exponent bits
  for (uint i = 2u; i < 13u; i++)
  {
    b[i] = chr_bdig_from_int (bit_is_set (u, 63));
    u <<= 1;
  }

  b[13] = ' ';

  // Mantissa bits
  for (uint i = 14u; i < 66u; i++)
  {
    b[i] = chr_bdig_from_int (bit_is_set (u, 63));
    u <<= 1;
  }

  // Null-terminate
  b[66] = '\0';
}
#endif // HAVE(FLT64) && HAVE(INT64)

// -----------------------------------------------------------------------------
// 80-bit binary representation
#if HAVE(FLT80) && HAVE(INT32)
static inline void flt_f80_bits (uchar* b, f80 f)
{
#if FP(LITTLE_ENDIAN)
  u32 u = *((u32*)&f + 2);
#else
  u32 u = *(u32*)&f;
#endif

#if FP(DIFFERENT_ENDIAN)
  u = bswap32 (u);
#endif

#if FP(LITTLE_ENDIAN)
  // Shift out junk
  u <<= 16;
#endif

  // Sign bit
  b[0] = chr_bdig_from_int (bit_is_set (u, 31));
  b[1] = ' ';
  u <<= 1;

  // Exponent bits
  for (uint i = 2u; i < 17u; i++)
  {
    b[i] = chr_bdig_from_int (bit_is_set (u, 31));
    u <<= 1;
  }

  b[17] = ' ';

  // Next chunk
  u = *((u32*)&f + 1);

#if FP(DIFFERENT_ENDIAN)
  u = bswap32 (u);
#endif

  // Mantissa bits
  for (uint i = 18u; i < 50u; i++)
  {
    b[i] = chr_bdig_from_int (bit_is_set (u, 31));
    u <<= 1;
  }

  // Next chunk
#if FP(LITTLE_ENDIAN)
  u = *(u32*)&f;
#else
  u = *((u32*)&f + 2);
#endif

#if FP(DIFFERENT_ENDIAN)
  u = bswap32 (u);
#endif

  for (uint i = 50u; i < 82u; i++)
  {
    b[i] = chr_bdig_from_int (bit_is_set (u, 31));
    u <<= 1;
  }

  // Null-terminate
  b[82] = '\0';
}
#endif // HAVE(FLT80) && HAVE(INT32)

// -----------------------------------------------------------------------------
// 128-bit binary representation
#if HAVE(FLT128) && HAVE(INT64)
static inline void flt_f128_bits (uchar* b, f128 f)
{
#if FP(LITTLE_ENDIAN)
  u64 u = *((u64*)&f + 1);
#else
  u64 u = *(u64*)&f;
#endif

#if FP(DIFFERENT_ENDIAN)
  u = bswap64 (u);
#endif

  // Sign bit
  b[0] = chr_bdig_from_int (bit_is_set (u, 63));
  b[1] = ' ';
  u <<= 1;

  // Exponent bits
  for (uint i = 2u; i < 17u; i++)
  {
    b[i] = chr_bdig_from_int (bit_is_set (u, 63));
    u <<= 1;
  }

  b[17] = ' ';

  // Mantissa bits
  for (uint i = 18u; i < 66u; i++)
  {
    b[i] = chr_bdig_from_int (bit_is_set (u, 63));
    u <<= 1;
  }

  // Next chunk
#if FP(LITTLE_ENDIAN)
  u = *(u64*)&f;
#else
  u = *((u64*)&f + 1);
#endif

#if FP(DIFFERENT_ENDIAN)
  u = bswap64 (u);
#endif

  for (uint i = 66u; i < 130u; i++)
  {
    b[i] = chr_bdig_from_int (bit_is_set (u, 63));
    u <<= 1;
  }

  // Null-terminate
  b[130] = '\0';
}
#endif // HAVE(FLT128) && HAVE(INT64)

// -----------------------------------------------------------------------------
// Aliases for the fundamental floating point types
// -----------------------------------------------------------------------------

#ifdef FLT_BINARY
  #define flt_sngl_bits flt_f##FLT_BINARY##_bits
#endif

#ifdef DBL_BINARY
  #define flt_dbl_bits flt_f##DBL_BINARY##_bits
#endif

#ifdef LDBL_BINARY
  #define flt_ldbl_bits flt_f##LDBL_BINARY##_bits
#endif

// -----------------------------------------------------------------------------

#endif // FP_IEEE754

// -----------------------------------------------------------------------------

#endif
