// =============================================================================
// <character/macros.h>
//
// Utility character definitions shared by units.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_C4B42507DA98415F98E14E15AE08A944
#define H_C4B42507DA98415F98E14E15AE08A944

// -----------------------------------------------------------------------------
// Transformation
// -----------------------------------------------------------------------------
// Toggle ASCII character case (corrupts non-alphabetic characters)
#define chr_to_lcase_fast(c) ((c) | 0x20u)
#define chr_to_ucase_fast(c) ((c) & ~0x20u)

// -----------------------------------------------------------------------------
// Conversion
// -----------------------------------------------------------------------------
// Convert an ASCII digit character to its numeric value
// and the other way around
#define chr_to_int(c) ((c) - (uint)'0')
#define chr_from_int(i) ((i) + (uint)'0')

// -----------------------------------------------------------------------------

#endif
