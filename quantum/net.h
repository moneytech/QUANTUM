// =============================================================================
// <net.h>
//
// Common network constants, types, macros,
// and host <-> network byte order conversion functions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A09BCAC43E4E422890B7D095331A1712
#define H_A09BCAC43E4E422890B7D095331A1712

// -----------------------------------------------------------------------------

#include "bswap.h"

// =============================================================================
// Constants
// -----------------------------------------------------------------------------
// All addresses in context of a server
#define NET_ALL "0.0.0.0"
#define NET_ALL6 "::"

// -----------------------------------------------------------------------------
// Non-routable "null" address in context of a client
#define NET_NULL NET_ALL
#define NET_NULL6 NET_ALL6

// -----------------------------------------------------------------------------
// Address of the local machine
#define NET_LOCALHOST "127.0.0.1"
#define NET_LOCALHOST6 "::1"

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// Network byte order conversion macros
// -----------------------------------------------------------------------------

#if CPU(LITTLE_ENDIAN)

  #if HAVE(INT16)
    #define net_bswap16 bswap16
  #endif

  #if HAVE(INT32)
    #define net_bswap32 bswap32
  #endif

  #if HAVE(INT64)
    #define net_bswap64 bswap64
  #endif

  #define net_buf_bswap(buf, size) buf_bswap ((buf), (size))

#else // CPU(LITTLE_ENDIAN) ][

  #if HAVE(INT16)
    #define net_bswap16 nop
  #endif

  #if HAVE(INT32)
    #define net_bswap32 nop
  #endif

  #if HAVE(INT64)
    #define net_bswap64 nop
  #endif

  #define net_buf_bswap(buf, size)

#endif // !CPU(LITTLE_ENDIAN)

// -----------------------------------------------------------------------------

#if HAVE(INT16)
  #define hton16 net_bswap16
  #define ntoh16 net_bswap16
#endif

#if HAVE(INT32)
  #define hton32 net_bswap32
  #define ntoh32 net_bswap32
#endif

#if HAVE(INT64)
  #define hton64 net_bswap64
  #define ntoh64 net_bswap64
#endif

// =============================================================================
// Types
// -----------------------------------------------------------------------------

typedef struct in_addr net_addr_t;
typedef struct in6_addr net_addr6_t;

typedef struct sockaddr_in net_saddr_t;
typedef struct sockaddr_in6 net_saddr6_t;
typedef struct sockaddr_storage net_saddr_store_t;

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// `long long` byte order conversion functions
// -----------------------------------------------------------------------------

#if !OS(WIN32)

static inline u64 htonll (u64 i)
{
#if CPU(LITTLE_ENDIAN)
  return (((u64)htonl (i)) << 32) | htonl (i >> 32);
#else
  return i;
#endif
}

#define ntohll htonll

#endif // !OS(WIN32)

// -----------------------------------------------------------------------------
// Helper functions to parse structures from buffers in network byte order
// -----------------------------------------------------------------------------
// Single byte functions following the same API pattern (for completeness sake)
// -----------------------------------------------------------------------------

static inline u8* net_hton8 (u8* restrict n, const u8* restrict h)
{
  *n = *h;
  return n + 1;
}

static inline u8* net_ntoh8 (u8* restrict h, const u8* restrict n)
{
  *h = *n;
  return (u8*)(n + 1);
}

// -----------------------------------------------------------------------------
// Two bytes
// -----------------------------------------------------------------------------

#if CPU(UNALIGNED_ACCESS) && HAVE(INT16)
  #define net_copy2(d, s)\
    *(u16*)(d) = net_bswap16 (*(const u16*)(s))
#else
  #if CPU(LITTLE_ENDIAN)
    #define NET_B0 1
    #define NET_B1 0
  #else
    #define NET_B0 0
    #define NET_B1 1
  #endif

  #define net_copy2(d, s)\
    (d)[0] = (s)[NET_B0];\
    (d)[1] = (s)[NET_B1]
#endif

static inline u8* net_hton16 (u8* restrict n, const u8* restrict h)
{
  net_copy2 (n, h);
  return n + 2;
}

