// =============================================================================
// <object/buffer.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_F87692407F054C89BCB63B7429194619
#define H_F87692407F054C89BCB63B7429194619

// -----------------------------------------------------------------------------

#include "../memory/buffer.h"

// -----------------------------------------------------------------------------
// Copy the object data into another memory block
#define obj_copy(dst, src) mem_copy (dst, src, obj_size (dst))

// -----------------------------------------------------------------------------
// Compare the two memory blocks occupied by the two objects
#define obj_equal(obj1, obj2) mem_equal (obj1, obj2, obj_size (obj1))

// -----------------------------------------------------------------------------
// Zero out the memory block occupied by the object
#define obj_zero(obj) mem_zero (obj, obj_size (obj))

// -----------------------------------------------------------------------------

#endif
