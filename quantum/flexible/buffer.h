// =============================================================================
// <flexible/buffer.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_F3A2B01609C14B9AAECBD580B26BD7BD
#define H_F3A2B01609C14B9AAECBD580B26BD7BD

// -----------------------------------------------------------------------------

#include "../object/buffer.h"
#include "../array/buffer.h"

// -----------------------------------------------------------------------------
// Copy the flexible object data into another memory block
#define flex_copy(dst, src, arr, num) mem_copy (dst, src, flex_size (dst, arr, num))

// -----------------------------------------------------------------------------
// Compare the two memory blocks occupied by the two flexible objects
#define flex_equal(obj1, obj2, arr, num) mem_equal (obj1, obj2, flex_size (obj1, arr, num))

// -----------------------------------------------------------------------------
// Zero out the memory block occupied by the flexible object
#define flex_zero(obj, arr, num) mem_zero (obj, flex_size (obj, arr, num))

// -----------------------------------------------------------------------------

#endif