static inline u8* net_ntoh16 (u8* restrict h, const u8* restrict n)
{
  net_copy2 (h, n);
  return (u8*)(n + 2);
}

#undef net_copy2

#undef NET_B0
#undef NET_B1

// -----------------------------------------------------------------------------
// Three bytes
// -----------------------------------------------------------------------------

#if CPU(UNALIGNED_ACCESS) && HAVE(INT16)
  #if CPU(LITTLE_ENDIAN)
    #define NET_B0 1
    #define NET_B2 0
  #else
    #define NET_B0 0
    #define NET_B2 2
  #endif

  #define net_copy3(d, s)\
    *(u16*)((d) + 0) = net_bswap16 (*(const u16*)((s) + NET_B0));\
    (d)[2] = (s)[NET_B2]
#else
  #if CPU(LITTLE_ENDIAN)
    #define NET_B0 2
    #define NET_B1 1
    #define NET_B2 0
  #else
    #define NET_B0 0
    #define NET_B1 1
    #define NET_B2 2
  #endif

  #define net_copy3(d, s)\
    (d)[0] = (s)[NET_B0];\
    (d)[1] = (s)[NET_B1];\
    (d)[2] = (s)[NET_B2]
#endif

static inline u8* net_hton24 (u8* restrict n, const u8* restrict h)
{
  net_copy3 (n, h);
  return n + 3;
}

static inline u8* net_ntoh24 (u8* restrict h, const u8* restrict n)
{
  net_copy3 (h, n);
  return (u8*)(n + 3);
}

#undef net_copy3

#undef NET_B0
#undef NET_B1
#undef NET_B2

// -----------------------------------------------------------------------------
// Four bytes
// -----------------------------------------------------------------------------

#if CPU(UNALIGNED_ACCESS) && HAVE(INT32)
  #define net_copy4(d, s)\
    *(u32*)(d) = net_bswap32 (*(const u32*)(s))
#else
  #if CPU(LITTLE_ENDIAN)
    #define NET_B0 3
    #define NET_B1 2
    #define NET_B2 1
    #define NET_B3 0
  #else
    #define NET_B0 0
    #define NET_B1 1
    #define NET_B2 2
    #define NET_B3 3
  #endif

  #define net_copy4(d, s)\
    (d)[0] = (s)[NET_B0];\
    (d)[1] = (s)[NET_B1];\
    (d)[2] = (s)[NET_B2];\
    (d)[3] = (s)[NET_B3]
#endif

static inline u8* net_hton32 (u8* restrict n, const u8* restrict h)
{
  net_copy4 (n, h);
  return n + 4;
}

static inline u8* net_ntoh32 (u8* restrict h, const u8* restrict n)
{
  net_copy4 (h, n);
  return (u8*)(n + 4);
}

#undef net_copy4

#undef NET_B0
#undef NET_B1
#undef NET_B2
#undef NET_B3

// -----------------------------------------------------------------------------
// Five bytes
// -----------------------------------------------------------------------------

#if CPU(UNALIGNED_ACCESS) && HAVE(INT32)
  #if CPU(LITTLE_ENDIAN)
    #define NET_B0 1
    #define NET_B4 0
  #else
    #define NET_B0 0
    #define NET_B4 4
  #endif

  #define net_copy5(d, s)\
    *(u32*)((d) + 0) = net_bswap32 (*(const u32*)((s) + NET_B0));\
    (d)[4] = (s)[NET_B4]
#else
  #if CPU(LITTLE_ENDIAN)
    #define NET_B0 4
    #define NET_B1 3
    #define NET_B2 2
    #define NET_B3 1
    #define NET_B4 0
  #else
    #define NET_B0 0
    #define NET_B1 1
    #define NET_B2 2
    #define NET_B3 3
    #define NET_B4 4
  #endif

  #define net_copy5(d, s)\
    (d)[0] = (s)[NET_B0];\
    (d)[1] = (s)[NET_B1];\
    (d)[2] = (s)[NET_B2];\
    (d)[3] = (s)[NET_B3];\
    (d)[4] = (s)[NET_B4]
