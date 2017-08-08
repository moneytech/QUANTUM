// =============================================================================
// <stdlib/windows/string.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_C64A171D64734CC388EC9D9937EA9CAA
#define H_C64A171D64734CC388EC9D9937EA9CAA

// =============================================================================
// Macros
// -----------------------------------------------------------------------------

#define memccpy _memccpy
#define wmemccpy _wmemccpy

#define memcasecmp _memicmp
#define wmemcasecmp _wmemicmp

#define strset _strset
#define wcsset _wcsset

#define strnset _strnset
#define wcsnset _wcsnset

#define strcasecmp _stricmp
#define wcscasecmp _wcsicmp

#define strncasecmp _strnicmp
#define wcsncasecmp _wcsnicmp

#define strupr _strupr
#define wcsupr _wcsupr

#define strlwr _strlwr
#define wcslwr _wcslwr

#define strrev _strrev
#define wcsrev _wcsrev

#define strdup _strdup
#define wcsdup _wcsdup

#define wcserror _wcserror

// -----------------------------------------------------------------------------

#endif
