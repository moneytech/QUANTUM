// =============================================================================
// <flint.h>
//
// Floating point integers ("flints") characteristics.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_B663A33B1D2C460B8D6A0259A5876AC4
#define H_B663A33B1D2C460B8D6A0259A5876AC4

// -----------------------------------------------------------------------------

#if (FLT_RADIX == 2)

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// Advance 8 significand bits
#define flint_fold(t, p)\
if ((p + 1) < n) f *= (t)2;\
if ((p + 2) < n) f *= (t)2;\
if ((p + 3) < n) f *= (t)2;\
if ((p + 4) < n) f *= (t)2;\
if ((p + 5) < n) f *= (t)2;\
if ((p + 6) < n) f *= (t)2;\
if ((p + 7) < n) f *= (t)2;\
if ((p + 8) < n) f *= (t)2

// -----------------------------------------------------------------------------
// For floating point types with up to 256 significand bits
#define flint_find(t)\
flint_fold (t, 0);  \
flint_fold (t, 8);  \
flint_fold (t, 16); \
flint_fold (t, 24); \
flint_fold (t, 32); \
flint_fold (t, 40); \
flint_fold (t, 48); \
flint_fold (t, 56); \
flint_fold (t, 64); \
flint_fold (t, 72); \
flint_fold (t, 80); \
flint_fold (t, 88); \
flint_fold (t, 96); \
flint_fold (t, 104);\
flint_fold (t, 112);\
flint_fold (t, 120);\
flint_fold (t, 128);\
flint_fold (t, 136);\
flint_fold (t, 144);\
flint_fold (t, 152);\
flint_fold (t, 160);\
flint_fold (t, 168);\
flint_fold (t, 176);\
flint_fold (t, 184);\
flint_fold (t, 192);\
flint_fold (t, 200);\
flint_fold (t, 208);\
flint_fold (t, 216);\
flint_fold (t, 224);\
flint_fold (t, 232);\
flint_fold (t, 240);\
flint_fold (t, 248)

// -----------------------------------------------------------------------------
// Using the macros above: find out the maximum flint value
// for a particular floating point type. This value is
// guaranteed to be computed losslessly
#define flint_max(t, d) do\
{                       \
  const uint n = d;     \
                        \
  t f = (t)1;           \
  flint_find (t);       \
                        \
  return f + (f - (t)1);\
} while (0)

// -----------------------------------------------------------------------------
// Given the maximum flint value of a particular floating point type
// found out using the macro above: find out the number of decimal digits
// it takes to represent it
#define flint_dig(t, m) do\
{                 \
  uint n = 0;     \
  t f = m;        \
                  \
  while (f > (t)1)\
  {            \
    f /= (t)10;\
    n++;   \
  }        \
           \
  return n;\
} while (0)

// -----------------------------------------------------------------------------
// Simple arithmetic formula to find out the maximum power of ten
// a particular floating type can represent losslessly
#define flint_pow(d) (((((d) - 1) / 7) * 3) + ((((d) - 1) % 7) / 2))

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// `float` flint characteristics
// -----------------------------------------------------------------------------

static forceinline const float flint_sngl_max()
{
#if (FLT_BINARY == 32)
  return 16777215.0f;
#else
  flint_max (float, FLT_MANT_DIG);
#endif
}

static forceinline const uint flint_sngl_dig_max()
{
#if (FLT_BINARY == 32)
  return 8;
#else
  flint_dig (float, flint_sngl_max());
#endif
}

static forceinline const uint flint_sngl_pow_max()
{
#if (FLT_BINARY == 32)
  return 10;
#else
  return flint_pow (FLT_MANT_DIG);
#endif
}

// -----------------------------------------------------------------------------

#if (FLT_BINARY == 32)
  #define flint_f32_max flint_sngl_max
  #define flint_f32_dig_max flint_sngl_dig_max
  #define flint_f32_pow_max flint_sngl_pow_max
#endif

// -----------------------------------------------------------------------------
// `double` flint characteristics
// -----------------------------------------------------------------------------

