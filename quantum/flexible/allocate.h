// =============================================================================
// <flexible/allocate.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_CC8B9C252A0347B58C144CB49EC503D4
#define H_CC8B9C252A0347B58C144CB49EC503D4

// -----------------------------------------------------------------------------

#include "../object/allocate.h"
#include "../array/allocate.h"

// -----------------------------------------------------------------------------
// Allocate the memory block capable of holding the particular flexible object
#define flex_alloc(obj, arr, num) mem_alloc (flex_size (obj, arr, num))

// -----------------------------------------------------------------------------
// Allocate the zeroed out memory block for the particular flexible object
#define flex_alloc_zero(obj, arr, num) mem_alloc_zero (flex_size (obj, arr, num))

// -----------------------------------------------------------------------------
// Allocate the memory block with stricter alignment
// for the particular flexible object
#define flex_alloc_align(align, obj, arr, num) mem_alloc_align (align, flex_size (obj, arr, num))

// -----------------------------------------------------------------------------
// Reallocate the previously allocated flexible object memory block.
// Stricter alignment requested from the previous
// `flex_alloc_align()` call might be lost.
#define flex_realloc(obj, arr, num) mem_realloc (arr, flex_size (obj, arr, num))

// -----------------------------------------------------------------------------

#endif
