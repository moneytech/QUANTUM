// =============================================================================
// <array/buffer.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_D9120C783F1A44E2860599B6A8063119
#define H_D9120C783F1A44E2860599B6A8063119

// -----------------------------------------------------------------------------

#include "../object/buffer.h"

// -----------------------------------------------------------------------------
// Copy the array of objects (destination and source cannot overlap)
#define arr_copy(dst, src, num) mem_copy (dst, src, arr_size (dst, num))

// -----------------------------------------------------------------------------
// Move the array of objects (destination and source can overlap)
#define arr_move(dst, src, num) mem_move (dst, src, arr_size (dst, num))

// -----------------------------------------------------------------------------
// Compare the two memory blocks occupied by the two arrays of objects
#define arr_equal(arr1, arr2, num) mem_equal (arr1, arr2, arr_size (arr1, num))

// -----------------------------------------------------------------------------
// Zero out the memory block occupied by the array of objects
#define arr_zero(arr, num) mem_zero (arr, arr_size (arr, num))

// -----------------------------------------------------------------------------

#endif
