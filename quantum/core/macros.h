// =============================================================================
// <core/macros.h>
//
// Core macro definitions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A337B70CDE1B4247B990A9BB462C959F
#define H_A337B70CDE1B4247B990A9BB462C959F

// -----------------------------------------------------------------------------
// Check if the particular third-party feature is available
#define HAVE(feat) (defined(HAVE_##feat))

// -----------------------------------------------------------------------------
// Check if the particular third-party feature is not available
#define NO(feat) (defined(NO_##feat))

// -----------------------------------------------------------------------------
// Check if the particular third-party feature must be used
// (implying that it is available)
#define USE(feat) (defined(USE_##feat))

// -----------------------------------------------------------------------------
// Check if the particular feature has been requested to be enabled
#define ENABLED(feat) (defined(ENABLE_##feat))

// -----------------------------------------------------------------------------
// Check if the particular feature has been requested to be disabled
#define DISABLED(feat) (defined(DISABLE_##feat))

// -----------------------------------------------------------------------------
// Check if the particular header file has already been included
#define H(uuid) (defined(H_##uuid))

// -----------------------------------------------------------------------------
// Check if the particular template parameter is set
#define T(feat) (defined(T_##feat))

// -----------------------------------------------------------------------------

#endif
