// =============================================================================
// <memory/macros.h>
//
// Useful memory macros.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_EDAC1C991F9D45BC94E85A60D4A3148D
#define H_EDAC1C991F9D45BC94E85A60D4A3148D

// -----------------------------------------------------------------------------
// Specialized standard C memory functions
// -----------------------------------------------------------------------------
// Compare two memory blocks for equality
#define memequ(mem1, mem2, size) (memcmp ((mem1), (mem2), (size)) == 0)

// -----------------------------------------------------------------------------
// Zero out a memory block
#define memzero(mem, size) memset ((mem), 0, (size))

// -----------------------------------------------------------------------------
// Deprecated BSD memory function definitions
// -----------------------------------------------------------------------------

#ifndef bcopy
  #define bcopy(src, dst, size) memmove ((dst), (src), (size))
#endif

#ifndef bcmp
  #define bcmp memcmp
#endif

#ifndef bzero
  #define bzero memzero
#endif

// -----------------------------------------------------------------------------

#endif
