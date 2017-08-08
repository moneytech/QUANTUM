// =============================================================================
// <hash.h>
//
// General-purpose hash functions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_422115E1778543EA8B14B96255DFFC98
#define H_422115E1778543EA8B14B96255DFFC98

// =============================================================================
// Macros
// -----------------------------------------------------------------------------

#define hash_fold(hash, bits) (((hash) ^ ((hash) >> (((sizeof (hash)) * CHAR_BIT) - (bits)))) << (bits))

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// DJB2 (by Daniel J. Bernstein)
// -----------------------------------------------------------------------------

static const uf32 hash_djb2_init = 5381u;

static inline uf32 hash_djb2_step (uf32 hash, char_t chr)
{
  return ((hash << 5) + hash) ^ chr;
}

static inline uf32 hash_djb2 (const char_t* str, size_t len)
{
  register uf32 hash = hash_djb2_init;

  const char_t* end = str + len;

  while (str != end) hash = hash_djb2_step (hash, *str++);

  return hash;
}

// -----------------------------------------------------------------------------
// SDBM (was created for sdbm database library)
// -----------------------------------------------------------------------------

static const uf32 hash_sdbm_init = 0;

static inline uf32 hash_sdbm_step (uf32 hash, char_t chr)
{
  return (hash << 6) + (hash << 16) - hash + chr;
}

static inline uf32 hash_sdbm (const char_t* str, size_t len)
{
  register uf32 hash = hash_sdbm_init;

  const char_t* end = str + len;

  while (str != end) hash = hash_sdbm_step (hash, *str++);

  return hash;
}

// -----------------------------------------------------------------------------
// FNV1A
// -----------------------------------------------------------------------------

static const uf32 hash_fnv1a_prime = 16777619u;
static const uf32 hash_fnv1a_init = 2166136261u;

static inline uf32 hash_fnv1a_step (uf32 hash, char_t chr)
{
  return (hash ^ chr) * hash_fnv1a_prime;
}

static inline uf32 hash_fnv1a (const char_t* str, size_t len)
{
  const char_t* s = str;

  const char_t* e = str + len;
  const char_t* b = str + size_align_floor (8u, len);

  const uf32 prime = hash_fnv1a_prime;
  uf32 hash = hash_fnv1a_init;

  while (s != b)
  {
#if CPU(UNALIGNED_ACCESS)
    hash = (hash ^ *(u32*)(s + 0)) * prime;
    hash = (hash ^ *(u32*)(s + 4)) * prime;
#else
    hash = (hash ^ s[0]) * prime;
    hash = (hash ^ s[1]) * prime;
    hash = (hash ^ s[2]) * prime;
    hash = (hash ^ s[3]) * prime;
    hash = (hash ^ s[4]) * prime;
    hash = (hash ^ s[5]) * prime;
    hash = (hash ^ s[6]) * prime;
    hash = (hash ^ s[7]) * prime;
#endif

    s += 8;
  }

  while (s != e) hash = (hash ^ *s++) * prime;

  return hash;
}

static inline uf32 hash_fnv1a_fast (const char_t* str, size_t len)
{
#if CPU(UNALIGNED_ACCESS) && HAVE(INT32)
  const char_t* s = str;

  const char_t* e = str + len;
  const char_t* b = str + size_align_floor (8u, len);

  const u32 prime = hash_fnv1a_prime;
  u32 hash = hash_fnv1a_init;

  while (s != b)
  {
    hash = (hash ^ *(const u32*)(s + 0)) * prime;
    hash = (hash ^ *(const u32*)(s + 4)) * prime;

    s += 8;
  }

  while (s != e) hash = (hash ^ *s++) * prime;

  return hash;
#else
  return hash_fnv1a (str, len);
#endif
}

// -----------------------------------------------------------------------------

#endif
