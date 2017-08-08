// =============================================================================
// <object/allocate.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_F15BAF2EFF5F45A6A7FA97DCA496944A
#define H_F15BAF2EFF5F45A6A7FA97DCA496944A

// -----------------------------------------------------------------------------

#include "../memory/allocate.h"

// -----------------------------------------------------------------------------
// Allocate the memory block capable of holding the particular object
#define obj_alloc(obj) mem_alloc (obj_size (obj))

// -----------------------------------------------------------------------------
// Allocate the zeroed out memory block for the particular object
#define obj_alloc_zero(obj) mem_alloc_zero (obj_size (obj))

// -----------------------------------------------------------------------------
// Allocate the memory block with stricter alignment for the particular object
#define obj_alloc_align(align, obj) mem_alloc_align (align, obj_size (obj))

// -----------------------------------------------------------------------------

#endif
