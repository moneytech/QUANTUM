// =============================================================================
// <stdlib/windows/time.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_F10206F0BA854CADA688B24D77548ECC
#define H_F10206F0BA854CADA688B24D77548ECC

// =============================================================================
// Macros
// -----------------------------------------------------------------------------

#define asctime_r(stm, buf) asctime_s (buf, 32u, stm)
#define wasctime _wasctime
#define wasctime_s _wasctime_s
#define wasctime_r(stm, buf) wasctime_s (buf, 32u, stm)

#define ctime_r(utm, buf) ctime_s (buf, 32u, utm)
#define wctime _wctime
#define wctime_s _wctime_s
#define wctime_r(utm, buf) wctime_s (buf, 32u, utm)

#define gmtime_r(utm, stm) gmtime_s (stm, utm)
#define localtime_r(utm, stm) localtime_s (stm, utm)

#define tzset _tzset

// -----------------------------------------------------------------------------

#endif
