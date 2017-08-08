// =============================================================================
// <array/allocate.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_BAA221A55F8D4E06AB167E570EB7FF8E
#define H_BAA221A55F8D4E06AB167E570EB7FF8E

// -----------------------------------------------------------------------------

#include "../object/allocate.h"

// -----------------------------------------------------------------------------
// Allocate the memory block capable of holding the specified number of objects
#define arr_alloc(arr, num) mem_alloc (arr_size (arr, num))

// -----------------------------------------------------------------------------
// Allocate the zeroed out memory block for the array of objects
#define arr_alloc_zero(arr, num) mem_alloc_zero (arr_size (arr, num))

// -----------------------------------------------------------------------------
// Allocate the memory block with stricter alignment for the array of objects
#define arr_alloc_align(align, arr, num) mem_alloc_align (align, arr_size (arr, num))

// -----------------------------------------------------------------------------
// Reallocate the previously allocated array memory block.
// Stricter alignment requested from the previous
// `arr_alloc_align()` call might be lost.
#define arr_realloc(arr, num) mem_realloc (arr, arr_size (arr, num))

// -----------------------------------------------------------------------------

#endif
