// =============================================================================
// <pointer.h>
//
// Pointer type definitions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_E256D63B71394226B31EB99B35DC48C4
#define H_E256D63B71394226B31EB99B35DC48C4

// =============================================================================
// Constants
// -----------------------------------------------------------------------------
// Characteristics of the pointer difference type
// -----------------------------------------------------------------------------
// `ptrdiff_t` is always signed
#define PTRDIFF_BIT (INT_BIT_MAX (PTRDIFF_MAX) + 1)

#define PTRDIFF_DIG INT_DIG_MAX (PTRDIFF_BIT)
#define PTRDIFF_XDIG INT_XDIG_MAX (PTRDIFF_BIT)
#define PTRDIFF_ODIG INT_ODIG_MAX (PTRDIFF_BIT)

// =============================================================================
// Types
// -----------------------------------------------------------------------------
// Abstract pointer type
typedef void* void_t;
typedef void* ptr_t;

// -----------------------------------------------------------------------------
// Alias of `ptrdiff_t`
typedef ptrdiff_t ptr_diff_t;

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// Pointer alignment (must be a power of two). The alignment is specified in
// the first parameter, as in the standard `aligned_alloc()` function.
// -----------------------------------------------------------------------------
// Check if the pointer satisfies the particular alignment requirement
#define ptr_aligned(align, ptr) (((uintptr_t)(ptr) & (uintptr_t)((align) - 1u)) == 0)

// -----------------------------------------------------------------------------
// Align the pointer downwards (previous address that would provide the alignment)
#define ptr_align_floor(align, ptr) (void*)((uintptr_t)(ptr) & ~(uintptr_t)((align) - 1u))

// -----------------------------------------------------------------------------
// Align the pointer upwards (next address that would provide the alignment)
#define ptr_align_ceil(align, ptr) (void*)(((uintptr_t)(ptr) + (uintptr_t)((align) - 1u)) & ~(uintptr_t)((align) - 1u))

// -----------------------------------------------------------------------------

#endif