static forceinline const double flint_dbl_max()
{
#if (DBL_BINARY == 64)
  return 9007199254740991.0;
#elif (DBL_BINARY == 32)
  return 16777215.0;
#else
  flint_max (double, DBL_MANT_DIG);
#endif
}

static forceinline const uint flint_dbl_dig_max()
{
#if (DBL_BINARY == 64)
  return 16;
#elif (DBL_BINARY == 32)
  return 8;
#else
  flint_dig (double, flint_dbl_max());
#endif
}

static forceinline const uint flint_dbl_pow_max()
{
#if (DBL_BINARY == 64)
  return 22;
#elif (DBL_BINARY == 32)
  return 10;
#else
  return flint_pow (DBL_MANT_DIG);
#endif
}

// -----------------------------------------------------------------------------

#if (DBL_BINARY == 32) && (DBL_BINARY != FLT_BINARY)
  #define flint_f32_max flint_dbl_max
  #define flint_f32_dig_max flint_dbl_dig_max
  #define flint_f32_pow_max flint_dbl_pow_max
#elif (DBL_BINARY == 64)
  #define flint_f64_max flint_dbl_max
  #define flint_f64_dig_max flint_dbl_dig_max
  #define flint_f64_pow_max flint_dbl_pow_max
#endif

// -----------------------------------------------------------------------------
// `long double` flint characteristics
// -----------------------------------------------------------------------------

static forceinline const long double flint_ldbl_max()
{
#if (LDBL_BINARY == 64)
  return 9007199254740991.0l;
#elif (LDBL_BINARY == 32)
  return 16777215.0l;
#else
  flint_max (long double, LDBL_MANT_DIG);
#endif
}

static forceinline const uint flint_ldbl_dig_max()
{
#if (LDBL_BINARY == 64)
  return 16;
#elif (LDBL_BINARY == 32)
  return 8;
#else
  flint_dig (long double, flint_ldbl_max());
#endif
}

static forceinline const uint flint_ldbl_pow_max()
{
#if (LDBL_BINARY == 64)
  return 22;
#elif (LDBL_BINARY == 32)
  return 10;
#else
  return flint_pow (LDBL_MANT_DIG);
#endif
}

// -----------------------------------------------------------------------------

#if (LDBL_BINARY == 32) && (LDBL_BINARY != DBL_BINARY) && (LDBL_BINARY != FLT_BINARY)
  #define flint_f32_max flint_ldbl_max
  #define flint_f32_dig_max flint_ldbl_dig_max
  #define flint_f32_pow_max flint_ldbl_pow_max
#elif (LDBL_BINARY == 64) && (LDBL_BINARY != DBL_BINARY)
  #define flint_f64_max flint_ldbl_max
  #define flint_f64_dig_max flint_ldbl_dig_max
  #define flint_f64_pow_max flint_ldbl_pow_max
#endif

// -----------------------------------------------------------------------------
// Extended precision flint characteristics
// -----------------------------------------------------------------------------

#if HAVE(FLT80)
static forceinline const f80 flint_f80_max()
{
  flint_max (f80, 64);
}

static forceinline const uint flint_f80_dig_max()
{
  flint_dig (f80, flint_f80_max());
}

static forceinline const uint flint_f80_pow_max()
{
  return flint_pow (64);
}
#endif

// -----------------------------------------------------------------------------
// Quadruple-precision flint characteristics
// -----------------------------------------------------------------------------

#if HAVE(FLT128)
static forceinline const f128 flint_f128_max()
{
  flint_max (f128, FLT128_MANT_DIG);
}

static forceinline const uint flint_f128_dig_max()
{
  flint_dig (f128, flint_f128_max());
}

static forceinline const uint flint_f128_pow_max()
{
  return flint_pow (FLT128_MANT_DIG);
}
#endif

// -----------------------------------------------------------------------------
// Cleanup
// -----------------------------------------------------------------------------

#undef flint_fold
#undef flint_find
#undef flint_max
#undef flint_dig
#undef flint_pow

// -----------------------------------------------------------------------------

#endif // (FLT_RADIX == 2)

// -----------------------------------------------------------------------------

#endif