#endif

static inline u8* net_hton40 (u8* restrict n, const u8* restrict h)
{
  net_copy5 (n, h);
  return n + 5;
}

static inline u8* net_ntoh40 (u8* restrict h, const u8* restrict n)
{
  net_copy5 (h, n);
  return (u8*)(n + 5);
}

#undef net_copy5

#undef NET_B0
#undef NET_B1
#undef NET_B2
#undef NET_B3
#undef NET_B4

// -----------------------------------------------------------------------------
// Six bytes
// -----------------------------------------------------------------------------

#if CPU(UNALIGNED_ACCESS) && HAVE(INT32) && HAVE(INT16)
  #if CPU(LITTLE_ENDIAN)
    #define NET_B0 2
    #define NET_B4 0
  #else
    #define NET_B0 0
    #define NET_B4 4
  #endif

  #define net_copy6(d, s)\
    *(u32*)((d) + 0) = net_bswap32 (*(const u32*)((s) + NET_B0));\
    *(u16*)((d) + 4) = net_bswap16 (*(const u16*)((s) + NET_B4))
#else
  #if CPU(LITTLE_ENDIAN)
    #define NET_B0 5
    #define NET_B1 4
    #define NET_B2 3
    #define NET_B3 2
    #define NET_B4 1
    #define NET_B5 0
  #else
    #define NET_B0 0
    #define NET_B1 1
    #define NET_B2 2
    #define NET_B3 3
    #define NET_B4 4
    #define NET_B5 5
  #endif

  #define net_copy6(d, s)\
    (d)[0] = (s)[NET_B0];\
    (d)[1] = (s)[NET_B1];\
    (d)[2] = (s)[NET_B2];\
    (d)[3] = (s)[NET_B3];\
    (d)[4] = (s)[NET_B4];\
    (d)[5] = (s)[NET_B5]
#endif

static inline u8* net_hton48 (u8* restrict n, const u8* restrict h)
{
  net_copy6 (n, h);
  return n + 6;
}

static inline u8* net_ntoh48 (u8* restrict h, const u8* restrict n)
{
  net_copy6 (h, n);
  return (u8*)(n + 6);
}

#undef net_copy6

#undef NET_B0
#undef NET_B1
#undef NET_B2
#undef NET_B3
#undef NET_B4
#undef NET_B5

// -----------------------------------------------------------------------------
// Seven bytes
// -----------------------------------------------------------------------------

#if CPU(UNALIGNED_ACCESS) && HAVE(INT32) && HAVE(INT16)
  #if CPU(LITTLE_ENDIAN)
    #define NET_B0 3
    #define NET_B4 1
    #define NET_B6 0
  #else
    #define NET_B0 0
    #define NET_B4 4
    #define NET_B6 6
  #endif

  #define net_copy7(d, s)\
    *(u32*)((d) + 0) = net_bswap32 (*(const u32*)((s) + NET_B0));\
    *(u16*)((d) + 4) = net_bswap16 (*(const u16*)((s) + NET_B4));\
    (d)[6] = (s)[NET_B6]
#else
  #if CPU(LITTLE_ENDIAN)
    #define NET_B0 6
    #define NET_B1 5
    #define NET_B2 4
    #define NET_B3 3
    #define NET_B4 2
    #define NET_B5 1
    #define NET_B6 0
  #else
    #define NET_B0 0
    #define NET_B1 1
    #define NET_B2 2
    #define NET_B3 3
    #define NET_B4 4
    #define NET_B5 5
    #define NET_B6 6
  #endif

  #define net_copy7(d, s)\
    (d)[0] = (s)[NET_B0];\
    (d)[1] = (s)[NET_B1];\
    (d)[2] = (s)[NET_B2];\
    (d)[3] = (s)[NET_B3];\
    (d)[4] = (s)[NET_B4];\
    (d)[5] = (s)[NET_B5];\
    (d)[6] = (s)[NET_B6]
#endif

static inline u8* net_hton56 (u8* restrict n, const u8* restrict h)
{
  net_copy7 (n, h);
  return n + 7;
}

