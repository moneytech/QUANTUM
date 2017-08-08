// =============================================================================
// <size.h>
//
// Size type definitions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_C68656C92F3C4DDBA5A4E50EA4EB27AE
#define H_C68656C92F3C4DDBA5A4E50EA4EB27AE

// =============================================================================
// Constants
// -----------------------------------------------------------------------------
// Characteristics of the size type
// -----------------------------------------------------------------------------
// `size_t` is always unsigned
#define SIZE_BIT INT_BIT_MAX (SIZE_MAX)

#define SIZE_DIG INT_DIG_MAX (SIZE_BIT)
#define SIZE_XDIG INT_XDIG_MAX (SIZE_BIT)
#define SIZE_ODIG INT_ODIG_MAX (SIZE_BIT)

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// Size alignment (must be a power of two)
// -----------------------------------------------------------------------------
// Check if the specified size value is divided by the specified power of two
// without a remainder
#define size_aligned(align, size) (((size) & (size_t)((align) - 1u)) == 0)

// -----------------------------------------------------------------------------
// Align the specified size value downwards (closest previous value)
#define size_align_floor(align, size) ((size) & ~(size_t)((align) - 1u))

// -----------------------------------------------------------------------------
// Align the specified size value upwards (closest next value)
#define size_align_ceil(align, size) (((size) + (size_t)((align) - 1u)) & ~(size_t)((align) - 1u))

// -----------------------------------------------------------------------------

#endif
