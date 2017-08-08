// =============================================================================
// <array/implicit.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A9919B0A61924F759DCB78399AB70B5C
#define H_A9919B0A61924F759DCB78399AB70B5C

// -----------------------------------------------------------------------------
// Find out the length of the null-terminated array
static inline size_t arri_length (const void* const* arr)
{
  size_t len = 0;

  while (arr[len] != null) len++;

  return len;
}

// -----------------------------------------------------------------------------

#endif