static inline u8* net_ntoh56 (u8* restrict h, const u8* restrict n)
{
  net_copy7 (h, n);
  return (u8*)(n + 7);
}

#undef net_copy7

#undef NET_B0
#undef NET_B1
#undef NET_B2
#undef NET_B3
#undef NET_B4
#undef NET_B5
#undef NET_B6

// -----------------------------------------------------------------------------
// Eight bytes
// -----------------------------------------------------------------------------

#if CPU(UNALIGNED_ACCESS) && HAVE(INT64)
  #define net_copy8(d, s)\
    *(u64*)(d) = net_bswap64 (*(const u64*)(s))
#else
  #if CPU(LITTLE_ENDIAN)
    #define NET_B0 7
    #define NET_B1 6
    #define NET_B2 5
    #define NET_B3 4
    #define NET_B4 3
    #define NET_B5 2
    #define NET_B6 1
    #define NET_B7 0
  #else
    #define NET_B0 0
    #define NET_B1 1
    #define NET_B2 2
    #define NET_B3 3
    #define NET_B4 4
    #define NET_B5 5
    #define NET_B6 6
    #define NET_B7 7
  #endif

  #define net_copy8(d, s)\
    (d)[0] = (s)[NET_B0];\
    (d)[1] = (s)[NET_B1];\
    (d)[2] = (s)[NET_B2];\
    (d)[3] = (s)[NET_B3];\
    (d)[4] = (s)[NET_B4];\
    (d)[5] = (s)[NET_B5];\
    (d)[6] = (s)[NET_B6];\
    (d)[7] = (s)[NET_B7]
#endif

static inline u8* net_hton64 (u8* restrict n, const u8* restrict h)
{
  net_copy8 (n, h);
  return n + 8;
}

static inline u8* net_ntoh64 (u8* restrict h, const u8* restrict n)
{
  net_copy8 (h, n);
  return (u8*)(n + 8);
}

#undef net_copy8

#undef NET_B0
#undef NET_B1
#undef NET_B2
#undef NET_B3
#undef NET_B4
#undef NET_B5
#undef NET_B6
#undef NET_B7

// -----------------------------------------------------------------------------
// Arbitrary number of bytes
// -----------------------------------------------------------------------------

static inline u8* net_buf_hton (u8* restrict dst, const u8* restrict src, size_t size)
{
#if CPU(LITTLE_ENDIAN)
  #include "string/buffer/reverse_copy/generic.c"
#else
  buf_copy (dst, src, size);
#endif

  return dst + size;
}

// -----------------------------------------------------------------------------

static inline u8* net_buf_ntoh (u8* restrict dst, const u8* restrict src, size_t size)
{
#if CPU(LITTLE_ENDIAN)
  #include "string/buffer/reverse_copy/generic.c"
#else
  buf_copy (dst, src, size);
#endif

  return (u8*)(src + size);
}

// -----------------------------------------------------------------------------
// Write a value of width `x` to a network buffer
// -----------------------------------------------------------------------------
// One byte
#if HAVE(INT8)
static inline u8* net_put8 (u8* n, u8 h)
{
  return net_hton8 (n, &h);
}
#endif

// -----------------------------------------------------------------------------
// Two bytes
#if HAVE(INT16)
static inline u8* net_put16 (u8* n, u16 h)
{
  return net_hton8 (n, (const u8*)&h);
}
#endif

// -----------------------------------------------------------------------------
// Three bytes
#if HAVE(INT32)
static inline u8* net_put24 (u8* n, u32 h)
{
#if CPU(LITTLE_ENDIAN)
  return net_hton24 (n, (const u8*)&h);
#else
  return net_hton24 (n, (const u8*)&h + 1);
#endif
}
#endif // HAVE(INT32)

// -----------------------------------------------------------------------------
// Four bytes
#if HAVE(INT32)
static inline u8* net_put32 (u8* n, u32 h)
{
  return net_hton32 (n, (const u8*)&h);
}
#endif

// -----------------------------------------------------------------------------
// Five bytes
#if HAVE(INT64)
static inline u8* net_put40 (u8* n, const u64 h)
{
#if CPU(LITTLE_ENDIAN)
  return net_hton40 (n, (const u8*)&h);
#else
  return net_hton40 (n, (const u8*)&h + 3);
#endif
}
#endif // HAVE(INT64)

// -----------------------------------------------------------------------------
// Six bytes
#if HAVE(INT64)
static inline u8* net_put48 (u8* n, const u64 h)
{
#if CPU(LITTLE_ENDIAN)
  return net_hton48 (n, (const u8*)&h);
#else
  return net_hton48 (n, (const u8*)&h + 2);
#endif
}
#endif // HAVE(INT64)

// -----------------------------------------------------------------------------
// Seven bytes
#if HAVE(INT64)
static inline u8* net_put56 (u8* n, const u64 h)
{
#if CPU(LITTLE_ENDIAN)
  return net_hton56 (n, (const u8*)&h);
#else
  return net_hton56 (n, (const u8*)&h + 1);
#endif
}
#endif // HAVE(INT64)

// -----------------------------------------------------------------------------
// Eight bytes
#if HAVE(INT64)
static inline u8* net_put64 (u8* n, const u64 h)
{
  return net_hton64 (n, (const u8*)&h);
}
#endif

// -----------------------------------------------------------------------------
// Read a value of width `x` from a network buffer
// -----------------------------------------------------------------------------
// One byte
#if HAVE(INT8)
static inline u8 net_get8 (const u8** n)
{
  u8 v;

  *n = net_ntoh8 (&v, *n);

  return v;
}
#endif

// -----------------------------------------------------------------------------
// Two bytes
#if HAVE(INT16)
static inline u16 net_get16 (const u8** n)
{
  u16 v;

  *n = net_ntoh16 ((u8*)&v, *n);

  return v;
}
#endif

// -----------------------------------------------------------------------------
// Three bytes
#if HAVE(INT32)
static inline u32 net_get24 (const u8** n)
{
  u32 v = 0;

#if CPU(LITTLE_ENDIAN)
  *n = net_ntoh24 ((u8*)&v, *n);
#else
  *n = net_ntoh24 ((u8*)&v + 1, *n);
#endif

  return v;
}
#endif // HAVE(INT32)

// -----------------------------------------------------------------------------
// Four bytes
#if HAVE(INT32)
static inline u32 net_get32 (const u8** n)
{
  u32 v;

  *n = net_ntoh32 ((u8*)&v, *n);

  return v;
}
#endif

// -----------------------------------------------------------------------------
// Five bytes
#if HAVE(INT64)
static inline u64 net_get40 (const u8** n)
{
  u64 v = 0;

#if CPU(LITTLE_ENDIAN)
  *n = net_ntoh40 ((u8*)&v, *n);
#else
  *n = net_ntoh40 ((u8*)&v + 3, *n);
#endif

  return v;
}
#endif // HAVE(INT64)

// -----------------------------------------------------------------------------
// six bytes
#if HAVE(INT64)
static inline u64 net_get48 (const u8** n)
{
  u64 v = 0;

#if CPU(LITTLE_ENDIAN)
  *n = net_ntoh48 ((u8*)&v, *n);
#else
  *n = net_ntoh48 ((u8*)&v + 2, *n);
#endif

  return v;
}
#endif // HAVE(INT64)

// -----------------------------------------------------------------------------
// Seven bytes
#if HAVE(INT64)
static inline u64 net_get56 (const u8** n)
{
  u64 v = 0;

#if CPU(LITTLE_ENDIAN)
  *n = net_ntoh56 ((u8*)&v, *n);
#else
  *n = net_ntoh56 ((u8*)&v + 1, *n);
#endif

  return v;
}
#endif // HAVE(INT64)

// -----------------------------------------------------------------------------
// Eight bytes
#if HAVE(INT64)
static inline u64 net_get64 (const u8** n)
{
  u64 v;

  *n = net_ntoh64 ((u8*)&v, *n);

  return v;
}
#endif

// -----------------------------------------------------------------------------

#endif
